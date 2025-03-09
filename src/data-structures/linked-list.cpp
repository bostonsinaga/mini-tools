#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__

#include "data-structures/linked-list.h"

//_____________________________|
// DOUBLY CIRCULAR LINKED LIST |
//_____________________________|

namespace mini_tools {
namespace data_structures {

  LinkedList::LinkedList(CR_STR name_in) {
    name = name_in;
    head = this;
  }

  bool LinkedList::notExist(
    LinkedList* start,
    LinkedList* node,
    LinkedList* test
  ) {
    if (node == test) return false;
    else if (node->next && node->next != start) {
      return notExist(start, node->next, test);
    }
    return true;
  }

  void LinkedList::connect(LinkedList *node) {
    if (node && notExist(this, this, node)) {

      LinkedList *third = next;
      node->resign();

      if (!third) {
        third = head;
        previous = node;
      }

      next = node;
      node->head = head;
      node->next = third;
      node->previous = this;
      third->previous = node;
    }
  }

  void LinkedList::disconnect(LinkedList *node) {
    if (node) node->resign();
  }

  void LinkedList::resign() {
    if (next) {
      if (head == this) {
        LinkedList *newHead = next,
          *current = next;

        while (current != this) {
          current->head = newHead;
          current = current->next;
        }
      }

      if (next == previous) {
        next->previous = nullptr;
        previous->next = nullptr;
      }
      else {
        next->previous = previous;
        previous->next = next;
      }

      next = nullptr;
      previous = nullptr;
      head = this;
    }
  }

  void LinkedList::remove() {
    resign();
    delete this;
  }

  void LinkedList::sequentialRemove() {
    LinkedList *current_1 = head,
      *current_2 = nullptr;

    bool willBreak = false;

    while (true) {
      current_2 = current_1->next;

      if (!current_2) {
        willBreak = true;
      }

      current_1->remove();
      current_1 = current_2;

      if (willBreak) break;
    }
  }

  void LinkedList::recurBool(
    CR_BOOL_CB callback,
    LinkedList *start,
    CR_BOL forwarding
  ) {
    bool keepGoing = false;

    if (forwarding) {
      keepGoing = callback(this);

      if (keepGoing && next && next != start) {
        next->recurBool(callback, start, true);
      }
    }
    // reversing
    else {
      if (previous) {
        keepGoing = callback(previous);

        if (keepGoing && previous != start) {
          previous->recurBool(callback, start, false);
        }
      }
      else callback(this);
    }
  }

  void LinkedList::recurVoid(
    CR_VOID_CB callback,
    LinkedList *start,
    CR_BOL forwarding
  ) {
    if (forwarding) {
      callback(this);

      if (next && next != start) {
        next->recurVoid(callback, start, true);
      }
    }
    else if (!forwarding) {
      if (previous) {
        callback(previous);

        if (previous != start) {
          previous->recurVoid(callback, start, false);
        }
      }
      else callback(this);
    }
  }
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__