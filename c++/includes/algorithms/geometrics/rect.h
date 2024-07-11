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

    void Rect::init(
      Point *position_in,
      Size *size_in,
      Point *anchor_in
    );

    void Rect::init(
      double *x, double *y,
      double *w, double *h,
      double *anc_x, double *anc_y
    );

  public:
    Rect() {}

    Rect(
      Point position_in,
      Size size_in,
      Point anchor_in = Point(0.5, 0.5)
    ) {
      init(&position_in, &size_in, &anchor_in);
    }

    Rect(
      double x, double y,
      double w, double h,
      double anc_x = 0.5,
      double anc_y = 0.5
    ) {
      init(&x, &y, &w, &h, &anc_x, &anc_y);
    }

    /** VALUES */

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

    /** RELATIONS */

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