#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_TPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_TPP__

//_____________________________|
// DOUBLY CIRCULAR LINKED LIST |
//_____________________________|

namespace mini_tools {
namespace data_structures {
namespace linked_list {

  /** recur BOOL */

  template<typename T, typename U, typename V>
  void Node::recurBool(
    CR_BOOL_CB_TUV<T, U, V> callback,
    T addParam_1,
    U addParam_2,
    V addParam_3,
    Node *start,
    CR_BOL forwarding
  ) {
    bool keepGoing = false;

    if (forwarding) {
      keepGoing = callback(
        this, addParam_1, addParam_2, addParam_3
      );

      if (keepGoing && next && next != start) {
        next->recurBool<T, U, V>(
          callback, addParam_1, addParam_2,
          addParam_3, start, true
        );
      }
    }
    // reversing
    else {
      if (previous) {
        keepGoing = callback(
          previous, addParam_1, addParam_2, addParam_3
        );

        if (keepGoing && previous != start) {
          previous->recurBool<T, U, V>(
            callback, addParam_1, addParam_2,
            addParam_3, start, false
          );
        }
      }
      else callback(
        this, addParam_1, addParam_2, addParam_3
      );
    }
  }

  template<typename T, typename U>
  void Node::recurBool(
    CR_BOOL_CB_TU<T, U> callback,
    T addParam_1,
    U addParam_2,
    Node *start,
    CR_BOL forwarding
  ) {
    bool keepGoing = false;

    if (forwarding) {
      keepGoing = callback(this, addParam_1, addParam_2);

      if (keepGoing && next && next != start) {
        next->recurBool<T, U>(
          callback, addParam_1, addParam_2,
          start, true
        );
      }
    }
    // reversing
    else {
      if (previous) {
        keepGoing = callback(previous, addParam_1, addParam_2);

        if (keepGoing && previous != start) {
          previous->recurBool<T, U>(
            callback, addParam_1, addParam_2,
            start, false
          );
        }
      }
      else callback(this, addParam_1, addParam_2);
    }
  }

  template<typename T>
  void Node::recurBool(
    CR_BOOL_CB_T<T> callback,
    T addParam_1,
    Node *start,
    CR_BOL forwarding
  ) {
    bool keepGoing = false;

    if (forwarding) {
      keepGoing = callback(this, addParam_1);

      if (keepGoing && next && next != start) {
        next->recurBool<T>(
          callback, addParam_1, start, true
        );
      }
    }
    // reversing
    else {
      if (previous) {
        keepGoing = callback(previous, addParam_1);

        if (keepGoing && previous != start) {
          previous->recurBool<T>(
            callback, addParam_1, start, false
          );
        }
      }
      else callback(this, addParam_1);
    }
  }

  /** recur VOID */

  template<typename T, typename U, typename V>
  void Node::recurVoid(
    CR_VOID_CB_TUV<T, U, V> callback,
    T addParam_1,
    U addParam_2,
    V addParam_3,
    Node *start,
    CR_BOL forwarding
  ) {
    if (forwarding) {
      callback(
        this, addParam_1, addParam_2, addParam_3
      );

      if (next && next != start) {
        next->recurVoid<T, U, V>(
          callback, addParam_1, addParam_2,
          addParam_3, start, true
        );
      }
    }
    else if (!forwarding) {
      if (previous) {
        callback(
          previous, addParam_1, addParam_2, addParam_3
        );

        if (previous != start) {
          previous->recurVoid<T, U, V>(
            callback, addParam_1, addParam_2,
            addParam_3, start, false
          );
        }
      }
      else callback(
        this, addParam_1, addParam_2, addParam_3
      );
    }
  }

  template<typename T, typename U>
  void Node::recurVoid(
    CR_VOID_CB_TU<T, U> callback,
    T addParam_1,
    U addParam_2,
    Node *start,
    CR_BOL forwarding
  ) {
    if (forwarding) {
      callback(this, addParam_1, addParam_2);

      if (next && next != start) {
        next->recurVoid<T, U>(
          callback, addParam_1, addParam_2,
          start, true
        );
      }
    }
    else if (!forwarding) {
      if (previous) {
        callback(previous, addParam_1, addParam_2);

        if (previous != start) {
          previous->recurVoid<T, U>(
            callback, addParam_1, addParam_2,
            start, false
          );
        }
      }
      else callback(this, addParam_1, addParam_2);
    }
  }

  template<typename T>
  void Node::recurVoid(
    CR_VOID_CB_T<T> callback,
    T addParam_1,
    Node *start,
    CR_BOL forwarding
  ) {
    if (forwarding) {
      callback(this, addParam_1);

      if (next && next != start) {
        next->recurVoid<T>(
          callback, addParam_1, start, true
        );
      }
    }
    else if (!forwarding) {
      if (previous) {
        callback(previous, addParam_1);

        if (previous != start) {
          previous->recurVoid<T>(
            callback, addParam_1, start, false
          );
        }
      }
      else callback(this, addParam_1);
    }
  }
}}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_TPP__