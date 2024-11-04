#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__

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

  /** recur BOOL */

  template<typename T, typename U, typename V>
  void Node::recurBool(
    CR_BOOL_CB_TUV<T, U, V> callback,
    CR_TUPLE_TUV<T, U, V> additionalParams,
    Node *start,
    CR_BOL forwarding
  ) {
    bool keepGoing = false;

    if (forwarding) {
      keepGoing = callback(
        this,
        std::get<0>(additionalParams),
        std::get<1>(additionalParams),
        std::get<2>(additionalParams)
      );

      if (keepGoing && next && next != start) {
        next->recurBool(
          callback, additionalParams, start, true
        );
      }
    }
    // reversing
    else {
      if (previous) {
        keepGoing = callback(
          previous,
          std::get<0>(additionalParams),
          std::get<1>(additionalParams),
          std::get<2>(additionalParams)
        );

        if (keepGoing && previous != start) {
          previous->recurBool(
            callback, additionalParams, start, false
          );
        }
      }
      else callback(
        this,
        std::get<0>(additionalParams),
        std::get<1>(additionalParams),
        std::get<2>(additionalParams)
      );
    }
  }

  template<typename T, typename U>
  void Node::recurBool(
    CR_BOOL_CB_TU<T, U> callback,
    CR_TUPLE_TU<T, U> additionalParams,
    Node *start,
    CR_BOL forwarding
  ) {
    bool keepGoing = false;

    if (forwarding) {
      keepGoing = callback(
        this,
        std::get<0>(additionalParams),
        std::get<1>(additionalParams)
      );

      if (keepGoing && next && next != start) {
        next->recurBool(
          callback, additionalParams, start, true
        );
      }
    }
    // reversing
    else {
      if (previous) {
        keepGoing = callback(
          previous,
          std::get<0>(additionalParams),
          std::get<1>(additionalParams)
        );

        if (keepGoing && previous != start) {
          previous->recurBool(
            callback, additionalParams, start, false
          );
        }
      }
      else callback(
        this,
        std::get<0>(additionalParams),
        std::get<1>(additionalParams)
      );
    }
  }

  template<typename T>
  void Node::recurBool(
    CR_BOOL_CB_T<T> callback,
    CR<T> additionalParam,
    Node *start,
    CR_BOL forwarding
  ) {
    bool keepGoing = false;

    if (forwarding) {
      keepGoing = callback(this, additionalParam);

      if (keepGoing && next && next != start) {
        next->recurBool(
          callback, additionalParam, start, true
        );
      }
    }
    // reversing
    else {
      if (previous) {
        keepGoing = callback(previous, additionalParam);

        if (keepGoing && previous != start) {
          previous->recurBool(
            callback, additionalParam, start, false
          );
        }
      }
      else callback(this, additionalParam);
    }
  }

  void Node::recurBool(
    CR_BOOL_CB callback,
    Node *start,
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

  /** recur VOID */

  template<typename T, typename U, typename V>
  void Node::recurVoid(
    CR_VOID_CB_TUV<T, U, V> callback,
    CR_TUPLE_TUV<T, U, V> additionalParams,
    Node *start,
    CR_BOL forwarding
  ) {
    if (forwarding) {
      callback(
        this,
        std::get<0>(additionalParams),
        std::get<1>(additionalParams),
        std::get<2>(additionalParams)
      );

      if (next && next != start) {
        next->recurVoid(
          callback, additionalParams, start, true
        );
      }
    }
    else if (!forwarding) {
      if (previous) {
        callback(
          previous,
          std::get<0>(additionalParams),
          std::get<1>(additionalParams),
          std::get<2>(additionalParams)
        );

        if (previous != start) {
          previous->recurVoid(
            callback, additionalParams, start, false
          );
        }
      }
      else callback(
        this,
        std::get<0>(additionalParams),
        std::get<1>(additionalParams),
        std::get<2>(additionalParams)
      );
    }
  }

  template<typename T, typename U>
  void Node::recurVoid(
    CR_VOID_CB_TU<T, U> callback,
    CR_TUPLE_TU<T, U> additionalParams,
    Node *start,
    CR_BOL forwarding
  ) {
    if (forwarding) {
      callback(
        this,
        std::get<0>(additionalParams),
        std::get<1>(additionalParams)
      );

      if (next && next != start) {
        next->recurVoid(
          callback, additionalParams, start, true
        );
      }
    }
    else if (!forwarding) {
      if (previous) {
        callback(
          previous,
          std::get<0>(additionalParams),
          std::get<1>(additionalParams)
        );

        if (previous != start) {
          previous->recurVoid(
            callback, additionalParams, start, false
          );
        }
      }
      else callback(
        this,
        std::get<0>(additionalParams),
        std::get<1>(additionalParams)
      );
    }
  }

  template<typename T>
  void Node::recurVoid(
    CR_VOID_CB_T<T> callback,
    CR<T> additionalParam,
    Node *start,
    CR_BOL forwarding
  ) {
    if (forwarding) {
      callback(this, additionalParam);

      if (next && next != start) {
        next->recurVoid(
          callback, additionalParam, start, true
        );
      }
    }
    else if (!forwarding) {
      if (previous) {
        callback(previous, additionalParam);

        if (previous != start) {
          previous->recurVoid(
            callback, additionalParam, start, false
          );
        }
      }
      else callback(this, additionalParam);
    }
  }

  void Node::recurVoid(
    CR_VOID_CB callback,
    Node *start,
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
}}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_CPP__