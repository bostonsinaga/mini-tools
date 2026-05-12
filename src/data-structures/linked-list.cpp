#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__

#include "data-structures/linked-list.hpp"

namespace mini_tools {
namespace data_structures {

  LinkedList::LinkedList() {
    start = this;
    neighbors[LEFT] = this;
    neighbors[RIGHT] = this;
    LinkedList::Metadata::reg(this);
  }

  LinkedList *LinkedList::slice() {
    LinkedList *newTail = start->neighbors[LEFT],
      *newStart = neighbors[RIGHT];

    start->neighbors[LEFT] = this;
    neighbors[RIGHT] = start;

    xappoint(newStart);
    return newStart;
  }

  LinkedList *LinkedList::skip(int steps) {
    LinkedList *el = this;

    int valsign = steps == 0 ? 1 : std::abs(steps) / steps,
      direction = valsign < 0 ? LEFT : RIGHT;

    while (steps != 0) {
      el = el->neighbors[direction];
      steps -= valsign;
    }

    return el;
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
    return LinkedList::Metadata::existences[start].find(member)
      != LinkedList::Metadata::existences[start].end();
  }

  void LinkedList::forEach(
    const Callback &callback,
    const DIRECTION &direction
  ) {
    LinkedList::Metadata::iteratings[start] = true;
    LinkedList *el = neighbors[direction];

    // begin from this
    if (callback(this)) {
      while (el != this) {
        if (!callback(el)) break;
        el = el->neighbors[direction];
      }
    }

    LinkedList::Metadata::iteratings[start] = false;
  }

  void LinkedList::forEach(
    const CallbackCounter &callback,
    const DIRECTION &direction
  ) {
    LinkedList::Metadata::iteratings[start] = true;
    LinkedList *el = neighbors[direction];
    int ctr = 0;

    // begin from this
    if (callback(this, ctr)) {
      ctr++;

      while (el != this) {
        if (!callback(el, ctr)) break;
        el = el->neighbors[direction];;
        ctr++;
      }
    }

    LinkedList::Metadata::iteratings[start] = false;
  }

  void LinkedList::xappoint(LinkedList *newStart) {

    LinkedList::Metadata::unreg(start);
    LinkedList::Metadata::reg(newStart);

    LinkedList *el = this,
      *elTail = neighbors[LEFT];

    // transfer ownership
    while (el != elTail) {
      LinkedList::Metadata::existences[newStart].insert(el);
      el->start = newStart;
      el = el->neighbors[RIGHT];
    }

    LinkedList::Metadata::existences[newStart].insert(elTail);
    elTail->start = newStart;
  }

  void LinkedList::appoint(LinkedList *newStart) {
    if (has(newStart)) xappoint(newStart);
  }

  void LinkedList::xdetach() {
    if (atFront()) xappoint(neighbors[RIGHT]);
    else LinkedList::Metadata::existences[start].erase(this);

    neighbors[LEFT]->neighbors[RIGHT] = neighbors[RIGHT];
    neighbors[RIGHT]->neighbors[LEFT] = neighbors[LEFT];
  }

  void LinkedList::detach() {
    xdetach();
    start = this;
    LinkedList::Metadata::reg(this);
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
    LinkedList::Metadata::existences[start].insert(this);
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
    if (!LinkedList::Metadata::iteratings[start]) {
      xdetach();
      LinkedList::Metadata::existences[start].erase(this);
      delete this;
    }
  }

  void LinkedList::annihilate() {
    if (!LinkedList::Metadata::iteratings[start]) {
      LinkedList::Metadata::unreg(start);

      LinkedList *el = this,
        *elTail = neighbors[LEFT];

      while (el != elTail) {
        LinkedList *newEl = el->neighbors[RIGHT];
        delete el;
        el = newEl;
      }

      delete elTail;
    }
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__