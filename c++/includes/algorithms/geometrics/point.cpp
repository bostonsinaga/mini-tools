#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POINT_CPP__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POINT_CPP__

#include <cmath>
#include "point.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  /** Constructors */

  Point::Point(double &x_in, double &y_in) {
    x = x_in;
    y = y_in;
  }

  Point::Point(const double &x_in, const double &y_in) {
    x = x_in;
    y = y_in;
  }

  /** Gradient */

  double Point::gradient() {
    if (x == 0) return DBL_MAX * y / std::abs(y);
    return y / x;
  }

  double Point::gradientTo(Point &pt) {
    double h = y - pt.y;
    if (x - pt.x == 0) return DBL_MAX * h / std::abs(h);
    return h / (x - pt.x);
  }

  double Point::gradientTo(const Point &pt) {
    double h = y - pt.y;
    if (x - pt.x == 0) return DBL_MAX * h / std::abs(h);
    return h / (x - pt.x);
  }

  /** Hypotenuse */

  double Point::hypotenuseZero() {
    return std::sqrt(x * x + y * y);
  }

  double Point::hypotenuseTo(Point &pt) {
    return std::sqrt(
      std::pow(x - pt.x, 2) +
      std::pow(y - pt.y, 2)
    );
  }

  double Point::hypotenuseTo(const Point &pt) {
    return std::sqrt(
      std::pow(x - pt.x, 2) +
      std::pow(y - pt.y, 2)
    );
  }

  /** Operator '+' */

  Point Point::operator+(Point &pt) {
    return Point(x + pt.x, y + pt.y);
  }

  Point Point::operator+(const Point &pt) {
    return Point(x + pt.x, y + pt.y);
  }

  Point Point::operator+(double &num) {
    return Point(x + num, y + num);
  }

  Point Point::operator+(const double &num) {
    return Point(x + num, y + num);
  }

  /** Operator '-' */

  Point Point::operator-(Point &pt) {
    return Point(x - pt.x, y - pt.y);
  }

  Point Point::operator-(const Point &pt) {
    return Point(x - pt.x, y - pt.y);
  }

  Point Point::operator-(double &num) {
    return Point(x - num, y - num);
  }

  Point Point::operator-(const double &num) {
    return Point(x - num, y - num);
  }

  /** Operator '*' */

  Point Point::operator*(Point &pt) {
    return Point(x * pt.x, y * pt.y);
  }

  Point Point::operator*(const Point &pt) {
    return Point(x * pt.x, y * pt.y);
  }
  
  Point Point::operator*(double &num) {
    return Point(x * num, y * num);
  }

  Point Point::operator*(const double &num) {
    return Point(x * num, y * num);
  }

  /** Operator '/' */

  Point Point::divideCopy(Point *pt) {
    Point newPt;
    bool anyZero[2] = {false, false};

    if (pt->x == 0) {
      newPt.x = DBL_MAX;
      anyZero[0] = true;
    }

    if (pt->y == 0) {
      newPt.y = DBL_MAX;
      anyZero[1] = true;
    }
    
    if (!anyZero[0]) newPt.x = x / pt->x;
    if (!anyZero[1]) newPt.y = y / pt->y;
  }

  Point Point::divideCopy(double *num) {
    Point tempPt(num, num);
    return divideCopy(&tempPt);
  }

  Point Point::operator/(Point &pt) {
    return divideCopy(&pt);
  }

  Point Point::operator/(const Point &pt) {
    return divideCopy(&pt);
  }

  Point Point::operator/(double &num) {
    return divideCopy(&num);
  }

  Point Point::operator/(const double &num) {
    return divideCopy(&num);
  }

  /** Operator '+=' */

  void Point::operator+=(Point &pt) {
    x += pt.x; y += pt.y;
  }

  void Point::operator+=(const Point &pt) {
    x += pt.x; y += pt.y;
  }

  void Point::operator+=(double &num) {
    x += pt.x; y += pt.y;
  }

  void Point::operator+=(const double &num) {
    x += pt.x; y += pt.y;
  }

  /** Operator '-=' */

  void Point::operator-=(Point &pt) {
    x -= pt.x; y -= pt.y;
  }

  void Point::operator-=(const Point &pt) {
    x -= pt.x; y -= pt.y;
  }

  void Point::operator-=(double &num) {
    x -= num; y -= num;
  }

  void Point::operator-=(const double &num) {
    x -= num; y -= num;
  }

  /** Operator '*=' */

  void Point::operator*=(Point &pt) {
    x *= pt.x; y *= pt.y;
  }

  void Point::operator*=(const Point &pt) {
    x *= pt.x; y *= pt.y;
  }

  void Point::operator*=(double &num) {
    x *= num; y *= num;
  }

  void Point::operator*=(const double &num) {
    x *= num; y *= num;
  }

  /** Operator '/=' */

  void Point::divideSelf(Point *pt) {
    bool anyZero[2] = {false, false};

    if (pt->x == 0) {
      x = DBL_MAX;
      anyZero[0] = true;
    }

    if (pt->y == 0) {
      y = DBL_MAX;
      anyZero[1] = true;
    }
    
    if (!anyZero[0]) x /= pt->x;
    if (!anyZero[1]) y /= pt->y;
  }

  void Point::divideSelf(double *num) {
    Point tempPt(num, num);
    divideSelf(tempPt);
  }

  void Point::operator/=(Point &pt) {
    divideSelf(&pt);
  }

  void Point::operator/=(const Point &pt) {
    divideSelf(&pt);
  }

  void Point::operator/=(double &num) {
    divideSelf(&num);
  }

  void Point::operator/=(const double &num) {
    divideSelf(&num);
  }

  /** Operator '==' */

  Point Point::operator==(Point &pt) {
    return x == pt.x && y == pt.y;
  }

  Point Point::operator==(const Point &pt) {
    return x == pt.x && y == pt.y;
  }

  Point Point::operator==(double &num) {
    return x == num && y == num;
  }

  Point Point::operator==(const double &num) {
    return x == num && y == num;
  }

  /** Operator '<' */

  Point Point::operator<(Point &pt) {
    return x < pt.x && y < pt.y;
  }

  Point Point::operator<(const Point &pt) {
    return x < pt.x && y < pt.y;
  }

  Point Point::operator<(double &num) {
    return x < num && y < num;
  }

  Point Point::operator<(const double &num) {
    return x < num && y < num;
  }

  /** Operator '<=' */

  Point Point::operator<=(Point &pt) {
    return x <= pt.x && y <= pt.y;
  }

  Point Point::operator<=(const Point &pt) {
    return x <= pt.x && y <= pt.y;
  }

  Point Point::operator<=(double &num) {
    return x <= num && y <= num;
  }

  Point Point::operator<=(const double &num) {
    return x <= num && y <= num;
  }

  /** Operator '>' */

  Point Point::operator>(Point &pt) {
    return x > pt.x && y > pt.y;
  }

  Point Point::operator>(const Point &pt) {
    return x > pt.x && y > pt.y;
  }

  Point Point::operator>(double &num) {
    return x > num && y > num;
  }

  Point Point::operator>(const double &num) {
    return x > num && y > num;
  }

  /** Operator '>=' */

  Point Point::operator>=(Point &pt) {
    return x >= pt.x && y >= pt.y;
  }

  Point Point::operator>=(const Point &pt) {
    return x >= pt.x && y >= pt.y;
  }

  Point Point::operator>=(double &num) {
    return x >= num && y >= num;
  }

  Point Point::operator>=(const double &num) {
    return x >= num && y >= num;
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POINT_CPP__