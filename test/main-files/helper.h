#include "mini-tools.h"

namespace helper {

  typedef std::tuple<
    mt::VEC_INT*, mt::VEC_DBL*,
    mt::VEC_STR*, mt::VEC_STR*
  > TUPLE_4;

  void call(
    std::function<TUPLE_4(mt::VEC_INT&, mt::VEC_DBL&, mt::VEC_STR&, mt::VEC_STR&)> callback,
    mt::CR_STR timerTitle,
    mt::CR_STR logFilePath
  ) {
    mt_uti::TimeDate timer;

    mt::VEC_INT integers = mt_uti::Scanner::txtToNumbers<int>("../../test/samples/integers.txt");
    mt::VEC_DBL reals = mt_uti::Scanner::txtToNumbers<double>("../../test/samples/reals.txt");
    mt::VEC_STR letters = mt_uti::Scanner::txtToLetters<std::string>("../../test/samples/letters.txt");
    mt::VEC_STR words = mt_uti::Scanner::txtToLetters<std::string>("../../test/samples/words.txt");

    TUPLE_4 toPrint = callback(integers, reals, letters, words);
    const std::string completeLogFilePath = "../../test/logs/" + logFilePath;

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

