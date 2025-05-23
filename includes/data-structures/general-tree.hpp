#ifndef __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_HPP__
#define __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_HPP__

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
    ~GeneralTree() {}

  public:
    size_t getLevel() { return level; }
    size_t childrenCount();

    GT *getChildren() { return children; }
    bool hasChild(GT *child);

    void setParent(GT *object);
    void addChild(GT *object);
    void removeChild(GT *child);
    void movePointer(CR_INT direction);
    void resetPointer();
    void cleanChildren();
    void traverse(CR_BOL direction, CR_CALLBACK callback);
    void branch(CR_BOL direction, CR_CALLBACK condition);

    /** OVERRIDES */

    void join(LinkedList *object) override;
    void accept(LinkedList *object) override;
    void destroy() override;
    void annihilate() override;
  };
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__GENERAL_TREE_HPP__