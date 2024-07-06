#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__SIZE_H__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__SIZE_H__

#include "point.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  class Size : public Point {
  public:
    Size() : Point() {}
    Size(double &w_in, double &h_in) : Point(w_in, h_in) {}
    Size(const double &w_in, const double &h_in) : Point(w_in, h_in) {}
  };
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__SIZE_H__