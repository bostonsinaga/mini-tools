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
  };

  class LinkedList {
  public:
    // return false to force stop the loop
    typedef std::function<bool(LinkedList*)> CALLBACK;

  private:
    LinkedList *start,
      *left = nullptr,
      *right = nullptr;

    void iterate(
      CALLBACK &callback,
      CR_BOL ascending
    );

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

    LinkedList *head() { return start; }
    LinkedList *tail() { return start->left; }
    LinkedList *next() { return right; }
    LinkedList *prev() { return left; }

    /**
     * Disconnect list from this thus dividing it into 2 'start'.
     * Returns 'start' if this is follower.
     * Returns 'right' if this the 'start'.
     * Returns 'nullptr' if this is single.
     */
    LinkedList *slice();

    bool isolated() { return !right; }
    bool atFront() { return this == start; }
    bool atBack() { return this == start->left; }
    size_t count() { return LinkedListMetadata::numbers[start]; }

    bool hasMember(LinkedList *object);
    void iterateRight(CALLBACK callback);
    void iterateLeft(CALLBACK callback);
    void appoint(LinkedList *newStart);
    void detach();

    virtual void join(LinkedList *insider);
    virtual void accept(LinkedList *outsider);
    virtual void destroy();
    virtual void annihilate();
  };
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__