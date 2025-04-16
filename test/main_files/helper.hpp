#include "mini_tools.hpp"

namespace helper {

  typedef std::tuple<
    mt::VEC_INT*, mt::VEC_DBL*,
    mt::VEC_STR*, mt::VEC_STR*
  > TUP4PTR;

  void call(
    std::function<TUP4PTR(mt::VEC_INT&, mt::VEC_DBL&, mt::VEC_STR&, mt::VEC_STR&)> callback,
    mt::CR_STR timerTitle,
    mt::CR_STR logFilePath
  ) {
    mt::FS_PATH testPath = mt_uti::Scanner::findDirectory("test", true);

    mt::VEC_INT integers = mt_uti::Scanner::txtToNumbers<int>(
      testPath / "samples/integers.txt"
    );

    mt::VEC_DBL reals = mt_uti::Scanner::txtToNumbers<double>(
      testPath / "samples/reals.txt"
    );

    mt::VEC_STR letters = mt_uti::Scanner::txtToLetters<std::string>(
      testPath / "samples/letters.txt"
    );

    mt::VEC_STR words = mt_uti::Scanner::txtToLetters<std::string>(
      testPath / "samples/words.txt"
    );

    TUP4PTR toPrint = callback(
      integers, reals, letters, words
    );

    const mt::FS_PATH
      completeLogFilePath = testPath / "logs" / logFilePath;

    // integers
    if (std::get<0>(toPrint)) {
      mt_uti::Printer::logf<int>(
        *std::get<0>(toPrint), completeLogFilePath, false
      );
    }

    // reals
    if (std::get<1>(toPrint)) {
      mt_uti::Printer::logf<double>(
        *std::get<1>(toPrint), completeLogFilePath, false
      );
    }

    // letters
    if (std::get<2>(toPrint)) {
      mt_uti::Printer::logf<std::string>(
        *std::get<2>(toPrint), completeLogFilePath, false
      );
    }

    // words
    if (std::get<3>(toPrint)) {
      mt_uti::Printer::logf<std::string>(
        *std::get<3>(toPrint), completeLogFilePath, false
      );
    }

    // display elapsed time
    mt_uti::TimeDate::print(false, timerTitle + ":");
  }

  /**
   * Only 1 argument is available to pair with each keyword.
   * Inconsistent arguments may cause some members of 'params' to not be assigned.
   * 
   * e.g. '--foo -start -end 10 20'
   * This is an example of an inconsistent pairs
   * with 'T' as an integer. The 'params' will not change.
   */
  template <mt::inspector::ALPHANUMERIC T, size_t N>
  bool parsePairCLI(
    mt::CR_INT argc,
    char *argv[],
    mt::CR_STR title,
    mt::CR_ARR_STR<N> keywords,
    mt::ARR<T, N> &params
  ) {
    constexpr size_t length = N*2+1;
    mt::ARR_STR<length> argvStr;

    // the first 'argv' aka the program name is excluded
    for (int i = 1; i < argc; i++) {
      argvStr[i-1] = std::string(argv[i]);
    }

    /**
     * It is recommended to use a double hyphen at the beginning
     * of the 'title' to distinguish it from the 'keywords'.
     */
    if (argvStr.size() > 1 && argvStr[0] == title) {

      // pair steps
      for (int i = 1; i < argvStr.size() - 1; i += 2) {
        if (argvStr[i] == keywords[i/2]) {
  
          try {
            if constexpr (mt::inspector::isNumber<T>()) {
              // integer
              if (mt_uti::StrTools::isInteger(argvStr[i+1])) {
                params[i/2] = std::stoi(argvStr[i+1]);
              }
              // floating-point
              else if (mt_uti::StrTools::isFloatingPoint(argvStr[i+1])) {
                params[i/2] = std::stof(argvStr[i+1]);
              }
            }
            // string
            else params[i/2] = argvStr[i+1];
          }
          catch (...) {}
        }
      }

      return true;
    }

    return false;
  }
}

