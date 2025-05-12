#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__

#include "types.hpp"
#include "data_structures/linked_list.hpp"

//_____________________________|
// DOUBLY CIRCULAR LINKED LIST |
//_____________________________|

namespace mini_tools {
namespace data_structures {

  /** Linked List Metadata */

  void LinkedListMetadata::create(LinkedList *leader) {
    numbers[leader] = 1;
    iteratings[leader] = false;
    existences[leader][leader] = true;
  }

  void LinkedListMetadata::add(
    LinkedList *leader,
    LinkedList *follower
  ) {
    numbers[leader]++;
    existences[leader][follower] = true;
  }

  void LinkedListMetadata::remove(LinkedList *leader) {
    numbers.erase(leader);
    iteratings.erase(leader);
    existences.erase(leader);
  }

  void LinkedListMetadata::drop(
    LinkedList *leader,
    LinkedList *follower
  ) {
    numbers[leader]--;
    existences[leader].erase(follower);
  }

  void LinkedListMetadata::appoint(
    LinkedList *leader,
    LinkedList *candidate
  ) {
    numbers[candidate] = numbers[leader];
    iteratings[candidate] = false;
    existences[candidate] = existences[leader];
    LinkedListMetadata::remove(leader);
  }

  /** LINKED LIST */

  LinkedList *LinkedList::slice() {
    if (right) {
      LinkedList *newStart;

      if (start == this) {
        newStart = right;
        detach();
      }
      else if (left == start) {
        newStart = this;
        start->detach();
      }
      else if (start->left == this) {
        newStart = start;
        detach();
      }
      else {
        LinkedList *tailBuffer = start->left;
        start->left = left;
        left->right = start;
        left = tailBuffer;
      }

      return newStart;
    }

    return nullptr;
  }

  bool LinkedList::hasMember(LinkedList *object) {
    return LinkedListMetadata::existences[start][object];
  }

  void LinkedList::iterate(
    CALLBACK &callback,
    CR_BOL ascending
  ) {
    if ((ascending && !right) ||
      (!ascending && !left)
    ) {
      callback(this);
      return;
    }

    LinkedList *current,
      *buffer = nullptr,
      *stop = this;

    if (ascending) current = right;
    else current = left;

    callback(this);
    LinkedListMetadata::iteratings[start] = true;

    if (ascending) while (current && current != stop) {
      if (!callback(current)) break;
      current = current->right;
    }
    else while (current && current != stop) {
      if (!callback(current)) break;
      current = current->left;
    }

    LinkedListMetadata::iteratings[start] = false;
  }

  void LinkedList::iterateRight(CALLBACK callback) {
    iterate(callback, true);
  }

  void LinkedList::iterateLeft(CALLBACK callback) {
    iterate(callback, false);
  }

  void LinkedList::xappoint(LinkedList *newStart) {
    LinkedListMetadata::appoint(start, newStart);

    LinkedList *current = right;
    start = newStart;

    while (current && current != this) {
      current->start = newStart;
      current = current->right;
    }
  }

  void LinkedList::appoint(LinkedList *newStart) {
    if (newStart) xappoint(newStart);
  }

  void LinkedList::xdetach() {
    if (right) {
      LinkedListMetadata::drop(start, this);
      left->right = right;
      right->left = left;

      if (start == this) xappoint(right);
    }
  }

  void LinkedList::detach() {
    xdetach();

    if (right) {
      LinkedListMetadata::create(this);
      start = this;
      left = nullptr;
      right = nullptr;
    }
  }

  void LinkedList::xjoin(LinkedList *insider) {
    xdetach();
    start = insider->start;
    left = insider;

    if (insider->right) {
      right = insider->right;
      insider->right->left = this;
    }
    else {
      right = insider;
      insider->left = this;
    }

    left = insider;
    insider->right = this;
    LinkedListMetadata::add(start, this);
  }

  void LinkedList::join(LinkedList *insider) {
    if (insider) xjoin(insider);
  }

  void LinkedList::xaccept(LinkedList *outsider) {
    outsider->xjoin(this);
  }

  void LinkedList::accept(LinkedList *outsider) {
    if (outsider) xaccept(outsider);
  }

  void LinkedList::destroy() {
    if (!LinkedListMetadata::iteratings[start]) {
      xdetach();
      LinkedListMetadata::remove(this);
      delete this;
    }
  }

  void LinkedList::annihilate() {
    if (!LinkedListMetadata::iteratings[start]) {

      LinkedListMetadata::remove(start);
      LinkedList *current = right;

      while (current && current != this) {
        delete current;
        current = current->right;
      }

      delete this;
    }
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__