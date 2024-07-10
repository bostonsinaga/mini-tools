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
    Point farMin, farMax;
    bool withinVertices(int index);

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

    void createRect();
    void editVertices(int index, double val);
    void setVertices(std::vector<Point> *points);

    void setVertices(
      std::vector<double> *vec_x,
      std::vector<double> *vec_y
    );

    Point cutVertices(int index);
    std::vector<Point> cutVertices(int start, int end);
    std::vector<Point> cutVertices(std::vector<int> indexes);

    Point getVertice(int index);
    int count() { return vertices.size(); }

    std::vector<Point> getVertices() { return vertices; }
    Rect getRect() { return rect; }

    double getFarMin() { return farMin; }
    double getFarMin() { return farMax; }
  };
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_H__