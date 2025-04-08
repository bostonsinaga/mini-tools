#include "mini-tools.h"

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
    mt_uti::TimeDate timer;
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
      mt_uti::Printer<int>::logf(
        *std::get<0>(toPrint), completeLogFilePath, true, false
      );
    }

    // reals
    if (std::get<1>(toPrint)) {
      mt_uti::Printer<double>::logf(
        *std::get<1>(toPrint), completeLogFilePath, true, false
      );
    }

    // letters
    if (std::get<2>(toPrint)) {
      mt_uti::Printer<std::string>::logf(
        *std::get<2>(toPrint), completeLogFilePath, true, false
      );
    }

    // words
    if (std::get<3>(toPrint)) {
      mt_uti::Printer<std::string>::logf(
        *std::get<3>(toPrint), completeLogFilePath, true, false
      );
    }

    timer.print(false, timerTitle + ":");
  }
}

