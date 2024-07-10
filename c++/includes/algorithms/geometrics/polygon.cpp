#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_CPP__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_CPP__

#include "polygon.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

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

  Point Polygon::getVertice(int index) {
    if (index >= 0 && index < vertices.size()) {
      return vertices.at(index);
    }
    else return Point(0, 0);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_CPP__