#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_H__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_H__

#include <vector>
#include "rect.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  class Polygon {
  private:
    Rect rect;
    std::vector<Point> vertices;
    void setRect();

  public:
    Polygon() {}

    Polygon(std::vector<Point> &points) {
      setVertices(&points);
    }

    Polygon(const std::vector<Point> &points) {
      setVertices(&points);
    }

    Polygon(
      std::vector<double> &vec_x,
      std::vector<double> &vec_y
    ) {
      setVertices(&vec_x, &vec_y);
    }

    Polygon(
      const std::vector<double> &vec_x,
      const std::vector<double> &vec_y
    ) {
      setVertices(&vec_x, &vec_y);
    }

    void setVertices(std::vector<Point> *points);

    void setVertices(
      std::vector<double> *vec_x,
      std::vector<double> *vec_y
    );
  };
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_H__