#ifndef __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_HPP__
#define __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_HPP__

#include "types.hpp"
#include "data-structures/linked-list.hpp"

namespace mini_tools {
namespace data_structures {

  /**
   * You can inherit from this class to create
   * what is generally referred to as a Node.
   */
  class GeneralTree : public LinkedList {
  private:
    typedef GeneralTree GT;
    size_t level = 0;

    GT *parent = nullptr,
      *children = nullptr;

    void xsetParent(GT *object);
    void xaddChild(GT *object);

  protected:
    ~GeneralTree() = default;

  public:
    size_t getLevel() { return level; }
    size_t numberOfChildren();

    GT *getParent() { return parent; }
    GT *getChildren() { return children; }
    bool hasChild(GT *child);

    void setParent(GT *object);
    void addChild(GT *object);
    void removeChild(GT *child);
    void cleanChildren();
    void resetPointer();

    /**
     * Move left or right by a number of steps
     * to select a linked list node.
     */
    void movePointer(CR_INT steps);

    /** Iterate through child nodes until reaching the leaves */

    void traverse(
      const DIRECTION &direction,
      const LinkedListCallback &callback
    );

    void branch(
      const DIRECTION &direction,
      const LinkedListCallback &callback
    );

    /** Override behavior through parent-child relationship configuration */

    void join(LinkedList *object) override;
    void accept(LinkedList *object) override;
    void destroy() override;
    void annihilate() override;
  };
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_HPP__