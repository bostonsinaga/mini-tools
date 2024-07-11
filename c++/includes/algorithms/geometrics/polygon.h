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
    void setPosition(Point *pt);

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

    /** RECT */

    void createRect();

    void setPosition(Point &pt) { setPosition(&pt); }
    void setPosition(const Point &pt) { setPosition(&pt); }
    void setPosition(double x, double y);

    void setAnchor(Point &pt) { rect.setAnchor(pt); }
    void setAnchor(const Point &pt) { rect.setAnchor(pt); }
    void setAnchor(double x, double y) { rect.setAnchor(Point(x, y)); }

    Point getPosition() { return rect.getPosition(); }
    Point getAnchor() { return rect.getAnchor(); }
    Size getSize() { return rect.getSize(); }

    Rect getRect() { return rect; }  // returns the copy
    Point getFarMin() { return farMin; }
    Point getFarMax() { return farMax; }

    /** VERTICES */

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
    std::vector<Point> getVertices() { return vertices; }  // returns the copy
    int verticesCount() { return vertices.size(); }
  };
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_H__