#ifndef __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_CPP__

#include "data-structures/general-tree.hpp"

namespace mini_tools {
namespace data_structures {

  void GeneralTree::xsetParent(GeneralTree *object) {
    if (parent) parent->removeChild(this);
    object->xaddChild(this);
  }

  void GeneralTree::xaddChild(GeneralTree *object) {
    if (children) children->xaccept(object);
    else children = object;
    object->level = level + 1;
    object->parent = this;
  }

  size_t GeneralTree::numberOfChildren() {
    if (children) return children->count();
    else return 0;
  }

  bool GeneralTree::hasChild(GeneralTree *child) {
    if (children) return children->hasMember(child);
    return false;
  }

  void GeneralTree::setParent(GeneralTree *object) {
    if (object) xsetParent(object);
  }

  void GeneralTree::addChild(GeneralTree *object) {
    if (object) xaddChild(object);
  }

  void GeneralTree::removeChild(GeneralTree *child) {
    if (hasChild(child)) child->destroy();
  }

  void GeneralTree::movePointer(CR_INT steps) {
    if (children && !children->isolated()) {
      if (steps < 0) {
        for (int i = 0; i < std::abs(steps); i++) {
          children = static_cast<GeneralTree*>(children->prev());
        }
      }
      else for (int i = 0; i < steps; i++) {
        children = static_cast<GeneralTree*>(children->next());
      }
    }
  }

  void GeneralTree::resetPointer() {
    if (children) {
      children = static_cast<GeneralTree*>(children->head());
    }
  }

  void GeneralTree::cleanChildren() {
    if (children) {
      children->annihilate();
      children = nullptr;
    }
  }

  // postorder traversal
  void GeneralTree::traverse(
    const DIRECTION &direction,
    const LinkedListCallback &callback
  ) {
    LinkedListMetadata::iteratings[start] = true;
    GeneralTree *current = static_cast<GeneralTree*>(neighbors[direction]);

    if (children) children->traverse(direction, callback);
    callback(this);

    while (current && current != this) {

      if (current->children) {
        current->children->traverse(direction, callback);
      }

      callback(current);
      current = static_cast<GeneralTree*>(current->neighbors[direction]);
    }

    LinkedListMetadata::iteratings[start] = false;
  }

  // preorder traversal
  void GeneralTree::branch(
    const DIRECTION &direction,
    const LinkedListCallback &callback
  ) {
    LinkedListMetadata::iteratings[start] = true;
    GeneralTree *current = static_cast<GeneralTree*>(neighbors[direction]);

    if (callback(this)) {
      branch(direction, callback);
      current = nullptr;
    }

    while (current && current != this) {

      if (callback(current)) {
        current->branch(direction, callback);
        break;
      }

      current = static_cast<GeneralTree*>(current->neighbors[direction]);
    }

    LinkedListMetadata::iteratings[start] = false;
  }

  void GeneralTree::bubble(const LinkedListCallback &callback) {

    LinkedListMetadata::iteratings[start] = true;
    GeneralTree *current = this;

    while (current && callback(current)) {
      current = current->parent;
    }

    LinkedListMetadata::iteratings[start] = false;
  }

  /** OVERRIDES */

  void GeneralTree::detach() {
    if (parent && parent->children->isolated()) {
      parent->children = nullptr;
    }

    LinkedList::detach();
    parent = nullptr;
  }

  void GeneralTree::join(LinkedList *object) {
    if (object) {
      LinkedList::xjoin(object);
      static_cast<GeneralTree*>(object)->xsetParent(parent);
    }
  }

  void GeneralTree::accept(LinkedList *object) {
    object->join(this);
  }

  void GeneralTree::destroy() {
    if (children) children->annihilate();
    LinkedList::destroy();
  }

  // postorder traversal
  void GeneralTree::annihilate() {
    GeneralTree *current = static_cast<GeneralTree*>(neighbors[RIGHT]);

    while (current && current != this) {

      if (current->children) {
        current->children->annihilate();
      }

      delete current;
      current = static_cast<GeneralTree*>(current->neighbors[RIGHT]);
    }

    delete this;
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_CPP__