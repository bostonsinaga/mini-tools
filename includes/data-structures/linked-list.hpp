#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__

#include "types.hpp"

namespace mini_tools {
namespace data_structures {

  /**
   * Doubly Circular Linked List.
   * Has head, previous, and next nodes.
   */
  class LinkedList {
  private:
    inline static UNORMAP<LinkedList*, UNORSET<LinkedList*>> existences;
    LinkedList *start, *neighbors[2];

    // these will not check for parameter existence
    void xjoin(LinkedList *insider);
    void xaccept(LinkedList *outsider);
    void xappoint(LinkedList *newStart);
    void xdetach();

    // the descendant
    friend class GeneralTree;

  protected:
    ~LinkedList() = default;

  public:
    enum DIRECTION { LEFT, RIGHT };

    // return false to force stop the loop
    typedef std::function<bool(LinkedList*)> Callback;

    LinkedList();
    LinkedList *head() { return start; }
    LinkedList *tail() { return start->neighbors[LEFT]; }
    LinkedList *next() { return neighbors[RIGHT]; }
    LinkedList *prev() { return neighbors[LEFT]; }

    /**
     * Disconnect the list from the right neighbor to the very end.
     * List with less than three nodes will not be affected.
     */
    virtual LinkedList *slice();

    // merged list will have this 'start' as the 'start'
    virtual void merge(LinkedList *outsider);

    bool alone() { return this == neighbors[RIGHT]; }
    bool atFront() { return this == start; }
    bool atBack() { return this == start->neighbors[LEFT]; }
    size_t number() { return LinkedList::existences[start].size(); }

    // from 'this' to left or right loop
    virtual void forEach(
      const DIRECTION &direction,
      const Callback &callback
    );

    bool has(LinkedList *member);
    virtual void detach();

    /**
     * The list will be iterated by assigning
     * each of their 'start' with 'newStart'.
     */
    virtual void appoint(LinkedList *newStart);

    // the insider is on the left
    virtual void join(LinkedList *insider);

    // the outsider is on the right
    virtual void accept(LinkedList *outsider);

    // detach and delete this
    virtual void destroy();

    // delete all nodes
    virtual void annihilate();
  };
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__