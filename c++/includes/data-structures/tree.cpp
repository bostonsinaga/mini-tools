#ifndef __MINI_TOOLS__DATA_STRUCTURES__TREE_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__TREE_CPP__

#include "tree.h"
#include "../utils/vec-tools.h"

namespace mini_tools {
namespace data_structures {
namespace tree {

  Node::Node(
    CR_STR name_in,
    Node *parent_in
  ):
  linked_list::Node::Node(name_in) {
    name = name_in;
    setParent(parent_in);
  }

  bool Node::hasChild(Node *node) {
    for (Node *com : children) {
      if (com == node) return true;
    }
    return false;
  }

  bool Node::hasChild(CR_STR searched) {
    for (Node *com : children) {
      if (com->name == searched) return true;
    }
    return false;
  }

  Node *Node::getChild(CR_INT index) {
    return utils::VecTools<Node*>::getAt(children, index, nullptr);
  }

  Node *Node::getChild(CR_STR searched) {
    for (Node *com : children) {
      if (com->name == searched) return com;
    }
    return nullptr;
  }

  Node *Node::getRoot() {
    Node *root = this;
    while (root->parent) root = root->parent;
    return root;
  }

  void Node::setChildren(
    CR_VEC_NODE newChildren,
    CR_BOL needEmpty,
    CR_BOL validating
  ) {
    int startIdx = 0;

    if (needEmpty) children = {};
    else startIdx = children.size();

    // slower (safe)
    if (validating) {
      for (Node *com : newChildren) {
        if (com) children.push_back(com);
      }
      cleanDuplicatesInChildren();
    }
    // faster (danger)
    else children = newChildren;

    for (int i = startIdx; i < children.size(); i++) {
      children[i]->setParent(this, false);
      if (i > 0) children[i-1]->connect(children[i]);
    }
  }

  VEC_NODE Node::setChildrenRelease(
    CR_VEC_NODE newChildren,
    CR_BOL validating
  ) {
    VEC_NODE oldChildren = children;
    setChildren(newChildren, true, validating);
    return oldChildren;
  }

  void Node::setChildrenReplace(
    CR_VEC_NODE newChildren,
    CR_BOL validating
  ) {
    cleanChildren();
    setChildren(newChildren, true, validating);
  }

  void Node::addChildren(
    CR_VEC_NODE newChildren,
    CR_BOL validating
  ) {
    setChildren(newChildren, false, validating);
  }

  void Node::addChild(
    Node *node,
    CR_BOL reconnected
  ) {
    if (node) {
      if (reconnected) {
        node->setParent(this, false);
      }

      if (!children.empty()) {
        children.back()->connect(node);
      }

      children.push_back(node);
      cleanDuplicateToLastAdded(node);
    }
  }

  void Node::setParent(
    Node *newParent,
    CR_BOL reconnected
  ) {
    if (newParent) {
      if (parent) {
        parent->releaseChild(this);
      }

      if (reconnected) {
        newParent->addChild(this, false);
      }

      parent = newParent;
      level = parent->level + 1;
    }
  }

  void Node::cleanDuplicatesInChildren() {
    std::tuple<VEC_NODE, VEC_NODE>
      wastedTuple = utils::VecTools<Node*>::cleanDuplicateInside(
        children, false,
        [](Node *rep, Node *com)->bool {
          if (rep->name == com->name) return true;
          return false;
        }
      );

    // remove duplicates of same name
    for (Node *com : std::get<1>(wastedTuple)) {
      com->remove();
    }
  }

  void Node::cleanDuplicateToLastAdded(Node *node) {
    std::tuple<VEC_NODE, VEC_NODE>
      wastedTuple = utils::VecTools<Node*>::cleanDuplicateToMember(
        children, node, false,
        [](Node *rep, Node *com)->bool {
          if (rep->name == com->name) return true;
          return false;
        }
      );

    // remove duplicates of same name
    for (Node *com : std::get<1>(wastedTuple)) {
      com->remove();
    }
  }

  void Node::cleanChildren() {
    for (Node *com : children) {
      com->destroy(false);
    }
  }

  Node *Node::dismantle(CR_INT index) {
    Node *target = children[index];
    target->resign();
    utils::VecTools<Node*>::cutSingle(children, index);
    return target;
  }

  void Node::dismantleDestroy(CR_INT index) {
    dismantle(index)->destroy(true);
  }

  Node* Node::dismantleRelease(CR_INT index) {
    children[index]->level = 0;
    children[index]->parent = nullptr;
    return dismantle(index);
  }

  void Node::removeChild(Node *node) {
    if (!node) return;

    for (int i = 0; i < children.size(); i++) {
      if (children[i] == node) {
        dismantleDestroy(i);
        break;
      }
    }
  }

  void Node::removeChild(CR_INT index) {
    if (utils::VecTools<Node*>::hasIndex(children, index)) {
      dismantleDestroy(index);
    }
  }

  Node *Node::releaseChild(Node *node) {
    if (!node) return nullptr;

    for (int i = 0; i < children.size(); i++) {
      if (children[i] == node) {
        return dismantleRelease(i);
      }
    }

    return nullptr;
  }

  Node *Node::releaseChild(CR_INT index) {
    if (utils::VecTools<Node*>::hasIndex(children, index)) {
      return dismantleRelease(index);
    }
    return nullptr;
  }

  VEC_NODE Node::releaseChildren() {
    VEC_NODE released = children;

    for (Node *com : children) {
      com->level = 0;
      com->parent = nullptr;
    }

    children = {};
    return released;
  }

  void Node::destroy(CR_BOL firstOccurrence) {
    if (firstOccurrence && parent) {
      parent->releaseChild(this);
    }
    cleanChildren();
    linked_list::Node::remove();
  }
}}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__TREE_CPP__