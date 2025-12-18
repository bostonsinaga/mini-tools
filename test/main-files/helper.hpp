#ifndef __TEST__HELPER_HPP__
#define __TEST__HELPER_HPP__

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
  );

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

    inline static const std::string
      italicFont = "\x1b[3m",
      redFontColor = "\x1b[38;2;255;0;0m",
      greenFontColor = "\x1b[38;2;0;255;0m",
      azureFontColor = "\x1b[38;2;0;127;255m",
      yellowFontColor = "\x1b[38;2;255;255;0m";

    // keywords and entries always contain strings
    static std::string generateDefaultEntry();

    static void printHeader(
      std::string &entry,
      std::string &description
    );

    static void printAbout(
      std::string &entry,
      std::string &description
    );

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
    );

    // final message flanked by new lines above and below
    static void displayFinalMessage(bool &callbackCompleted);

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
    );

    /**
     * OPTIONS
     * Call these methods before calling 'run' because
     * 'run' will use the values ​​set in these methods.
     */

    static void setCompletedMessage(mt::CR_STR message);
    static void setFailedMessage(mt::CR_STR message);
    static void setInvalidMessage(mt::CR_STR message);

    // the description in 'run' cannot be empty
    static void setDefaultDescription(mt::CR_STR description);

    // empty or invalid argument will not be responded
    static void hideFinalMessage();

    /**
     * Less than one will cause the invalid message
     * to never be printed at the end of 'run' call.
     */
    static void setNumberOfRuns(mt::CR_INT count);
  };
};

#include "helper.tpp"
#endif // __TEST__HELPER_HPP__