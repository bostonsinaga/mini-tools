#ifndef __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_CPP__

#include "data-structures/general-tree.hpp"

namespace mini_tools {
namespace data_structures {

  void GeneralTree::xsetParent(GT *object) {
    if (parent) parent->removeChild(this);
    parent = object;
    level = object->level + 1;
  }

  void GeneralTree::xaddChild(GT *object) {
    children->xaccept(object);
    object->level = level + 1;
    object->parent = this;
  }

  size_t GeneralTree::numberOfChildren() {
    if (children) return children->count();
    else return 0;
  }

  bool GeneralTree::hasChild(GT *child) {
    if (children) return children->hasMember(child);
    return false;
  }

  void GeneralTree::setParent(GT *object) {
    if (object) xsetParent(object);
  }

  void GeneralTree::addChild(GT *object) {
    if (children) xaddChild(object);
  }

  void GeneralTree::removeChild(GT *child) {
    if (child && hasChild(child)) {
      child->destroy();
    }
  }

  void GeneralTree::movePointer(CR_INT steps) {
    if (children) {
      if (steps < 0) {
        for (int i = 0; i < std::abs(steps); i++) {
          children = static_cast<GT*>(children->prev());
        }
      }
      else for (int i = 0; i < steps; i++) {
        children = static_cast<GT*>(children->next());
      }
    }
  }

  void GeneralTree::resetPointer() {
    if (children) {
      children = static_cast<GT*>(children->head());
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
    GT *current = static_cast<GT*>(neighbors[direction]);

    if (children) children->traverse(direction, callback);
    callback(this);

    while (current && current != this) {

      if (current->children) {
        current->children->traverse(direction, callback);
      }

      callback(current);
      current = static_cast<GT*>(current->neighbors[direction]);
    }

    LinkedListMetadata::iteratings[start] = false;
  }

  // preorder traversal
  void GeneralTree::branch(
    const DIRECTION &direction,
    const LinkedListCallback &callback
  ) {
    LinkedListMetadata::iteratings[start] = true;
    GT *current = static_cast<GT*>(neighbors[direction]);

    if (callback(this)) {
      branch(direction, callback);
      current = nullptr;
    }

    while (current && current != this) {

      if (callback(current)){
        current->branch(direction, callback);
        break;
      }

      current = static_cast<GT*>(current->neighbors[direction]);
    }

    LinkedListMetadata::iteratings[start] = false;
  }

  /** OVERRIDES */

  void GeneralTree::join(LinkedList *object) {
    if (object) {
      LinkedList::xjoin(object);
      static_cast<GT*>(object)->xsetParent(parent);
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
    GT *current = static_cast<GT*>(neighbors[RIGHT]);

    while (current && current != this) {

      if (current->children) {
        current->children->annihilate();
      }

      delete current;
      current = static_cast<GT*>(current->neighbors[RIGHT]);
    }

    delete this;
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_CPP__