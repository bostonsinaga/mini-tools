#ifndef __MINI_TOOLS__ALGORITHMS__GEOMETRICS__SIZE_H__
#define __MINI_TOOLS__ALGORITHMS__GEOMETRICS__SIZE_H__

#include "point.h"

namespace mini_tools {
namespace algorithms {
namespace geometrics {

  class Size : public Point {
  private:
    double *w, *h;
    void init() { w = &x; h = &y; }

  public:
    double W() { return *w; }
    double H() { return *h; }
    void W(double val) { *w = val; }
    void H(double val) { *h = val; }

    Size() : Point() { init(); }
    Size(double side) : Point(side, side) { init(); }
    Size(double w_in, double h_in) : Point(w_in, h_in) { init(); }
  };
}}}

#endif // __MINI_TOOLS__ALGORITHMS__GEOMETRICS__SIZE_H__