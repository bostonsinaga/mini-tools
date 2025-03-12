#ifndef __MINI_TOOLS__DATA_STRUCTURES__TREE_H__
#define __MINI_TOOLS__DATA_STRUCTURES__TREE_H__

#include "linked-list.h"

//____________|
// N-ARY TREE |
//____________|

namespace mini_tools {
namespace data_structures {

  class Tree;
  typedef std::vector<Tree*> VEC_TREE;
  typedef const VEC_TREE& CR_VEC_TREE;

  /**
   * You can inherit from this class to create
   * what is generally referred to as a Node.
   */
  class Tree : public LinkedList {
  private:
    void cleanDuplicateToLastAdded(Tree *tree);
    void cleanChildren();
    void destroy(CR_BOL firstOccurrence);
    void dismantleDestroy(CR_INT index);
    Tree* dismantleRelease(CR_INT index);

  protected:
    UI level = 0;
    VEC_TREE children;
    Tree *parent = nullptr;

    virtual void setChildren(
      CR_VEC_TREE newChildren,
      CR_BOL needEmpty,
      CR_BOL validating
    );

    virtual Tree* dismantle(CR_INT index);
    void cleanDuplicatesInChildren();
    void setLevel(CR_UI lv) { level = lv; }

    // destructor only invoked from 'remove' method
    ~Tree() {}

  public:
    Tree() {}

    Tree(
      CR_STR name_in,
      Tree *parent_in = nullptr
    );

    UI getLevel() { return level; }
    size_t getNumberOfChildren() { return children.size(); }

    bool hasChild(Tree *tree);
    bool hasChild(CR_STR searched);

    VEC_TREE getChildren() { return children; }
    Tree *getParent() { return parent; }

    Tree *getChild(CR_INT index);
    Tree *getChild(CR_STR searched);
    Tree *getRoot();

    VEC_TREE setChildrenRelease(
      CR_VEC_TREE newChildren,
      CR_BOL validating = true
    );

    void setChildrenReplace(
      CR_VEC_TREE newChildren,
      CR_BOL validating = true
    );

    void addChildren(
      CR_VEC_TREE newChildren,
      CR_BOL validating = true
    );

    virtual void addChild(
      Tree *tree,
      CR_BOL reconnected = true
    );

    void setParent(
      Tree *newParent,
      CR_BOL reconnected = true
    );

    void removeChild(Tree *tree);
    void removeChild(CR_INT index);

    Tree *releaseChild(Tree *tree);
    Tree *releaseChild(CR_INT index);

    virtual VEC_TREE releaseChildren();
    void remove() override { destroy(true); }
  };
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__TREE_H__