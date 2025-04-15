#include "helper.hpp"

namespace sorters_helper {

  void usePair(mt::VEC_PAIR2<int, std::string> &merged);

  helper::TUP4PTR use4Vectors(
    mt::VEC_INT &integers,
    mt::VEC_DBL &reals,
    mt::VEC_STR &letters,
    mt::VEC_STR &words
  ) {
    mt::VEC_PAIR2<int, std::string> merged
      = mt_uti::PairTools<int, std::string>::mergeVectors(integers, letters);

    usePair(merged);

    mt_uti::PairTools<int, std::string>::unmergeVectors(
      merged, integers, letters, true
    );

    return std::make_tuple(
      &integers, nullptr, &letters, nullptr
    );
  }
}

