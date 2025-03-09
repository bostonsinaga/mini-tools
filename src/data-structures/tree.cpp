#ifndef __MINI_TOOLS__DATA_STRUCTURES__TREE_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__TREE_CPP__

#include "data-structures/tree.h"
#include "data-structures/vec-tools.h"

//____________|
// N-ARY TREE |
//____________|

namespace mini_tools {
namespace data_structures {

  Tree::Tree(
    CR_STR name_in,
    Tree *parent_in
  ):
  LinkedList(name_in) {
    name = name_in;
    setParent(parent_in);
  }

  bool Tree::hasChild(Tree *node) {
    for (Tree *nd : children) {
      if (nd == node) return true;
    }
    return false;
  }

  bool Tree::hasChild(CR_STR searched) {
    for (Tree *nd : children) {
      if (nd->name == searched) return true;
    }
    return false;
  }

  Tree *Tree::getChild(CR_INT index) {
    return VecTools<Tree*>::getAt(children, index, nullptr);
  }

  Tree *Tree::getChild(CR_STR searched) {
    for (Tree *nd : children) {
      if (nd->name == searched) return nd;
    }
    return nullptr;
  }

  Tree *Tree::getRoot() {
    Tree *root = this;
    while (root->parent) root = root->parent;
    return root;
  }

  void Tree::setChildren(
    CR_VEC_NODE newChildren,
    CR_BOL needEmpty,
    CR_BOL validating
  ) {
    if (newChildren.empty()) return;

    int startIdx = 0;

    if (needEmpty) children = {};
    else startIdx = children.size();

    // slower (safe)
    if (validating) {
      for (Tree *nd : newChildren) {
        if (nd) children.push_back(nd);
      }
      cleanDuplicatesInChildren();
    }
    // faster (danger)
    else {
      if (needEmpty) children = newChildren;
      else VecTools<Tree*>::concat(children, newChildren);
    }

    for (int i = startIdx; i < children.size(); i++) {
      children[i]->setParent(this, false);
      if (i > 0) children[i-1]->connect(children[i]);
    }
  }

  VEC_NODE Tree::setChildrenRelease(
    CR_VEC_NODE newChildren,
    CR_BOL validating
  ) {
    VEC_NODE oldChildren = children;
    setChildren(newChildren, true, validating);
    return oldChildren;
  }

  void Tree::setChildrenReplace(
    CR_VEC_NODE newChildren,
    CR_BOL validating
  ) {
    cleanChildren();
    setChildren(newChildren, true, validating);
  }

  void Tree::addChildren(
    CR_VEC_NODE newChildren,
    CR_BOL validating
  ) {
    setChildren(newChildren, false, validating);
  }

  void Tree::addChild(
    Tree *node,
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

  void Tree::setParent(
    Tree *newParent,
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

  void Tree::cleanDuplicatesInChildren() {
    std::tuple<VEC_NODE, VEC_NODE>
      wastedTuple = VecTools<Tree*>::cleanDuplicateInside(
        children, false,
        [](Tree *rep, Tree *nd)->bool {
          if (rep->name == nd->name) return true;
          return false;
        }
      );

    // remove duplicates of same name
    for (Tree *nd : std::get<1>(wastedTuple)) {
      nd->remove();
    }
  }

  void Tree::cleanDuplicateToLastAdded(Tree *node) {
    std::tuple<VEC_NODE, VEC_NODE>
      wastedTuple = VecTools<Tree*>::cleanDuplicateToMember(
        children, node, false,
        [](Tree *rep, Tree *nd)->bool {
          if (rep->name == nd->name) return true;
          return false;
        }
      );

    // remove duplicates of same name
    for (Tree *nd : std::get<1>(wastedTuple)) {
      nd->remove();
    }
  }

  void Tree::cleanChildren() {
    for (Tree *nd : children) {
      nd->destroy(false);
    }
  }

  Tree *Tree::dismantle(CR_INT index) {
    Tree *target = children[index];
    target->resign();
    VecTools<Tree*>::cutSingle(children, index);
    return target;
  }

  void Tree::dismantleDestroy(CR_INT index) {
    dismantle(index)->destroy(true);
  }

  Tree* Tree::dismantleRelease(CR_INT index) {
    children[index]->level = 0;
    children[index]->parent = nullptr;
    return dismantle(index);
  }

  void Tree::removeChild(Tree *node) {
    if (!node) return;

    for (int i = 0; i < children.size(); i++) {
      if (children[i] == node) {
        dismantleDestroy(i);
        break;
      }
    }
  }

  void Tree::removeChild(CR_INT index) {
    if (VecTools<Tree*>::hasIndex(children, index)) {
      dismantleDestroy(index);
    }
  }

  Tree *Tree::releaseChild(Tree *node) {
    if (!node) return nullptr;

    for (int i = 0; i < children.size(); i++) {
      if (children[i] == node) {
        return dismantleRelease(i);
      }
    }

    return nullptr;
  }

  Tree *Tree::releaseChild(CR_INT index) {
    if (VecTools<Tree*>::hasIndex(children, index)) {
      return dismantleRelease(index);
    }
    return nullptr;
  }

  VEC_NODE Tree::releaseChildren() {
    VEC_NODE released = children;

    for (Tree *nd : children) {
      nd->level = 0;
      nd->parent = nullptr;
    }

    children = {};
    return released;
  }

  void Tree::destroy(CR_BOL firstOccurrence) {
    if (firstOccurrence && parent) {
      parent->releaseChild(this);
    }
    cleanChildren();
    LinkedList::remove();
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__TREE_CPP__