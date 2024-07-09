#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_CPP__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_CPP__

#include "polygon.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  void Polygon::createRect() {
    double farX[2] = {0, 0}, farY[2] = {0, 0};

    for (Point &pt : vertices) {

      if (std::abs(pt.x) < farX[0]) {
        farX[0] = pt.x;
      }
      else if (std::abs(pt.x) > farX[1]) {
        farX[1] = pt.x;
      }

      if (std::abs(pt.y) < farY[0]) {
        farY[0] = pt.y;
      }
      else if (std::abs(pt.y) > farY[1]) {
        farY[1] = pt.y;
      }
    }

    rect = Rect(
      (farX[0] + farX[1]) / 2,
      (farY[0] + farY[1]) / 2,
      std::abs(farX[0] - farX[1]),
      std::abs(farY[0] - farY[1])
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