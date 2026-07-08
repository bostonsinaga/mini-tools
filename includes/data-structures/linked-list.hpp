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
    class Metadata {
    public:
      inline static UNORMAP<LinkedList*, UNORSET<LinkedList*>> existences;
      inline static UNORMAP<LinkedList*, bool> iteratings;

      static void reg(LinkedList *key) {
        Metadata::existences[key].insert(key);
        Metadata::iteratings[key] = false;
      }

      static void unreg(LinkedList *key) {
        Metadata::existences.erase(key);
        Metadata::iteratings.erase(key);
      }
    };

    LinkedList *start, *neighbors[2];

    // these will not check for potential nullptr
    void xjoin(LinkedList *insider);
    void xaccept(LinkedList *outsider);
    void xappoint(LinkedList *newStart);
    void xdetach();

    // the descendant
    friend class GeneralTree;

  protected:
    virtual ~LinkedList() = default;

  public:
    enum DIRECTION { LEFT, RIGHT };

    // return false to force stop the loop
    typedef std::function<bool(LinkedList*)> Callback;
    typedef std::function<bool(LinkedList*, CR_INT)> CallbackCounter;

    LinkedList();
    LinkedList *head() { return start; }
    LinkedList *tail() { return start->neighbors[LEFT]; }
    LinkedList *next() { return neighbors[RIGHT]; }
    LinkedList *prev() { return neighbors[LEFT]; }

    // get a node in the order of steps starting from this
    LinkedList *skip(int steps);

    /**
     * Disconnect the list from the right neighbor to the very end.
     * List with less than three nodes will not be affected.
     */
    virtual LinkedList *slice();

    // merged list will have this start as the start
    virtual void merge(LinkedList *outsider);

    bool alone() { return this == neighbors[RIGHT]; }
    bool atFront() { return this == start; }
    bool atBack() { return this == start->neighbors[LEFT]; }
    size_t number() { return LinkedList::Metadata::existences[start].size(); }

    bool has(LinkedList *member);
    virtual void detach();

    /** From this to left or right loop */

    virtual void forEach(
      const Callback &callback,
      const DIRECTION &direction = RIGHT
    );

    virtual void forEach(
      const CallbackCounter &callback,
      const DIRECTION &direction = RIGHT
    );

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