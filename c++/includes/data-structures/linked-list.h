#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_H__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_H__

#include "../types.h"

namespace mini_tools {
namespace data_structures {
namespace linked_list {

  class Node {
  private:
    typedef const std::function<bool(Node*)>& CR_BOOL_CB;
    typedef const std::function<void(Node*)>& CR_VOID_CB;

    bool notExist(
      Node* start,
      Node* node,
      Node* test
    );

    void forEach(
      CR_VOID_CB callback,
      Node *start,
      CR_BOL forwarding
    );

    void forEach(
      CR_BOOL_CB callback,
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

    void forEach(
      CR_VOID_CB callback,
      CR_BOL forwarding = true
    );

    void forEach(
      CR_BOOL_CB callback,
      CR_BOL forwarding = true
    );

    Node *getNext() { return next; }
    Node *getPrevious() { return previous; }
    Node *getHead() { return head; }
    std::string getName() { return name; }
  };
}}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_H__