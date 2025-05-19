#include "sorters-helper.hpp"

void sorters_helper::usePair(mt::VEC_PAIR2<int, std::string> &merged) {
  mt_alg::sorters::Selection<int, std::string>::solve(merged);
}

int main() {
  helper::call(
    sorters_helper::use4Vectors,
    "Selection Sort",
    "algorithms/sorters/selection.txt"
  );
}

