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

    static void add(LinkedList *leader) {
      numbers[leader] = 1;
      iteratings[leader] = false;
      existences[leader][leader] = true;
    }

    static void addTo(
      LinkedList *leader,
      LinkedList *follower
    ) {
      numbers[leader]++;
      existences[leader][follower] = true;
    }

    static void remove(LinkedList *leader) {
      numbers.erase(leader);
      iteratings.erase(leader);
      existences.erase(leader);
    }

    static void removeFrom(
      LinkedList *leader,
      LinkedList *follower
    ) {
      numbers[leader]--;
      existences[leader].erase(follower);
    }

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
    ) {
      if ((ascending && !right) ||
        (!ascending && !left)
      ) {
        callback(this);
        return;
      }

      LinkedList *current,
        *buffer = nullptr,
        *stop = this;

      if (ascending) current = right;
      else current = left;

      callback(this);
      LinkedListMetadata::iteratings[start] = true;

      if (ascending) while (current && current != stop) {
        if (!callback(current)) break;
        current = current->right;
      }
      else while (current && current != stop) {
        if (!callback(current)) break;
        current = current->left;
      }

      LinkedListMetadata::iteratings[start] = false;
    }

    void xjoin(LinkedList *insider) {
      xdetach();
      start = insider->start;
      left = insider;

      if (insider->right) {
        right = insider->right;
        insider->right->left = this;
      }
      else {
        right = insider;
        insider->left = this;
      }

      left = insider;
      insider->right = this;
      LinkedListMetadata::addTo(start, this);
    }

    void xaccept(LinkedList *outsider) {
      outsider->xjoin(this);
    }

    void xdetach() {
      if (right) {
        LinkedListMetadata::removeFrom(start, this);
        left->right = right;
        right->left = left;
      }
    }

    friend class GeneralTree;

  protected:
    ~LinkedList() {}

  public:
    LinkedList() {
      start = this;
      LinkedListMetadata::add(this);
    }

    LinkedList *head() { return start; }
    LinkedList *tail() { return start->left; }
    LinkedList *next() { return right; }
    LinkedList *prev() { return left; }

    bool isolated() const { return !right; }
    bool front() const { return this == start; }
    bool back() const { return this == start->left; }
    size_t count() const { return LinkedListMetadata::numbers[start]; }

    bool hasMember(LinkedList *object) {
      return LinkedListMetadata::existences[start][object];
    }

    void iterateRight(CALLBACK callback) {
      iterate(callback, true);
    }

    void iterateLeft(CALLBACK callback) {
      iterate(callback, false);
    }

    LinkedList *slice() {
      return start;
    }

    void detach() {
      if (right) {
        LinkedListMetadata::removeFrom(start, this);
        left->right = right;
        right->left = left;
  
        LinkedListMetadata::add(this);
        start = this;
        left = nullptr;
        right = nullptr;
      }
    }

    virtual void join(LinkedList *insider) {
      if (insider) xjoin(insider);
    }

    virtual void accept(LinkedList *outsider) {
      if (outsider) xaccept(outsider);
    }

    virtual void destroy() {
      if (!LinkedListMetadata::iteratings[start]) {

        xdetach();
        LinkedListMetadata::remove(this);

        delete this;
      }
    }

    virtual void annihilate() {
      if (!LinkedListMetadata::iteratings[start]) {

        LinkedListMetadata::remove(start);
        LinkedList *current = right;

        while (current && current != this) {
          current->destroy();
          current = current->right;
        }
      }

      destroy();
    }
  };
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__LINKED_LIST_HPP__