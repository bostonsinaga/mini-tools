#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__RAY_CASTING_CPP__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__RAY_CASTING_CPP__

#include <cmath>
#include "ray-casting.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  bool RayCasting::checkInside(
    Point point,
    Polygon &polygon,
    double step
  ) {
    if (step <= 0 ||
      !polygon.getRect().contains(point)
    ) { return false; }

    int last = polygon.verticesCount() - 1,
        catchCount = 0;

    bool lastPair = false;
    std::vector<Point> laserIntersections;

    /** Load 'laserIntersections' */

    for (int i = 0; i < last; i++) {

      // next index
      int j;
      if (lastPair) { i = last; j = 0; }
      else j = i + 1;

      double gradient = polygon.getVertice(i).gradientTo(polygon.getVertice(j));
      if (gradient == 0) gradient = 1/1000000;

      laserIntersections.push_back(Point(
        point.Y() / gradient,
        point.Y()
      ));

      // back to first index once after last index
      if (lastPair) break;
      else if (i == last - 1) {
        lastPair = true;
        i = 0;
      }
    }

    /** Check 'laserIntersections' */

    for (int i = 0; i < laserIntersections.size(); i++) {
      for (
        double x = polygon.getFarMin().X();
        x <= point.X();
        x += step
      ) {
        if (Rect(
          laserIntersections[i],
          Size(step)
        ).contains(Point(x, point.Y()))) {
          catchCount++;
        }
      }
    }

    // even is outside
    if (catchCount % 2 == 0) return false;
    // uneven is inside
    return true;
  }

  bool RayCasting::checkInside(
    Point point,
    Polygon &&polygon,
    double step
  ) {
    return checkInside(point, polygon, step);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__RAY_CASTING_CPP_