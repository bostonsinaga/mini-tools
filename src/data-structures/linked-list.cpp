#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__

#include "data-structures/linked-list.hpp"

//_____________________________|
// DOUBLY CIRCULAR LINKED LIST |
//_____________________________|

namespace mini_tools {
namespace data_structures {

  LinkedList::LinkedList() {
    start = this;
    neighbors[LEFT] = this;
    neighbors[RIGHT] = this;
    LinkedList::existences[start].insert(this);
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

  bool LinkedList::has(LinkedList *member) {
    return LinkedList::existences[start].find(member) != LinkedList::existences[start].end();
  }

  void LinkedList::forEach(
    const DIRECTION &direction,
    const Callback &callback
  ) {
    LinkedList *el = neighbors[direction];

    // begin from this
    if (callback(this)) {
      while (el != this) {
        LinkedList *newEl = el->neighbors[direction];
        if (!callback(el)) break;
        el = newEl;
      }
    }
  }

  void LinkedList::xappoint(LinkedList *newStart) {

    LinkedList::existences.erase(start);
    LinkedList::existences[newStart].insert(newStart);

    LinkedList *el = this,
      *elTail = neighbors[LEFT];

    // transfer ownership
    while (el != elTail) {
      LinkedList::existences[newStart].insert(el);
      el->start = newStart;
      el = el->neighbors[RIGHT];
    }

    LinkedList::existences[newStart].insert(elTail);
    elTail->start = newStart;
  }

  void LinkedList::appoint(LinkedList *newStart) {
    if (has(newStart)) xappoint(newStart);
  }

  void LinkedList::xdetach() {
    if (atFront()) xappoint(neighbors[RIGHT]);
    else LinkedList::existences[start].erase(this);

    neighbors[LEFT]->neighbors[RIGHT] = neighbors[RIGHT];
    neighbors[RIGHT]->neighbors[LEFT] = neighbors[LEFT];
  }

  void LinkedList::detach() {
    xdetach();
    start = this;
    LinkedList::existences[start].insert(this);
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
    LinkedList::existences[start].insert(this);
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
    xdetach();
    LinkedList::existences.erase(this);
    delete this;
  }

  void LinkedList::annihilate() {
    LinkedList::existences.erase(start);

    LinkedList *el = this,
      *elTail = neighbors[LEFT];

    while (el != elTail) {
      LinkedList *newEl = el->neighbors[RIGHT];
      delete el;
      el = newEl;
    }

    delete elTail;
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__