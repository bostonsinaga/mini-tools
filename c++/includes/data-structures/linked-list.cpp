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

  void Node::connect(Node *node) {
    if (node) {
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
}}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__