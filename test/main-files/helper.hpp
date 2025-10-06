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
  void getSamples(
    const std::function<TUP4PTR(mt::VEC_INT&, mt::VEC_DBL&, mt::VEC_STR&, mt::VEC_STR&)> &callback,
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
    mt_uti::Timer::Stopwatch::print(false, timerTitle + ":");
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
      std::cout << std::endl << mainEntry << ":\n" << description << std::endl
        << "\033[3m" << parameterList << "\033[0m\n";
    }

    void printDone() {
      std::cout << std::endl << mainEntry << ":\n" << "\033[32m" << doneMessage << "\033[0m\n";
    }

    void printInvalid() {
      std::cout << std::endl << mainEntry << ":\n" << "\033[31m" << errorMessage << "\033[0m\n"
        << "\033[3mPlease type --help or -h to see available parameters\033[0m\n";
    }

    std::string getMainEntry() {
      return mainEntry;
    }
  };

  /**
   * Wrapper to evaluate input, print messages,
   * and invoke callback in single 'run()' call.
   */
  class CLIWrapper final {
  private:
    bool mainEntryEntered = false;
    int numberOfCLIs, numberOfRegistered = 0;
    mt::VEC<CLIMessage*> messagesForInvalid;

  public:
    CLIWrapper() = delete;

    CLIWrapper(mt::CR_INT numberOfCLIs_in) {
      numberOfCLIs = numberOfCLIs_in;
    }

    /**
     * The '--help' and '-h' entries are included
     * by default to invoke 'CLIMessage::printDescription'.
     */
    template <
      typename T = mt_uti::CLIDefault_T::type,
      typename U = mt_uti::CLIDefault_U<T>::type,
      typename V = mt_uti::CLIDefault_V<T, U>::type
    >
    requires mt_uti::CLIUniqueType<T, U, V>
    void run(
      CLIMessage &message,
      mt_uti::CLIParser<T, U, V> &cli,
      bool (&callback)(mt_uti::CLIParser<T, U, V>&)
    ) {
      if (numberOfRegistered < numberOfCLIs) {
        numberOfRegistered++;
      }
      else return;

      std::string mainEntry = message.getMainEntry();

      // entry
      if (cli.enter({mainEntry})) {
        mainEntryEntered = true;

        // help
        if (cli.enter({mainEntry, "--help"}) ||
          cli.enter({mainEntry, "-h"})
        ) {
          message.printDescription();
        }
        // parse inputs
        else {
          if (!callback(cli)) {
            message.printInvalid();
          }
          else message.printDone();
        }
      }
      else {
        // help
        if (cli.query({"--help"}, false) ||
          cli.query({"-h"}, false)
        ) {
          message.printDescription();
        }
        // error
        else messagesForInvalid.push_back(&message);
      }

      /**
       * Print an invalid message by all registered CLIs
       * if any main entry is not entered or not found.
       */
      if (numberOfRegistered == numberOfCLIs && !mainEntryEntered) {
        for (CLIMessage *message : messagesForInvalid) {
          message->printInvalid();
        }
      }
    }
  };
}
