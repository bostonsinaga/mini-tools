#ifndef __MINI_TOOLS__DATA_STRUCTURES__TREE_H__
#define __MINI_TOOLS__DATA_STRUCTURES__TREE_H__

#include "linked-list.h"

namespace mini_tools {
namespace data_structures {
namespace tree {

  class Node;
  typedef std::vector<Node*> VEC_NODE;
  typedef const VEC_NODE& CR_VEC_NODE;

  class Node : public linked_list::Node {
  private:
    void cleanDuplicateToLastAdded(Node *node);
    void cleanChildren();
    void destroy(CR_BOL firstOccurrence);

    void setChildren(
      CR_VEC_NODE newChildren,
      CR_BOL needEmpty,
      CR_BOL validating
    );

    Node* dismantle(CR_INT index);
    void dismantleDestroy(CR_INT index);
    Node* dismantleRelease(CR_INT index);

  protected:
    UI level = 0;
    VEC_NODE children;
    Node *parent = nullptr;

    void cleanDuplicatesInChildren();
    void setLevel(CR_UI lv) { level = lv; }

    // destructor only invoked from 'remove' method
    ~Node() {}

  public:
    Node() {}

    Node(
      CR_STR name_in,
      Node *parent_in = nullptr
    );

    UI getLevel() { return level; }
    size_t getNumberOfChildren() { return children.size(); }

    bool hasChild(Node *node);
    bool hasChild(CR_STR searched);

    VEC_NODE getChildren() { return children; }
    Node *getParent() { return parent; }

    Node *getChild(CR_INT index);
    Node *getChild(CR_STR searched);
    Node *getRoot();

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

    void addChild(
      Node *node,
      CR_BOL reconnected = true
    );

    void setParent(
      Node *newParent,
      CR_BOL reconnected = true
    );

    void removeChild(Node *node);
    void removeChild(CR_INT index);

    Node *releaseChild(Node *node);
    Node *releaseChild(CR_INT index);

    VEC_NODE releaseChildren();
    void remove() override { destroy(true); }
  };
}}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__TREE_H__