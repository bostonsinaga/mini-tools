#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__

#include "data-structures/linked-list.hpp"

//_____________________________|
// DOUBLY CIRCULAR LINKED LIST |
//_____________________________|

namespace mini_tools {
namespace data_structures {

  /** METADATA */

  void LinkedList::Metadata::create(LinkedList *leader) {
    iteratings[leader] = false;
    existences[leader][leader] = true;
  }

  void LinkedList::Metadata::remove(LinkedList *leader) {
    iteratings.erase(leader);
    existences.erase(leader);
  }

  void LinkedList::Metadata::add(
    LinkedList *leader,
    LinkedList *follower
  ) {
    existences[leader][follower] = true;
  }

  void LinkedList::Metadata::drop(
    LinkedList *leader,
    LinkedList *follower
  ) {
    existences[leader].erase(follower);
  }

  /** LINKED LIST */

  LinkedList::LinkedList() {
    start = this;
    neighbors[LEFT] = this;
    neighbors[RIGHT] = this;
    Metadata::create(this);
  }

  LinkedList *LinkedList::slice() {
    LinkedList *newTail = start->neighbors[LEFT],
      *newStart = neighbors[RIGHT];

    start->neighbors[LEFT] = this;
    neighbors[RIGHT] = start;

    xappoint(newStart);
    return newStart;
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
      Metadata::existences[start],
      member
    );
  }

  void LinkedList::iterate(
    const DIRECTION &direction,
    const LinkedListCallback &callback
  ) {
    Metadata::iteratings[start] = true;

    // begin from this
    if (!callback(this) || !neighbors[direction]) {
      Metadata::iteratings[start] = false;
      return;
    }

    LinkedList *current = neighbors[direction];

    while (current != this) {
      if (!callback(current)) break;
      current = current->neighbors[direction];
    }

    Metadata::iteratings[start] = false;
  }

  void LinkedList::xappoint(LinkedList *newStart) {

    Metadata::remove(start);
    Metadata::create(newStart);
    LinkedList *current = neighbors[RIGHT];

    // transfer ownership
    while (current != this) {
      Metadata::add(newStart, current);
      current->start = newStart;
      current = current->neighbors[RIGHT];
    }

    Metadata::add(newStart, this);
    start = newStart;
  }

  void LinkedList::appoint(LinkedList *newStart) {
    if (hasMember(newStart)) xappoint(newStart);
  }

  void LinkedList::xdetach() {
    if (atFront()) xappoint(neighbors[RIGHT]);
    else Metadata::drop(start, this);

    neighbors[LEFT]->neighbors[RIGHT] = neighbors[RIGHT];
    neighbors[RIGHT]->neighbors[LEFT] = neighbors[LEFT];
  }

  void LinkedList::detach() {
    xdetach();
    start = this;
    Metadata::create(this);
    Metadata::add(start, this);
    neighbors[LEFT] = this;
    neighbors[RIGHT] = this;
  }

  void LinkedList::xjoin(LinkedList *insider) {
    xdetach();
    start = insider->start;
    neighbors[LEFT] = insider;
    neighbors[RIGHT] = insider->neighbors[RIGHT];
    insider->neighbors[RIGHT]->neighbors[LEFT] = this;
    insider->neighbors[RIGHT] = this;
    Metadata::add(start, this);
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
    if (!Metadata::iteratings[start]) {
      xdetach();
      Metadata::remove(this);
      delete this;
    }
  }

  void LinkedList::annihilate() {

    if (!Metadata::iteratings[start]) {
      Metadata::remove(start);

      LinkedList *newCurrent,
        *current = neighbors[RIGHT];

      while (current != this) {
        newCurrent = current->neighbors[RIGHT];
        delete current;
        current = newCurrent;
      }

      delete this;
    }
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__