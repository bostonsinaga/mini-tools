#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_TPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_TPP__

namespace mini_tools {
namespace data_structures {
namespace linked_list {

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
}}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_TPP__