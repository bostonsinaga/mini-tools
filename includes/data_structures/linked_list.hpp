#ifndef __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__
#define __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__

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
    template<typename T, typename U>
    using MAP_LL = std::unordered_map<T, U>;

    inline static MAP_LL<LinkedList*, size_t> numbers;
    inline static MAP_LL<LinkedList*, bool> iteratings;
    inline static MAP_LL<LinkedList*, MAP_LL<LinkedList*, bool>> existences;

    static void create(LinkedList *leader);

    static void add(
      LinkedList *leader,
      LinkedList *follower
    );

    static void remove(LinkedList *leader);

    static void drop(
      LinkedList *leader,
      LinkedList *follower
    );

    static void appoint(
      LinkedList *leader,
      LinkedList *candidate
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
    ~LinkedList() {}

  public:
    LinkedList() {
      start = this;
      LinkedListMetadata::create(this);
    }

    enum DIRECTION { LEFT, RIGHT };

    LinkedList *head() { return start; }
    LinkedList *tail() { return start->neighbors[LEFT]; }
    LinkedList *next() { return neighbors[RIGHT]; }
    LinkedList *prev() { return neighbors[LEFT]; }

    /**
     * Disconnect list from this thus dividing it into 2 'start'.
     * Returns 'start' if this is follower.
     * Returns 'neighbors[RIGHT]' if this the 'start'.
     * Returns 'nullptr' if this is single.
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
      CR_BOL direction,
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