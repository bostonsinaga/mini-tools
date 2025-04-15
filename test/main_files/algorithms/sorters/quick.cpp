#include "sorters_helper.h"

void sorters_helper::usePair(mt::VEC_PAIR2<int, std::string> &merged) {
  mt_alg::sorters::Quick<int, std::string>::solve(merged);
}

int main() {
  helper::call(
    sorters_helper::use4Vectors,
    "Quick Sort",
    "algorithms/sorters/quick.txt"
  );
}

