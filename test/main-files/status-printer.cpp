#include "helper.hpp"

/**
 * Print custom status message after an executable runtime.
 */
class StatusPrinter {
private:
  inline static const std::string
    defaultCompletedLabel = "PROGRAM COMPLETED",
    defaultFailedLabel = "PROGRAM FAILED",
    coloringStrings[2] = {
      "\n\x1b[38;2;0;0;255m",  // blue
      "\n\x1b[38;2;255;127;0m" // orange
    };

public:
  enum LABEL_CODE {
    LABEL_COMPLETED, LABEL_FAILED
  };

  static void printStatusLabel(
    mt_uti::CLIParser<std::string> &cli,
    LABEL_CODE colorCode
  ) {
    // clamping code value
    if (colorCode < LABEL_CODE::LABEL_COMPLETED) {
      colorCode = LABEL_CODE::LABEL_COMPLETED;
    }
    else if (colorCode > LABEL_CODE::LABEL_FAILED) {
      colorCode = LABEL_CODE::LABEL_FAILED;
    }

    // opening color
    std::cout << StatusPrinter::coloringStrings[colorCode];

    // get CLI input
    mt::VEC_STR labels = cli.getVectorAt<std::string>("-message");

    // print default labels
    if (labels.empty()) {
      if (colorCode == LABEL_CODE::LABEL_COMPLETED) {
        std::cout << StatusPrinter::defaultCompletedLabel;
      }
      else std::cout << StatusPrinter::defaultFailedLabel;
    }
    // print labels from CLI input
    else for (mt::CR_STR str : labels) {
      std::cout << str << ' ';
    }

    // closing color
    std::cout << "\x1b[0m\n";
  }
};

bool completedLabelCallback(mt_uti::CLIParser<std::string> &cli) {
  StatusPrinter::printStatusLabel(cli, StatusPrinter::LABEL_COMPLETED);
  return true;
}

bool failedLabelCallback(mt_uti::CLIParser<std::string> &cli) {
  StatusPrinter::printStatusLabel(cli, StatusPrinter::LABEL_FAILED);
  return true;
}

int main(int argc, char *argv[]) {

  /** PARSERS */

  mt_uti::CLIParser<std::string> completedLabelCLI(
    mt_uti::StrTools::argvToStringVector(argc, argv),
    {std::make_pair("-message", "")}
  );

  mt_uti::CLIParser<std::string, mt::LD, bool> failedLabelCLI(
    mt_uti::StrTools::argvToStringVector(argc, argv),
    {std::make_pair("-message", "")}
  );

  /** WRAPPERS */

  Helper::CLIWrapper::setNumberOfRuns(2);
  Helper::CLIWrapper::hideFinalMessage();

  Helper::CLIWrapper::run<std::string>(
    "--completed-label",
    "Printed when the program returns a zero value.",
    completedLabelCLI,
    completedLabelCallback
  );

  Helper::CLIWrapper::run<std::string, mt::LD, bool>(
    "--failed-label",
    "Printed when the program returns a non-zero value.",
    failedLabelCLI,
    failedLabelCallback
  );

  return 0;
}
