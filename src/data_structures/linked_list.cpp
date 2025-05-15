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
    if (neighbors[RIGHT]) {
      LinkedList *newStart;

      if (start == this) {
        newStart = neighbors[RIGHT];
        detach();
      }
      else if (neighbors[LEFT] == start) {
        newStart = this;
        start->detach();
      }
      else if (start->neighbors[LEFT] == this) {
        newStart = start;
        detach();
      }
      else {
        LinkedList *tailBuffer = start->neighbors[LEFT];
        start->neighbors[LEFT] = neighbors[LEFT];
        neighbors[LEFT]->neighbors[RIGHT] = start;
        neighbors[LEFT] = tailBuffer;
      }

      return newStart;
    }

    return nullptr;
  }

  bool LinkedList::hasMember(LinkedList *object) {
    return LinkedListMetadata::existences[start][object];
  }

  void LinkedList::iterate(
    CR_BOL direction,
    CR_CALLBACK &callback
  ) {
    LinkedListMetadata::iteratings[start] = true;

    // begin from this
    if (!callback(this) || !neighbors[direction]) return;

    LinkedList *current = neighbors[direction];

    while (current && current != this) {
      if (!callback(current)) break;
      current = current->neighbors[direction];
    }

    LinkedListMetadata::iteratings[start] = false;
  }

  void LinkedList::xappoint(LinkedList *newStart) {
    LinkedListMetadata::appoint(start, newStart);

    LinkedList *current = neighbors[RIGHT];
    start = newStart;

    while (current && current != this) {
      current->start = newStart;
      current = current->neighbors[RIGHT];
    }
  }

  void LinkedList::appoint(LinkedList *newStart) {
    if (newStart) xappoint(newStart);
  }

  void LinkedList::xdetach() {
    if (neighbors[RIGHT]) {
      LinkedListMetadata::drop(start, this);
      neighbors[LEFT]->neighbors[RIGHT] = neighbors[RIGHT];
      neighbors[RIGHT]->neighbors[LEFT] = neighbors[LEFT];

      if (start == this) xappoint(neighbors[RIGHT]);
    }
  }

  void LinkedList::detach() {
    xdetach();

    if (neighbors[RIGHT]) {
      LinkedListMetadata::create(this);
      start = this;
      neighbors[LEFT] = nullptr;
      neighbors[RIGHT] = nullptr;
    }
  }

  void LinkedList::xjoin(LinkedList *insider) {
    xdetach();
    start = insider->start;
    neighbors[LEFT] = insider;

    if (insider->neighbors[RIGHT]) {
      neighbors[RIGHT] = insider->neighbors[RIGHT];
      insider->neighbors[RIGHT]->neighbors[LEFT] = this;
    }
    else {
      neighbors[RIGHT] = insider;
      insider->neighbors[LEFT] = this;
    }

    neighbors[LEFT] = insider;
    insider->neighbors[RIGHT] = this;
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
      LinkedList *current = neighbors[RIGHT];

      while (current && current != this) {
        delete current;
        current = current->neighbors[RIGHT];
      }

      delete this;
    }
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__