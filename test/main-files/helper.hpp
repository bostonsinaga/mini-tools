#include "mini-tools.hpp"

namespace helper {

  typedef std::tuple<
    mt::VEC_INT*, mt::VEC_DBL*,
    mt::VEC_STR*, mt::VEC_STR*
  > TUP4PTR;

  /**
   * 'timerTitle' is test program name.
   * 'logFilePath' is relative path to 'mini-tools/test/logs/'.
   */
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

  // help and error message
  class Helperr {
  private:
    std::string description,
      parameterList,
      doneMessage,
      errorMessage;

  public:
    Helperr() = delete;

    Helperr(
      mt::CR_STR about,
      mt::CR_STR paramList,
      mt::CR_STR doneMsg = "DONE",
      mt::CR_STR errMsg = "INVALID ARGUMENTS"
    ) {
      description = about;
      parameterList = paramList;
      doneMessage = doneMsg;
      errorMessage = errMsg;
    }

    void printDescription() {
      std::cout << std::endl << description << std::endl
        << "\033[3m" << parameterList << "\033[0m\n";
    }

    void printDone() {
      std::cout << "\n\033[32m" << doneMessage << "\033[0m\n";
    }

    void printInvalid() {
      std::cout << "\n\033[31m" << errorMessage << "\033[0m\n"
        << "\033[3mPlease type --help or -h to see available parameters\033[0m\n";
    }
  };

  /** Default entries: '--test', '--help', and '-h' */

  template <mt::inspector::NUMBER T>
  void CLIWrapper(
    Helperr *helperr,
    mt_uti::CLIParser<T> *cli,
    const std::function<bool(mt_uti::CLIParser<T>*)> &callback,
    mt::CR_VEC_STR additionalEntries = {}
  ) {
    if (!helperr || !cli) return;

    // entry
    if (cli->enter({"--test"})) {

      // help
      if (cli->enter({"--test", "--help"}) ||
        cli->enter({"--test", "-h"})
      ) {
        helperr->printDescription();
      }
      // parse inputs
      else if (cli->enter({"--test"})) {
        if (!callback(cli)) {
          helperr->printInvalid();
        }
        else helperr->printDone();
      }
    }
    // additional entries
    else if (!additionalEntries.empty() &&
      cli->enter(additionalEntries)
    ) {
      if (!callback(cli)) {
        helperr->printInvalid();
      }
      else helperr->printDone();
    }
    // help
    else if (cli->enter({"--help"}) || cli->enter({"-h"})) {
      helperr->printDescription();
    }
    // error
    else helperr->printInvalid();
  }

  template <mt::inspector::NUMBER T>
  void CLIWrapper(
    Helperr helperr,
    mt_uti::CLIParser<T> cli,
    const std::function<bool(mt_uti::CLIParser<T>*)> &callback,
    mt::CR_VEC_STR additionalEntries = {}
  ) {
    CLIWrapper(
      &helperr, &cli,
      callback, additionalEntries
    );
  }
}

