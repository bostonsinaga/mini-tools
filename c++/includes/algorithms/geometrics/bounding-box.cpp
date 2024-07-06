#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_CPP__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_CPP__

#include "bounding-box.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  BoundingBox::BoundingBox(
    Point &position_in,
    Size &size_in
  ) {
    position = position_in;
    size = size_in;
  }

  BoundingBox::BoundingBox(
    const Point &position_in,
    const Size &size_in
  ) {
    position = position_in;
    size = size_in;
  }

  BoundingBox::BoundingBox(
    Point &position_in,
    Size &size_in,
    Point &anchor_in
  ) {
    position = position_in;
    size = size_in;
    anchor = anchor_in;
  }

  BoundingBox::BoundingBox(
    const Point &position_in,
    const Size &size_in,
    const Point &anchor_in
  ) {
    position = position_in;
    size = size_in;
    anchor = anchor_in;
  }

  BoundingBox::BoundingBox(
    double &x, double &y,
    double &w, double &h
  ) {
    position = Point(x, y);
    size = Size(w, h);
  }

  BoundingBox::BoundingBox(
    const double &x, const double &y,
    const double &w, const double &h
  ) {
    position = Point(x, y);
    size = Size(w, h);
  }

  /** Values */

  Point BoundingBox::getPosition() { return position; }
  Size BoundingBox::getSize() { return size; }
  Point BoundingBox::getAnchor() { return anchor; }

  void BoundingBox::setPosition(Point &pt) { position = pt; }
  void BoundingBox::setPosition(const Point &pt) { position = pt; }

  void BoundingBox::setSize(Size &sz) { size = az; }
  void BoundingBox::setSize(const Size &sz) { size = az; }

  void BoundingBox::setAnchor(Point &pt) { anchor = pt; }
  void BoundingBox::setAnchor(const Point &pt) { anchor = pt; }

  double BoundingBox::getLeft() { return position.x - size.w * anchor.x; }
  double BoundingBox::getRight() { return position.x + size.w * (1 - anchor.x); }
  double BoundingBox::getBottom() { return position.y - size.h * anchor.y; }
  double BoundingBox::getTop() { return position.y + size.h * (1 - anchor.y); }

  /** Relations */

  bool BoundingBox::contains(Point *pt) {
    if (pt->x >= getLeft() && pt->x <= getRight() &&
      pt->y >= getBottom() && pt->y <= getTop()
    ) { return true; }
    return false;
  }

  bool BoundingBox::contains(Point pt) {
    return contains(&pt);
  }

  bool BoundingBox::contains(BoundingBox *bb) {
    if (bb->getLeft() >= getLeft() &&
      bb->getRight() <= getRight() &&
      bb->getBottom() >= getBottom() &&
      bb->getTop() <= getTop()
    ) { return true; }
    return false;
  }

  bool BoundingBox::contains(BoundingBox bb) {
    return contains(&bb);
  }

  bool BoundingBox::inside(BoundingBox *bb) {
    if (getLeft() >= bb->getLeft() &&
      getRight() <= bb->getRight() &&
      getBottom() >= bb->getBottom() &&
      getTop() <= bb->getTop()
    ) { return true; }
    return false;
  }

  bool BoundingBox::inside(BoundingBox bb) {
    return inside(&bb);
  }

  bool BoundingBox::intersect(BoundingBox *bb) {
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

  bool BoundingBox::intersect(BoundingBox bb) {
    return intersect(&bb);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__BOUNDING_BOX_CPP__