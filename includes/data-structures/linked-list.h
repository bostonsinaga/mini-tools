#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_H__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_H__

#include "../types.h"

namespace mini_tools {
namespace data_structures {
namespace linked_list {

  //_____________________________|
  // DOUBLY CIRCULAR LINKED LIST |
  //_____________________________|
  class Node {
  private:
    bool notExist(
      Node* start,
      Node* node,
      Node* test
    );

    /** using std::function<bool> */

    template<typename T, typename U, typename V>
    using CR_BOOL_CB_TUV = const std::function<bool(Node*, T, U, V)>&;

    template<typename T, typename U>
    using CR_BOOL_CB_TU = const std::function<bool(Node*, T, U)>&;

    template<typename T>
    using CR_BOOL_CB_T = const std::function<bool(Node*, T)>&;

    using CR_BOOL_CB = const std::function<bool(Node*)>&;

    /** typedef std::function<void> */

    template<typename T, typename U, typename V>
    using CR_VOID_CB_TUV = const std::function<void(Node*, T, U, V)>&;

    template<typename T, typename U>
    using CR_VOID_CB_TU = const std::function<void(Node*, T, U)>&;

    template<typename T>
    using CR_VOID_CB_T = const std::function<void(Node*, T)>&;

    using CR_VOID_CB = const std::function<void(Node*)>&;

    /** recur std::function<bool> */

    template<typename T, typename U, typename V>
    void recurBool(
      CR_BOOL_CB_TUV<T, U, V> callback,
      T addParam_1,
      U addParam_2,
      V addParam_3,
      Node *start,
      CR_BOL forwarding
    );

    template<typename T, typename U>
    void recurBool(
      CR_BOOL_CB_TU<T, U> callback,
      T addParam_1,
      U addParam_2,
      Node *start,
      CR_BOL forwarding
    );

    template<typename T>
    void recurBool(
      CR_BOOL_CB_T<T> callback,
      T addParam_1,
      Node *start,
      CR_BOL forwarding
    );

    void recurBool(
      CR_BOOL_CB callback,
      Node *start,
      CR_BOL forwarding
    );

    /** recur std::function<void> */

    template<typename T, typename U, typename V>
    void recurVoid(
      CR_VOID_CB_TUV<T, U, V> callback,
      T addParam_1,
      U addParam_2,
      V addParam_3,
      Node *start,
      CR_BOL forwarding
    );

    template<typename T, typename U>
    void recurVoid(
      CR_VOID_CB_TU<T, U> callback,
      T addParam_1,
      U addParam_2,
      Node *start,
      CR_BOL forwarding
    );

    template<typename T>
    void recurVoid(
      CR_VOID_CB_T<T> callback,
      T addParam_1,
      Node *start,
      CR_BOL forwarding
    );

    void recurVoid(
      CR_VOID_CB callback,
      Node *start,
      CR_BOL forwarding
    );

  protected:
    std::string name;

    Node *head = nullptr,
      *next = nullptr,
      *previous = nullptr;

    ~Node() {}

  public:
    Node() {}
    Node(CR_STR name_in);

    void connect(Node *node);
    void disconnect(Node *node);
    void resign();

    virtual void remove();
    void sequentialRemove();

    Node *getNext() { return next; }
    Node *getPrevious() { return previous; }
    Node *getHead() { return head; }
    std::string getName() { return name; }

    /** iterate bool(*) */

    template<typename T, typename U, typename V>
    void iterate(
      bool (*callback)(Node*, T, U, V),
      T addParam_1,
      U addParam_2,
      V addParam_3,
      CR_BOL forwarding = true
    ) {
      recurBool<T, U, V>(
        callback, addParam_1, addParam_2,
        addParam_3, this, forwarding
      );
    }

    template<typename T, typename U>
    void iterate(
      bool (*callback)(Node*, T, U),
      T addParam_1,
      U addParam_2,
      CR_BOL forwarding = true
    ) {
      recurBool<T, U>(
        callback, addParam_1, addParam_2,
        this, forwarding
      );
    }

    template<typename T>
    void iterate(
      bool (*callback)(Node*, T),
      T addParam_1,
      CR_BOL forwarding = true
    ) {
      recurBool<T>(
        callback, addParam_1, this, forwarding
      );
    }

    void iterate(
      bool (*callback)(Node*),
      CR_BOL forwarding = true
    ) {
      recurBool(callback, this, forwarding);
    }

    /** iterate void(*) */

    template<typename T, typename U, typename V>
    void iterate(
      void (*callback)(Node*, T, U, V),
      T addParam_1,
      U addParam_2,
      V addParam_3,
      CR_BOL forwarding = true
    ) {
      recurVoid<T, U, V>(
        callback, addParam_1, addParam_2,
        addParam_3, this, forwarding
      );
    }

    template<typename T, typename U>
    void iterate(
      void (*callback)(Node*, T, U),
      T addParam_1,
      U addParam_2,
      CR_BOL forwarding = true
    ) {
      recurVoid<T, U>(
        callback, addParam_1, addParam_2,
        this, forwarding
      );
    }

    template<typename T>
    void iterate(
      void (*callback)(Node*, T),
      T addParam_1,
      CR_BOL forwarding = true
    ) {
      recurVoid<T>(
        callback, addParam_1, this, forwarding
      );
    }

    void iterate(
      void (*callback)(Node*),
      CR_BOL forwarding = true
    ) {
      recurVoid(callback, this, forwarding);
    }

    /** iterate std::function<bool> */

    template<typename T, typename U, typename V>
    void iterate(
      CR_BOOL_CB_TUV<T, U, V> callback,
      T addParam_1,
      U addParam_2,
      V addParam_3,
      CR_BOL forwarding = true
    ) {
      recurBool<T, U, V>(
        callback, addParam_1, addParam_2,
        addParam_3, this, forwarding
      );
    }

    template<typename T, typename U>
    void iterate(
      CR_BOOL_CB_TU<T, U> callback,
      T addParam_1,
      U addParam_2,
      CR_BOL forwarding = true
    ) {
      recurBool<T, U>(
        callback, addParam_1, addParam_2,
        this, forwarding
      );
    }

    template<typename T>
    void iterate(
      CR_BOOL_CB_T<T> callback,
      T addParam_1,
      CR_BOL forwarding = true
    ) {
      recurBool<T>(
        callback, addParam_1, this, forwarding
      );
    }

    void iterate(
      CR_BOOL_CB callback,
      CR_BOL forwarding = true
    ) {
      recurBool(callback, this, forwarding);
    }

    /** iterate std::function<void> */

    template<typename T, typename U, typename V>
    void iterate(
      CR_VOID_CB_TUV<T, U, V> callback,
      T addParam_1,
      U addParam_2,
      V addParam_3,
      CR_BOL forwarding = true
    ) {
      recurVoid<T, U, V>(
        callback, addParam_1, addParam_2,
        addParam_3, this, forwarding
      );
    }

    template<typename T, typename U>
    void iterate(
      CR_VOID_CB_TU<T, U> callback,
      T addParam_1,
      U addParam_2,
      CR_BOL forwarding = true
    ) {
      recurVoid<T, U>(
        callback, addParam_1, addParam_2,
        this, forwarding
      );
    }

    template<typename T>
    void iterate(
      CR_VOID_CB_T<T> callback,
      T addParam_1,
      CR_BOL forwarding = true
    ) {
      recurVoid<T>(
        callback, addParam_1, this, forwarding
      );
    }

    void iterate(
      CR_VOID_CB callback,
      CR_BOL forwarding = true
    ) {
      recurVoid(callback, this, forwarding);
    }
  };
}}}

#include "linked-list.tpp"
#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_H__