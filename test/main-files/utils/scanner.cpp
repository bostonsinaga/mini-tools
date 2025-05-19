#include "mini-tools.hpp"

int main(int argc, char *argv[]) {

  if (argc > 1) {
    mt::VEC_INT numbers = mt_uti::Scanner::txtToNumbers<int>(
      std::string(argv[1])
    );
  }

  return 0;
}

