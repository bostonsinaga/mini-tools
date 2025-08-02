#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__

#include "data-structures/linked-list.hpp"

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

  void LinkedListMetadata::remove(LinkedList *leader) {
    numbers.erase(leader);
    iteratings.erase(leader);
    existences.erase(leader);
  }

  void LinkedListMetadata::add(
    LinkedList *leader,
    LinkedList *follower
  ) {
    numbers[leader]++;
    existences[leader][follower] = true;
  }

  void LinkedListMetadata::drop(
    LinkedList *leader,
    LinkedList *follower
  ) {
    numbers[leader]--;
    existences[leader].erase(follower);
  }

  /** LINKED LIST */

  LinkedList::LinkedList() {
    start = this;
    LinkedListMetadata::create(this);
  }

  LinkedList *LinkedList::slice() {
    if (neighbors[RIGHT]) {
      LinkedList *newStart = start;

      // head
      if (start == this) {
        newStart = neighbors[RIGHT];
        detach();
      }
      // head right
      else if (neighbors[LEFT] == start) {
        start->detach();
      }
      // tail
      else if (start->neighbors[LEFT] == this) {
        detach();
      }
      else {
        // segment 1
        LinkedList *tailBuffer = start->neighbors[LEFT];
        start->neighbors[LEFT] = neighbors[LEFT];
        neighbors[LEFT]->neighbors[RIGHT] = start;

        // segment 2
        neighbors[LEFT] = tailBuffer;
        tailBuffer->neighbors[RIGHT] = this;

        xappoint(this);
      }

      return newStart;
    }

    return nullptr;
  }

  void LinkedList::merge(LinkedList *outsider) {
    if (outsider) {
      LinkedList *outStart = outsider->start,
        *outTail = outsider->tail();

      outsider->xappoint(start);

      outStart->neighbors[LEFT] = tail();
      outTail->neighbors[RIGHT] = start;
      tail()->neighbors[RIGHT] = outStart;
      start->neighbors[LEFT] = outTail;
    }
  }

  bool LinkedList::hasMember(LinkedList *member) {
    return UNORMAP_FOUND<LinkedList*, bool>(
      LinkedListMetadata::existences[start],
      member
    );
  }

  void LinkedList::iterate(
    const DIRECTION &direction,
    const LinkedListCallback &callback
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

    if (!UNORMAP_FOUND<LinkedList*, UNORMAP<LinkedList*, bool>>(
      LinkedListMetadata::existences,
      newStart
    )) {
      LinkedListMetadata::create(newStart);
    }

    LinkedList *current = neighbors[RIGHT];
    start = newStart;

    while (current && current != this) {

      // transfer ownership
      LinkedListMetadata::drop(start, current);
      LinkedListMetadata::add(newStart, current);

      current->start = newStart;
      current = current->neighbors[RIGHT];
    }
  }

  void LinkedList::appoint(LinkedList *newStart) {
    if (hasMember(newStart)) xappoint(newStart);
  }

  void LinkedList::xdetach() {
    if (neighbors[RIGHT]) {

      if (start == this) {
        xappoint(neighbors[RIGHT]);
        start = this;
      }
      else LinkedListMetadata::drop(start, this);

      neighbors[LEFT]->neighbors[RIGHT] = neighbors[RIGHT];
      neighbors[RIGHT]->neighbors[LEFT] = neighbors[LEFT];
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

      LinkedList *newCurrent,
        *current = neighbors[RIGHT];

      while (current && current != this) {
        newCurrent = current->neighbors[RIGHT];
        delete current;
        current = newCurrent;
      }

      delete this;
    }
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__