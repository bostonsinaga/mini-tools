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
    children = object;
    object->level = level + 1;
    object->parent = this;
  }

  size_t GeneralTree::numberOfChildren() {
    if (children) return children->number();
    else return 0;
  }

  bool GeneralTree::hasChild(GeneralTree *child) {
    if (children) return children->has(child);
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

  void GeneralTree::releaseChild(GeneralTree *child) {
    if (hasChild(child)) child->detach();
  }

  void GeneralTree::movePointer(CR_INT steps) {
    if (children && !children->alone()) {
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
      children->xannihilate();
      children = nullptr;
    }
  }

  void GeneralTree::traverse(
    const DIRECTION &direction,
    const Callback &callback
  ) {
    GeneralTree *el = static_cast<GeneralTree*>(neighbors[direction]);

    if (children) children->traverse(direction, callback);
    callback(this);

    while (el && el != this) {

      if (el->children) {
        el->children->traverse(direction, callback);
      }

      GeneralTree *newEl = static_cast<GeneralTree*>(el->neighbors[direction]);
      callback(el);
      el = newEl;
    }
  }

  void GeneralTree::bubble(const Callback &callback) {
    GeneralTree *el = this;

    while (el && callback(el)) {
      el = el->parent;
    }
  }

  GeneralTree *GeneralTree::getRoot() {
    GeneralTree *el = this;
    while (el->parent) el = el->parent;
    return el;
  }

  /** OVERRIDES */

  void GeneralTree::detach() {

    if (parent) {
      if (parent->children->alone()) {
        parent->children = nullptr;
      }

      parent = nullptr;
    }

    LinkedList::detach();
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
    if (parent && parent->children->alone()) {
      parent->children = nullptr;
    }

    if (children) children->xannihilate();
  }

  // postorder traversal
  void GeneralTree::xannihilate() {

    LinkedList::existences.erase(start);
    GeneralTree *el = static_cast<GeneralTree*>(neighbors[RIGHT]);

    // vertically and horizontally recursive deletion
    while (el && el != this) {

      if (el->children) {
        el->children->xannihilate();
      }

      GeneralTree *newEl = static_cast<GeneralTree*>(el->neighbors[RIGHT]);
      delete el;
      el = newEl;
    }

    delete this;
  }

  void GeneralTree::annihilate() {
    if (parent) parent->children = nullptr;
    xannihilate();
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_CPP__