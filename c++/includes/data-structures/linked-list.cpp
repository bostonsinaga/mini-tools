#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__

#include "linked-list.h"

namespace mini_tools {
namespace data_structures {
namespace linked_list {

  Node::Node(CR_STR name_in) {
    name = name_in;
    head = this;
  }

  bool Node::notExist(
    Node* start,
    Node* node,
    Node* test
  ) {
    if (node == test) return false;
    else if (node->next && node->next != start) {
      return notExist(start, node->next, test);
    }
    return true;
  }

  void Node::connect(Node *node) {
    if (node && notExist(this, this, node)) {

      Node *third = next;
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

  void Node::disconnect(Node *node) {
    if (node) node->resign();
  }

  void Node::resign() {
    if (next) {
      if (head == this) {
        Node *newHead = next,
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

  void Node::remove() {
    resign();
    delete this;
  }

  void Node::sequentialRemove() {
    Node *current_1 = head,
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

  void Node::forEach(
    CR_BOOL_CB callback,
    Node *start,
    CR_BOL forwarding
  ) {
    bool keepGoing = false;

    if (forwarding) {
      keepGoing = callback(this);

      if (keepGoing && next && next != start) {
        next->forEach(callback, start, true);
      }
    }
    // reversing
    else {
      if (previous) {
        keepGoing = callback(previous);

        if (keepGoing && previous != start) {
          previous->forEach(callback, start, false);
        }
      }
      else callback(this);
    }
  }

  void Node::forEach(
    CR_VOID_CB callback,
    Node *start,
    CR_BOL forwarding
  ) {
    if (forwarding) {
      callback(this);

      if (next && next != start) {
        next->forEach(callback, start, true);
      }
    }
    else if (!forwarding) {
      if (previous) {
        callback(previous);

        if (previous != start) {
          previous->forEach(callback, start, false);
        }
      }
      else callback(this);
    }
  }

  void Node::forEach(
    CR_BOOL_CB callback,
    CR_BOL forwarding
  ) { forEach(callback, this, forwarding); }

  void Node::forEach(
    CR_VOID_CB callback,
    CR_BOL forwarding
  ) { forEach(callback, this, forwarding); }
}}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__