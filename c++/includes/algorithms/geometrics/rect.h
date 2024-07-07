#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_H__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_H__

#include "size.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  class Rect {
  private:
    Point position, anchor = Point(0.5, 0.5);
    Size size;

  public:
    Rect() {}

    Rect(
      Point &position_in,
      Size &size_in
    );

    Rect(
      const Point &position_in,
      const Size &size_in
    );

    Rect(
      Point &position_in,
      Size &size_in,
      Point &anchor_in
    );

    Rect(
      const Point &position_in,
      const Size &size_in,
      const Point &anchor_in
    );

    Rect(
      double &x, double &y,
      double &w, double &h
    );

    Rect(
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
    bool contains(Rect *bb);
    bool contains(Rect bb);

    bool inside(Rect *bb);
    bool inside(Rect bb);

    bool intersect(Rect *bb);
    bool intersect(Rect bb);
  };
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_H__