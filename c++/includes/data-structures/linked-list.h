#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_H__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_H__

#include "../types.h"

namespace mini_tools {
namespace data_structures {
namespace linked_list {

  class Node {
  protected:
    std::string name;

    Node *next = nullptr,
      *previous = nullptr,
      *head = nullptr;

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
  };
}}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_H__