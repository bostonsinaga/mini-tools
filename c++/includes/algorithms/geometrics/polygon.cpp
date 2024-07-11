#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_CPP__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_CPP__

#include "polygon.h"
#include "../../utils/vec-tools.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {
  //______|
  // RECT |
  //______|

  void Polygon::createRect() {
    for (Point &pt : vertices) {

      if (std::abs(pt.x) < farMin.x) {
        farMin.x = pt.x;
      }
      else if (std::abs(pt.x) > farMax.x) {
        farMax.x = pt.x;
      }

      if (std::abs(pt.y) < farMin.y) {
        farMin.y = pt.y;
      }
      else if (std::abs(pt.y) > farMax.y) {
        farMax.y = pt.y;
      }
    }

    rect = Rect(
      (farMin.x + farMax.x) / 2,
      (farMin.y + farMax.y) / 2,
      std::abs(farMin.x - farMax.x),
      std::abs(farMin.y - farMax.y)
    );
  }

  void Polygon::setPosition(Point *pt) {
    Point diff = *pt - rect.getPosition();
    rect.setPosition(*pt);
    for (Point &v : vertices) v += dif;
  }

  void Polygon::setPosition(double x, double y) {
    Pont pt = Point(x, y);
    setPosition(&pt);
  }

  //_________|
  //VERTICES |
  //_________|

  bool Polygon::withinVertices(int index) {
    if (index >= 0 && index < vertices.size()) {
      return true;
    }
    else return false;
  }

  void Polygon::editVertices(int index, double val) {
    if (withinVertices(index)) {
      vertices.at(index) = val;
    }
  }

  void Polygon::setVertices(std::vector<Point> *points) {
    vertices = *points;
    createRect();
  }

  void Polygon::setVertices(
    std::vector<double> *vec_x,
    std::vector<double> *vec_y
  ) {
    int size = vec_x->size();
    if (vec_y->size() < size) size = vec_y->size();
    vertices = {};
    
    for (int i = 0; i < size; i++) {
      vertices.push_back(
        Point(vec_x->at(i), vec_y->at(i))
      );
    }

    createRect();
  }

  Point Polygon::cutVertices(int index) {
    Point wasted;
    int prevCount = count();
    utils::VecTools::cutSingle(vertices, wasted, index);
    if (count() < prevCount) createRect();
    return wasted;
  }

  std::vector<Point> Polygon::cutVertices(int start, int end) {
    std::vector<Point> wasted;
    utils::VecTools::cutInterval(vertices, wasted, start, end);
    if (wasted.size() > 0) createRect();
    return wasted;
  }

  std::vector<Point> Polygon::cutVertices(std::vector<int> indexes) {
    std::vector<Point> wasted;
    utils::VecTools::cutIndexes(vertices, wasted, indexes);
    if (wasted.size() > 0) createRect();
    return wasted;
  }

  Point Polygon::getVertice(int index) {
    if (withinVertices(index)) {
      return vertices.at(index);
    }
    else return Point(0, 0);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_CPP__