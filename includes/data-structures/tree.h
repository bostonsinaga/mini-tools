#ifndef __MINI_TOOLS__DATA_STRUCTURES__TREE_H__
#define __MINI_TOOLS__DATA_STRUCTURES__TREE_H__

#include "linked-list.h"

//____________|
// N-ARY TREE |
//____________|

namespace mini_tools {
namespace data_structures {

  class Tree;
  typedef std::vector<Tree*> VEC_NODE;
  typedef const VEC_NODE& CR_VEC_NODE;

  class Tree : public LinkedList {
  private:
    void cleanDuplicateToLastAdded(Tree *node);
    void cleanChildren();
    void destroy(CR_BOL firstOccurrence);
    void dismantleDestroy(CR_INT index);
    Tree* dismantleRelease(CR_INT index);

  protected:
    UI level = 0;
    VEC_NODE children;
    Tree *parent = nullptr;

    virtual void setChildren(
      CR_VEC_NODE newChildren,
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

    bool hasChild(Tree *node);
    bool hasChild(CR_STR searched);

    VEC_NODE getChildren() { return children; }
    Tree *getParent() { return parent; }

    Tree *getChild(CR_INT index);
    Tree *getChild(CR_STR searched);
    Tree *getRoot();

    VEC_NODE setChildrenRelease(
      CR_VEC_NODE newChildren,
      CR_BOL validating = true
    );

    void setChildrenReplace(
      CR_VEC_NODE newChildren,
      CR_BOL validating = true
    );

    void addChildren(
      CR_VEC_NODE newChildren,
      CR_BOL validating = true
    );

    virtual void addChild(
      Tree *node,
      CR_BOL reconnected = true
    );

    void setParent(
      Tree *newParent,
      CR_BOL reconnected = true
    );

    void removeChild(Tree *node);
    void removeChild(CR_INT index);

    Tree *releaseChild(Tree *node);
    Tree *releaseChild(CR_INT index);

    virtual VEC_NODE releaseChildren();
    void remove() override { destroy(true); }
  };
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__TREE_H__