#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_HPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_HPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  // this belongs to quick sort
  enum QUICK_SCHEME_ENUM {QUICK_HOARE, QUICK_LOMUTO};

  template <inspector::NUMBER T, class U>
  class Insertion {
  protected:
    static void process(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order,
      CR_INT start,
      CR_INT end
    );

  public:
    static void solve(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order = ORDER_ASCENDING
    );

  private:
    template <inspector::NUMBER, class, QUICK_SCHEME_ENUM>
    friend class Quick;
  };
}}}

#include "algorithms/sorters/insertion.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_HPP__