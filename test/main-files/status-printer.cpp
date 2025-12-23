#include "helper.hpp"

/**
 * Print custom status message after an executable runtime.
 */
class StatusPrinter {
private:
  inline static const std::string
    coloringStrings[2] = {
      "\n\x1b[38;2;0;0;255m",  // blue
      "\n\x1b[38;2;255;127;0m" // orange
    };

public:
  enum STATUS_CODE {
    STATUS_COMPLETED, STATUS_FAILED
  };

  inline static const std::string defaultBorderStyle = "**";

  static void displayStatusMessage(
    mt::CR_VEC_STR words,
    mt::CR_STR borderStyle,
    STATUS_CODE colorCode
  ) {
    // clamping code value
    if (colorCode < STATUS_CODE::STATUS_COMPLETED) {
      colorCode = STATUS_CODE::STATUS_COMPLETED;
    }
    else if (colorCode > STATUS_CODE::STATUS_FAILED) {
      colorCode = STATUS_CODE::STATUS_FAILED;
    }

    // opening color
    std::cout << StatusPrinter::coloringStrings[colorCode] << borderStyle;

    // print words from CLI input
    for (int i = 0; i < words.size(); i++) {
      std::cout << words[i];
      if (i < words.size() - 1) std::cout << ' ';
    }

    // closing color
    std::cout << borderStyle << "\x1b[0m\n";
  }
};

bool messageCallback(mt_uti::CLIParser<std::string> &cli) {

  constexpr int _not_found = -1;
  StatusPrinter::STATUS_CODE foundStatus;
  std::string foundKeyword;

  int completedOrder = cli.getMainUnormapOrder("-completed"),
    failedOrder = cli.getMainUnormapOrder("-failed");

  // all found
  if (failedOrder != _not_found &&
    completedOrder != _not_found
  ) {
    if (completedOrder < failedOrder) {
      foundStatus = StatusPrinter::STATUS_COMPLETED;
      foundKeyword = "-completed";
    }
    else {
      foundStatus = StatusPrinter::STATUS_FAILED;
      foundKeyword = "-failed";
    }
  }
  // completed found
  else if (completedOrder != _not_found) {
    foundStatus = StatusPrinter::STATUS_COMPLETED;
    foundKeyword = "-completed";
  }
  // failed found
  else if (failedOrder != _not_found) {
    foundStatus = StatusPrinter::STATUS_FAILED;
    foundKeyword = "-failed";
  }

  // any keyword found
  if (!foundKeyword.empty()) {
    mt::VEC_STR words = cli.getVectorAt<std::string>(foundKeyword);
    std::string borderStyle = cli.getAt<std::string>("-border-style", 0);

    // set default border style
    if (borderStyle.empty()) {
      borderStyle = StatusPrinter::defaultBorderStyle;
    }

    // the keyword followed by input
    if (!words.empty()) {
      StatusPrinter::displayStatusMessage(
        words, borderStyle, foundStatus
      );
    }
  }

  return true;
}

int main(int argc, char *argv[]) {

  /** PARSERS */

  mt_uti::CLIParser<std::string> messageCLI(
    mt_uti::StrTools::argvToStringVector(argc, argv),
    {
      std::make_pair("-border-style", ""),
      std::make_pair("-failed", ""),
      std::make_pair("-completed", "")
    }
  );

  /** WRAPPERS */

  Helper::CLIWrapper::hideFinalMessage();

  Helper::CLIWrapper::run<std::string>(
    "--message",
    "Print message for completed (return 0) or failed (return 1) executable.\n"
    "Select either '-completed' or '-failed' to display a message.\n"
    "Only the first detected keyword input will be displayed.\n"
    "Set the left and right border style by specifying '-border-style'.",
    messageCLI,
    messageCallback
  );

  return 0;
}
