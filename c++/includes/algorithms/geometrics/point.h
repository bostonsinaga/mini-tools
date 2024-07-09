#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POINT_H__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POINT_H__

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  class Point {
  public:
    double x = 0, y = 0;
    double& w = 0, h = 0;

    Point() {}
    Point(double &num);
    Point(const double &num);
    Point(double &x_in, double &y_in);
    Point(const double &x_in, const double &y_in);

    /** Gradient */
    double gradient();
    double gradientTo(Point &pt);
    double gradientTo(const Point &pt);

    /** Hypotenuse */
    double hypotenuseZero();
    double hypotenuseTo(Point &pt);
    double hypotenuseTo(const Point &pt);

    /** Operator '+' */
    Point operator+(Point &pt);
    Point operator+(const Point &pt);
    Point operator+(double &num);
    Point operator+(const double &num);

    /** Operator '-' */
    Point operator-(Point &pt);
    Point operator-(const Point &pt);
    Point operator-(double &num);
    Point operator-(const double &num);

    /** Operator '*' */
    Point operator*(Point &pt);
    Point operator*(const Point &pt);
    Point operator*(double &num);
    Point operator*(const double &num);

    /** Operator '/' */
    Point operator/(Point &pt);
    Point operator/(const Point &pt);
    Point operator/(double &num);
    Point operator/(const double &num);

    /** Operator '+=' */
    Point operator+=(Point &pt);
    Point operator+=(const Point &pt);
    Point operator+=(double &num);
    Point operator+=(const double &num);

    /** Operator '-=' */
    Point operator-=(Point &pt);
    Point operator-=(const Point &pt);
    Point operator-=(double &num);
    Point operator-=(const double &num);

    /** Operator '*=' */
    Point operator*=(Point &pt);
    Point operator*=(const Point &pt);
    Point operator*=(double &num);
    Point operator*=(const double &num);

    /** Operator '/=' */
    Point operator/=(Point &pt);
    Point operator/=(const Point &pt);
    Point operator/=(double &num);
    Point operator/=(const double &num);

    /** Operator '==' */
    Point operator==(Point &pt);
    Point operator==(const Point &pt);
    Point operator==(double &num);
    Point operator==(const double &num);

    /** Operator '<' */
    Point operator<(Point &pt);
    Point operator<(const Point &pt);
    Point operator<(double &num);
    Point operator<(const double &num);

    /** Operator '<=' */
    Point operator<=(Point &pt);
    Point operator<=(const Point &pt);
    Point operator<=(double &num);
    Point operator<=(const double &num);

    /** Operator '>' */
    Point operator>(Point &pt);
    Point operator>(const Point &pt);
    Point operator>(double &num);
    Point operator>(const double &num);

    /** Operator '>=' */
    Point operator>=(Point &pt);
    Point operator>=(const Point &pt);
    Point operator>=(double &num);
    Point operator>=(const double &num);

  private:
    Point divideCopy(Point *pt);
    Point divideCopy(double *num);
    void divideSelf(Point *pt);
    void divideSelf(double *num);
  };
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__POINT_H__