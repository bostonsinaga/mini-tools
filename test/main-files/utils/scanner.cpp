#include "mini_tools.hpp"
// #include "helper.h"

int main(int argc, char *argv[]) {
  // mt::VEC_STR filenames = helper::charsToStrings(argv, argc);

  if (argc > 1) {
    mt::VEC_INT numbers = mt_uti::Scanner::txtToNumbers<int>(
      std::string(argv[1])
    );
  }
}

