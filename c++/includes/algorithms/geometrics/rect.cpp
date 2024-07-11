#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_CPP__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_CPP__

#include "bounding-box.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  void Rect::init(
    Point *position_in,
    Size *size_in,
    Point *anchor_in
  ) {
    position = *position_in;
    size = *size_in;
    if (anchor_in) anchor = *anchor_in;
  }

  void Rect::init(
    double *x, double *y,
    double *w, double *h,
    double *anc_x, double *anc_y
  ) {
    position = Point(*x, *y);
    size = Size(*w, *h);
    if (anc_x && anc_y) anchor = Point(*anc_x, *anc_y);
  }

  /** VALUES */

  Point Rect::getPosition() { return position; }
  Size Rect::getSize() { return size; }
  Point Rect::getAnchor() { return anchor; }

  void Rect::setPosition(Point &pt) { position = pt; }
  void Rect::setPosition(const Point &pt) { position = pt; }

  void Rect::setSize(Size &sz) { size = az; }
  void Rect::setSize(const Size &sz) { size = az; }

  void Rect::setAnchor(Point &pt) { anchor = pt; }
  void Rect::setAnchor(const Point &pt) { anchor = pt; }

  double Rect::getLeft() { return position.x - size.w * anchor.x; }
  double Rect::getRight() { return position.x + size.w * (1 - anchor.x); }
  double Rect::getBottom() { return position.y - size.h * anchor.y; }
  double Rect::getTop() { return position.y + size.h * (1 - anchor.y); }

  /** RELATIONS */

  bool Rect::contains(Point *pt) {
    if (pt->x >= getLeft() && pt->x <= getRight() &&
      pt->y >= getBottom() && pt->y <= getTop()
    ) { return true; }
    return false;
  }

  bool Rect::contains(Point pt) {
    return contains(&pt);
  }

  bool Rect::contains(Rect *bb) {
    if (bb->getLeft() >= getLeft() &&
      bb->getRight() <= getRight() &&
      bb->getBottom() >= getBottom() &&
      bb->getTop() <= getTop()
    ) { return true; }
    return false;
  }

  bool Rect::contains(Rect bb) {
    return contains(&bb);
  }

  bool Rect::inside(Rect *bb) {
    if (getLeft() >= bb->getLeft() &&
      getRight() <= bb->getRight() &&
      getBottom() >= bb->getBottom() &&
      getTop() <= bb->getTop()
    ) { return true; }
    return false;
  }

  bool Rect::inside(Rect bb) {
    return inside(&bb);
  }

  bool Rect::intersect(Rect *bb) {
    if ((
      (getLeft() >= bb->getLeft() &&
      getLeft() <= bb->getRight()) ||
      (getRight() >= bb->getLeft() &&
      getRight() <= bb->getRight())
    ) && (
      (getBottom() >= bb->getBottom() &&
      getBottom() <= bb->getTop()) ||
      (getTop() >= bb->getBottom() &&
      getTop() <= bb->getTop())
    )) {
      return true;
    }
    return false;
  }

  bool Rect::intersect(Rect bb) {
    return intersect(&bb);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_CPP__