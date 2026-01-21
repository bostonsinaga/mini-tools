#include "helper.hpp"
#include <thread>

bool stopwatchCallback(mt_uti::CLIParser<double> &cli) {
  mt_uti::Timer::Stopwatch stopwatch;

  std::this_thread::sleep_for(std::chrono::milliseconds(
    int(cli.getAt<double>("-dt")))
  );

  stopwatch.check();
  Helper::printTitle("\nSTOPWATCH:\n\n");

  std::cout
    << "printInMilliseconds: " << stopwatch.getMillisecondsString() << std::endl
    << "printInSeconds: " << stopwatch.getSecondsString() << std::endl
    << "printInMinutes: " << stopwatch.getMinutesString() << std::endl
    << "printInHours: " << stopwatch.getHoursString() << std::endl;

  stopwatch.reset();
  return true;
}

bool dateStringifyCallback(mt_uti::CLIParser<double> &cli) {

  mt_uti::Timer::Date date(
    cli.getAt<double>("-dd"),
    cli.getAt<double>("-mm"),
    cli.getAt<double>("-yyyy")
  );

  Helper::printTitle("\nSTRINGIFIERS:\n\n");

  std::cout
    << "numericStringify: " << date.numericStringify() << std::endl
    << "longCapitalizedStringify: " << date.longCapitalizedStringify() << std::endl
    << "shortCapitalizedStringify: " << date.shortCapitalizedStringify() << std::endl
    << "longAllCapsStringify: " << date.longAllCapsStringify() << std::endl
    << "shortAllCapsStringify: " << date.shortAllCapsStringify() << std::endl;

  return true;
}

int main(int argc, char *argv[]) {

  /** PARSERS */

  mt_uti::CLIParser<double> stopwatchCLI(
    mt_uti::StrTool::argvToStringVector(argc, argv),
    {std::make_pair("-dt", 0)}
  );

  mt_uti::CLIParser<double> dateStringifyCLI(
    mt_uti::StrTool::argvToStringVector(argc, argv),
    {
      std::make_pair("-dd", 1),
      std::make_pair("-mm", 1),
      std::make_pair("-yyyy", 1)
    }
  );

  /** WRAPPERS */

  Helper::CLIWrapper::setNumberOfRuns(2);

  Helper::CLIWrapper::run<double>(
    "--stopwatch",
    "Sleep for given time",
    stopwatchCLI,
    stopwatchCallback
  );

  Helper::CLIWrapper::run<double>(
    "--date-stringify",
    "Convert date components to text with separators or month names.",
    dateStringifyCLI,
    dateStringifyCallback
  );

  return 0;
}
