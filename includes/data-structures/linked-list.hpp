#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__

#include "types.hpp"

//_____________________________|
// DOUBLY CIRCULAR LINKED LIST |
//_____________________________|

namespace mini_tools {
namespace data_structures {

  class LinkedList;

  // return false to force stop the loop
  typedef std::function<bool(LinkedList*)> LinkedListCallback;

  class LinkedList {
  private:
    class Metadata final {
    public:
      Metadata() = delete;

      inline static UNORMAP<LinkedList*, bool> iteratings;
      inline static UNORMAP<LinkedList*, UNORMAP<LinkedList*, bool>> existences;

      static void create(LinkedList *leader);
      static void remove(LinkedList *leader);

      static void add(
        LinkedList *leader,
        LinkedList *follower
      );

      static void drop(
        LinkedList *leader,
        LinkedList *follower
      );
    };

    // head, prev, next
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
    size_t count() { return Metadata::existences[start].size(); }

    // from 'this' to 'left' loop
    virtual void iterate(
      const DIRECTION &direction,
      const LinkedListCallback &callback
    );

    bool hasMember(LinkedList *member);
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