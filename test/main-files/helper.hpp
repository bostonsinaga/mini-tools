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
  class CLIMessage {
  private:
    std::string mainEntry,
      description,
      parameterList,
      doneMessage,
      errorMessage;

  public:
    CLIMessage() = delete;

    CLIMessage(
      mt::CR_STR mEntry,
      mt::CR_STR desc,
      mt::CR_STR paramList,
      mt::CR_STR doneMsg = "DONE",
      mt::CR_STR errMsg = "INVALID ARGUMENTS"
    ) {
      mainEntry = mEntry;
      description = desc;
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

    std::string getMainEntry() {
      return mainEntry;
    }
  };

  /**
   * The '--help' and '-h' entries are included
   * by default to call 'CLIMessage::printDescription'.
   */
  template <
    typename T = mt_uti::CLIDefault_T::type,
    typename U = mt_uti::CLIDefault_U<T>::type,
    typename V = mt_uti::CLIDefault_V<T, U>::type
  >
  requires mt_uti::CLIUniqueType<T, U, V>
  void CLIWrapper(
    const mt::VEC<CLIMessage*> &cliMessageVec,
    const mt::VEC<mt_uti::CLIParser<T, U, V>*> &cliVec,
    const mt::VEC<std::function<bool(mt_uti::CLIParser<T, U, V>*)>> &callbackVec,
    mt::CR_VEC_STR additionalEntries = {}
  ) {
    // the vectors must contain and be the same size
    if (cliMessageVec.empty() || cliVec.empty() || callbackVec.empty() ||
      cliMessageVec.size() != cliVec.size() ||
      cliVec.size() != callbackVec.size() ||
      callbackVec.size() != cliMessageVec.size()
    ) return;

    bool entered = false;
    int i = 0;

    for (i = 0; i < cliMessageVec.size(); i++) {
      // entry
      if (cliVec[i]->enter({cliMessageVec[i]->getMainEntry()})) {

        // help
        if (cliVec[i]->enter({cliMessageVec[i]->getMainEntry(), "--help"}) ||
          cliVec[i]->enter({cliMessageVec[i]->getMainEntry(), "-h"})
        ) {
          entered = true;
          cliMessageVec[i]->printDescription();
          break;
        }
        // parse inputs
        else if (cliVec[i]->enter({cliMessageVec[i]->getMainEntry()})) {
          entered = true;

          if (!callbackVec[i](cliVec[i])) {
            cliMessageVec[i]->printInvalid();
          }
          else cliMessageVec[i]->printDone();

          break;
        }
      }
    }

    if (!entered) {
      // help
      if (cliVec[i]->enter({"--help"}) || cliVec[i]->enter({"-h"})) {
        cliMessageVec[i]->printDescription();
      }
      // error
      else cliMessageVec[i]->printInvalid();
    }
  }
}

