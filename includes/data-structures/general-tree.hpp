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
    size_t level = 0;

    GeneralTree *parent = nullptr,
      *children = nullptr;

    void xsetParent(GeneralTree *object);
    void xaddChild(GeneralTree *object);
    void xannihilate();

  public:
    size_t getLevel() { return level; }
    size_t numberOfChildren();

    GeneralTree *getRoot();
    GeneralTree *getParent() { return parent; }
    GeneralTree *getChildren() { return children; }
    bool hasChild(GeneralTree *child);

    virtual void setParent(GeneralTree *object);
    virtual void addChild(GeneralTree *object);
    virtual void removeChild(GeneralTree *child);
    virtual void releaseChild(GeneralTree *child);
    virtual void cleanChildren();

    // change 'children' address to 'children->start'
    virtual void resetPointer();

    /**
     * Move left or right by a number of steps
     * to select a linked list node (the children).
     */
    virtual void movePointer(CR_INT steps);

    // iterate through child nodes until reaching the leaves
    virtual void traverse(
      const Callback &callback,
      const DIRECTION &direction = RIGHT
    );

    // iterate from here to the root without visiting neighbors
    virtual void bubble(const Callback &callback);

    /** Override behavior through parent-child relationship configuration */

    void detach() override;
    void join(LinkedList *object) override;
    void accept(LinkedList *object) override;

    // delete this and its children vertically and horizontally
    void destroy() override;

    // delete this and the neighbors vertically and horizontally
    void annihilate() override;
  };
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_HPP__