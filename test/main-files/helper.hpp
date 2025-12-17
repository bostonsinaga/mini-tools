#include "mini-tools.hpp"

class Helper {
public:
  typedef std::tuple<
    mt::VEC_INT*, mt::VEC_DBL*,
    mt::VEC_STR*, mt::VEC_STR*
  > TUP4PTR;

  /**
   * 'timerTitle' is test program name.
   * 'logFilePath' is relative path to 'mini-tools/test/logs/'.
   */
  static void getSamples(
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

  /**
   * Simplifying the use of 'CLIParser'. Providing final responses
   * and descriptions of commands from one class. The '--help' and '-h'
   * commands are provided by default. One of the callback calls must
   * return 'true' for the response to display the completed message.
   * 
   * Steps of use:
   * 1. Define callbacks.
   * 2. Create 'CLIParser' objects.
   * 3. Set optional values.
   * 4. Call 'run' method.
   */
  class CLIWrapper {
  private:
    inline static int numberOfRuns = 0;

    inline static bool
      displayingFinalMessage = true,
      mainMenuDetected = false,
      maxRunsReached = false,
      entryDetected = false;

    inline static std::string
      completedMessage = "**PROGRAM COMPLETED**",
      failedMessage = "**PROGRAM FAILED**",
      invalidMessage = "**INVALID ARGUMENT**",
      defaultDescription = "No description.";

    inline static mt::PAIR2<mt::VEC_CH, int>
      lastDefaultEntry = {{'a'}, 1};

    // keywords and entries always contain strings
    static std::string generateDefaultEntry() {
      lastDefaultEntry.second++;

      // limit counter
      if (lastDefaultEntry.second > 26) {
        lastDefaultEntry.second = 1;
        lastDefaultEntry.first.push_back('a');
      }
      else lastDefaultEntry.first.back()++;

      // combine characters
      std::string generatedEntry;

      for (char &ch : lastDefaultEntry.first) {
        generatedEntry += ch;
      }

      // combine letters with number
      return generatedEntry + std::to_string(lastDefaultEntry.second);
    }

    static void printHeader(
      std::string &entry,
      std::string &description
    ) {
      std::cout << "\x1b[36m" << entry << ":\x1b[0m\n"
        << "\x1b[3m" << description << "\x1b[0m";
    }

    static void printAbout(
      std::string &entry,
      std::string &description
    ) {
      std::cout << std::endl;
      CLIWrapper::printHeader(entry, description);
      std::cout << std::endl;
    }

    template <
      typename T = mt_uti::CLIDefault_T::type,
      typename U = mt_uti::CLIDefault_U<T>::type,
      typename V = mt_uti::CLIDefault_V<T, U>::type
    >
    requires mt_uti::CLIUniqueType<T, U, V>
    static void printKeywords(
      std::string &entry,
      std::string &description,
      mt_uti::CLIParser<T, U, V> &parser
    ) {
      std::cout << std::endl;
      CLIWrapper::printHeader(entry, description);

      for (mt::CR_STR keyword : parser.template extractStringsFromMainUnormap<T>()) {
        std::cout << "\n  " << keyword << " <"
          << mt_uti::CLIParser<T, U, V>::template getStringifiedType<T>() << '>';
      }

      for (mt::CR_STR keyword : parser.template extractStringsFromMainUnormap<U>()) {
        std::cout << "\n  " << keyword << " <"
          << mt_uti::CLIParser<T, U, V>::template getStringifiedType<U>() << '>';
      }

      for (mt::CR_STR keyword : parser.template extractStringsFromMainUnormap<V>()) {
        std::cout << "\n  " << keyword << " <"
          << mt_uti::CLIParser<T, U, V>::template getStringifiedType<V>() << '>';
      }

      std::cout << std::endl;
    }

    static void displayFinalMessage(bool &callbackCompleted) {
      static int currentRunNumber = 1;

      if (CLIWrapper::displayingFinalMessage) {
        if (callbackCompleted) {
          std::cout << "\n\x1b[032m" << CLIWrapper::completedMessage << "\x1b[0m\n";
        }
        else if (CLIWrapper::entryDetected) {
          std::cout << "\n\x1b[031m" << CLIWrapper::failedMessage << "\x1b[0m\n";
        }
        else if (CLIWrapper::numberOfRuns == currentRunNumber) {
          CLIWrapper::maxRunsReached = true;
          std::cout << "\n\x1b[033m" << CLIWrapper::invalidMessage << "\x1b[0m\n";
        }
      }

      currentRunNumber++;
    }

  public:
    CLIWrapper() = delete;

    template <
      typename T = mt_uti::CLIDefault_T::type,
      typename U = mt_uti::CLIDefault_U<T>::type,
      typename V = mt_uti::CLIDefault_V<T, U>::type
    >
    requires mt_uti::CLIUniqueType<T, U, V>
    static void run(
      std::string entry,
      std::string description,
      mt_uti::CLIParser<T, U, V> &parser,
      bool (*callback)(mt_uti::CLIParser<T, U, V>&)
    ) {
      /**
       * Skip this run.
       * An entry was detected in the previous runs
       * or the number of runs has exceeded the limit.
       */
      if (CLIWrapper::entryDetected || CLIWrapper::maxRunsReached) return;

      /** Assign default strings */

      if (entry.empty()) {
        entry = CLIWrapper::generateDefaultEntry();
      }

      if (description.empty()) {
        description = CLIWrapper::defaultDescription;
      }

      /**
       * Displaying main menu.
       * Main menu was already detected in previous runs.
       */
      if (CLIWrapper::mainMenuDetected) {
        CLIWrapper::printAbout(entry, description);
        return;
      }

      /** Entry Detection */

      bool callbackCompleted = false;

      // main menu
      if (parser.query({"-h"}) ||
        parser.query({"--help"})
      ) {
        CLIWrapper::mainMenuDetected = true;
        CLIWrapper::printAbout(entry, description);
        return;
      }
      // individual description
      else if (
        parser.enter({entry, "-h"}) ||
        parser.enter({entry, "--help"})
      ) {
        CLIWrapper::entryDetected = true;
        CLIWrapper::printKeywords<T, U, V>(entry, description, parser);
        return;
      }
      // invoke callback
      else if (parser.query({entry})) {
        CLIWrapper::entryDetected = true;

        if (callback && callback(parser)) {
          callbackCompleted = true;
        }
      }

      // display final message
      CLIWrapper::displayFinalMessage(callbackCompleted);
    }

    /**
     * OPTIONS
     * Call these methods before calling 'run' because
     * 'run' will use the values ​​set in these methods.
     */

    static void setCompletedMessage(mt::CR_STR message) {
      CLIWrapper::completedMessage = message;
    }

    static void setFailedMessage(mt::CR_STR message) {
      CLIWrapper::failedMessage = message;
    }

    static void setInvalidMessage(mt::CR_STR message) {
      CLIWrapper::invalidMessage = message;
    }

    // the description in 'run' cannot be empty
    static void setDefaultDescription(mt::CR_STR description) {
      if (!description.empty()) {
        CLIWrapper::defaultDescription = description;
      }
    }

    // empty or invalid argument will not be responded
    static void hideFinalMessage() {
      CLIWrapper::displayingFinalMessage = false;
    }

    /**
     * Less than one will cause the invalid message
     * to never be printed at the end of 'run' call.
     */
    static void setNumberOfRuns(mt::CR_INT count) {
      CLIWrapper::numberOfRuns = count;
    }
  };
};
