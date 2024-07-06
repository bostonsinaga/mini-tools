#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_H__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_H__

#include "point.h"
#include "size.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  class BoundingBox {
  private:
    Point position, anchor = Point(0.5, 0.5);
    Size size;

  public:
    BoundingBox() {}

    BoundingBox(
      Point &position_in,
      Size &size_in
    );

    BoundingBox(
      const Point &position_in,
      const Size &size_in
    );

    BoundingBox(
      Point &position_in,
      Size &size_in,
      Point &anchor_in
    );

    BoundingBox(
      const Point &position_in,
      const Size &size_in,
      const Point &anchor_in
    );

    BoundingBox(
      double &x, double &y,
      double &w, double &h
    );

    BoundingBox(
      const double &x, const double &y,
      const double &w, const double &h
    );

    /** Values */

    Point getPosition();
    Size getSize();
    Point getAnchor();

    void setPosition(Point &pt);
    void setPosition(const Point &pt);

    void setSize(Size &sz);
    void setSize(const Size &sz);

    void setAnchor(Point &pt);
    void setAnchor(const Point &pt);

    double getLeft();
    double getRight();
    double getBottom();
    double getTop();

    /** Relations */

    bool contains(Point *pt);
    bool contains(Point pt);
    bool contains(BoundingBox *bb);
    bool contains(BoundingBox bb);

    bool inside(BoundingBox *bb);
    bool inside(BoundingBox bb);

    bool intersect(BoundingBox *bb);
    bool intersect(BoundingBox bb);
  };
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_H__