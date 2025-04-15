#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__

#include "types.hpp"

//_____________________________|
// DOUBLY CIRCULAR LINKED LIST |
//_____________________________|

namespace mini_tools {
namespace data_structures {

  class LinkedList {
  private:
    bool notExist(
      LinkedList* start,
      LinkedList* linkedList,
      LinkedList* test
    );

    /** using std::function<bool> */

    template<typename T, typename U, typename V>
    using CR_BOOL_CB_TUV = const std::function<bool(LinkedList*, T, U, V)>&;

    template<typename T, typename U>
    using CR_BOOL_CB_TU = const std::function<bool(LinkedList*, T, U)>&;

    template<typename T>
    using CR_BOOL_CB_T = const std::function<bool(LinkedList*, T)>&;

    using CR_BOOL_CB = const std::function<bool(LinkedList*)>&;

    /** using std::function<void> */

    template<typename T, typename U, typename V>
    using CR_VOID_CB_TUV = const std::function<void(LinkedList*, T, U, V)>&;

    template<typename T, typename U>
    using CR_VOID_CB_TU = const std::function<void(LinkedList*, T, U)>&;

    template<typename T>
    using CR_VOID_CB_T = const std::function<void(LinkedList*, T)>&;

    using CR_VOID_CB = const std::function<void(LinkedList*)>&;

    /** recur std::function<bool> */

    template<typename T, typename U, typename V>
    void recurBool(
      CR_BOOL_CB_TUV<T, U, V> callback,
      T addParam_1,
      U addParam_2,
      V addParam_3,
      LinkedList *start,
      CR_BOL forwarding
    );

    template<typename T, typename U>
    void recurBool(
      CR_BOOL_CB_TU<T, U> callback,
      T addParam_1,
      U addParam_2,
      LinkedList *start,
      CR_BOL forwarding
    );

    template<typename T>
    void recurBool(
      CR_BOOL_CB_T<T> callback,
      T addParam_1,
      LinkedList *start,
      CR_BOL forwarding
    );

    void recurBool(
      CR_BOOL_CB callback,
      LinkedList *start,
      CR_BOL forwarding
    );

    /** recur std::function<void> */

    template<typename T, typename U, typename V>
    void recurVoid(
      CR_VOID_CB_TUV<T, U, V> callback,
      T addParam_1,
      U addParam_2,
      V addParam_3,
      LinkedList *start,
      CR_BOL forwarding
    );

    template<typename T, typename U>
    void recurVoid(
      CR_VOID_CB_TU<T, U> callback,
      T addParam_1,
      U addParam_2,
      LinkedList *start,
      CR_BOL forwarding
    );

    template<typename T>
    void recurVoid(
      CR_VOID_CB_T<T> callback,
      T addParam_1,
      LinkedList *start,
      CR_BOL forwarding
    );

    void recurVoid(
      CR_VOID_CB callback,
      LinkedList *start,
      CR_BOL forwarding
    );

  protected:
    std::string name;

    LinkedList *head = nullptr,
      *next = nullptr,
      *previous = nullptr;

    ~LinkedList() {}

  public:
    LinkedList() {}
    LinkedList(CR_STR name_in);

    void connect(LinkedList *linkedList);
    void disconnect(LinkedList *linkedList);
    void resign();

    virtual void remove();
    void sequentialRemove();

    LinkedList *getNext() { return next; }
    LinkedList *getPrevious() { return previous; }
    LinkedList *getHead() { return head; }
    std::string getName() { return name; }

    /** iterate bool(*) */

    template<typename T, typename U, typename V>
    void iterate(
      bool (*callback)(LinkedList*, T, U, V),
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
      bool (*callback)(LinkedList*, T, U),
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
      bool (*callback)(LinkedList*, T),
      T addParam_1,
      CR_BOL forwarding = true
    ) {
      recurBool<T>(
        callback, addParam_1, this, forwarding
      );
    }

    void iterate(
      bool (*callback)(LinkedList*),
      CR_BOL forwarding = true
    ) {
      recurBool(callback, this, forwarding);
    }

    /** iterate void(*) */

    template<typename T, typename U, typename V>
    void iterate(
      void (*callback)(LinkedList*, T, U, V),
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
      void (*callback)(LinkedList*, T, U),
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
      void (*callback)(LinkedList*, T),
      T addParam_1,
      CR_BOL forwarding = true
    ) {
      recurVoid<T>(
        callback, addParam_1, this, forwarding
      );
    }

    void iterate(
      void (*callback)(LinkedList*),
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
}}

#include "data_structures/linked_list.tpp"
#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__