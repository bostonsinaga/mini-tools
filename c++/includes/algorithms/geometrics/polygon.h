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

    void createRect(Point *anc = nullptr);
    void setPosition(Point *pt);
    bool withinVertices(int index);
    bool isFarPoint(Point &pt);

    void setVertices(
      std::vector<Point> *points,
      Point *anc = nullptr
    );

    void setVertices(
      std::vector<double> *vec_x,
      std::vector<double> *vec_y,
      Point *anc = nullptr
    );

  public:
    Polygon() {}

    Polygon(
      std::vector<Point> &points,
      Point anc = Point(0.5, 0.5)
    ) {
      setVertices(&points, &anc);
    }

    Polygon(
      const std::vector<Point> &points,
      Point anc = Point(0.5, 0.5)
    ) {
      setVertices(&points, &anc);
    }

    Polygon(
      std::vector<double> &vec_x,
      std::vector<double> &vec_y,
      Point anc = Point(0.5, 0.5)
    ) {
      setVertices(&vec_x, &vec_y, &anc);
    }

    Polygon(
      const std::vector<double> &vec_x,
      const std::vector<double> &vec_y,
      Point anc = Point(0.5, 0.5)
    ) {
      setVertices(&vec_x, &vec_y, &anc);
    }

    /** RECT */

    void setPosition(Point &pt) { setPosition(&pt); }
    void setPosition(const Point &pt) { setPosition(&pt); }
    void setPosition(double x, double y) { setPosition(&x, &y); }

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
    Point cutVertices(int index);

    void setVertices(std::vector<Point> &points) {
      setVertices(&points);
    }

    void setVertices(const std::vector<Point> &points) {
      setVertices(&points);
    }

    void setVertices(
      std::vector<double> &vec_x,
      std::vector<double> &vec_y
    ) {
      setVertices(&vec_x, &vec_y);
    }

    void setVertices(
      const std::vector<double> &vec_x,
      const std::vector<double> &vec_y
    ) {
      setVertices(&vec_x, &vec_y);
    }

    std::vector<Point> cutVertices(int start, int end);
    std::vector<Point> cutVertices(std::vector<int> indexes);

    Point getVertice(int index);
    std::vector<Point> getVertices() { return vertices; }  // returns the copy
    int verticesCount() { return vertices.size(); }
  };
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POLYGON_H__