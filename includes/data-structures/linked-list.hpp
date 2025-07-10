#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__

#include "types.hpp"

//_____________________________|
// DOUBLY CIRCULAR LINKED LIST |
//_____________________________|

namespace mini_tools {
namespace data_structures {

  class LinkedList;

  class LinkedListMetadata final {
  public:
    LinkedListMetadata() = delete;

  private:
    inline static UNORMAP<LinkedList*, size_t> numbers;
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

    friend class LinkedList;
    friend class GeneralTree;
  };

  class LinkedList {
  public:
    // return false to force stop the loop
    typedef std::function<bool(LinkedList*)> CALLBACK;
    typedef const CALLBACK& CR_CALLBACK;

  private:
    LinkedList *start,
      *neighbors[2] = {nullptr, nullptr};

    // these will not check for parameter existence
    void xjoin(LinkedList *insider);
    void xaccept(LinkedList *outsider);
    void xappoint(LinkedList *newStart);
    void xdetach();

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
     * Disconnect list from this thus dividing it into 2 'start'
     * and make this a 'start' for the right followers.
     * 
     * Rules:
     *  Returns 'start' if this is follower.
     *  Returns 'neighbors[RIGHT]' if this the 'start'.
     *  Returns 'nullptr' if this is single.
     */
    LinkedList *slice();

    // merged list will have this 'start' as the 'start'
    void merge(LinkedList *outsider);

    bool isolated() { return !neighbors[RIGHT]; }
    bool atFront() { return this == start; }
    bool atBack() { return this == start->neighbors[LEFT]; }
    size_t count() { return LinkedListMetadata::numbers[start]; }

    // from 'this' to 'left' loop
    void iterate(
      const DIRECTION &direction,
      CR_CALLBACK callback
    );

    bool hasMember(LinkedList *member);
    void detach();

    /**
     * The list will be iterated by assigning
     * each of their 'start' with 'newStart'.
     */
    void appoint(LinkedList *newStart);

    virtual void join(LinkedList *insider);
    virtual void accept(LinkedList *outsider);
    virtual void destroy();
    virtual void annihilate();
  };
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__