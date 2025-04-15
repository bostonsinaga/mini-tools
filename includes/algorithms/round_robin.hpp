#ifndef __MINI_TOOLS__ALGORITHMS__ROUND_ROBIN_HPP__
#define __MINI_TOOLS__ALGORITHMS__ROUND_ROBIN_HPP__

namespace mini_tools {
namespace algorithms {

  class RoundRobin {
  public:
    template <inspector::NUMBER T>
    struct NumericTask {
      std::function<void(T&)> ongoing;
      std::function<void()> finish;
      T load;
    };

    template <typename T>
    struct VectorTask {
      std::function<void(VEC<T>&)> ongoing;
      std::function<void()> finish;
      VEC<T> load;
    };

    template <inspector::NUMBER T>
    static void arbitrateNumeric(
      std::queue<NumericTask<T>> &taskQueue,
      CR<T> valueLimit
    );

    template <typename T>
    static void arbitrateVector(
      std::queue<VectorTask<T>> &taskQueue,
      CR_SZ sizeLimit
    );
  };
}}

#include "algorithms/round-robin.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__ROUND_ROBIN_HPP__