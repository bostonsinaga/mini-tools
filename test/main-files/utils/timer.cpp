#include "helper.hpp"
#include <thread>

bool stopwatchCallback(mt_uti::CLIParser<double> &cli) {
  mt_uti::Timer::Stopwatch stopwatch;

  std::this_thread::sleep_for(std::chrono::milliseconds(
    int(cli.getAt<double>("-delta-time")))
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

bool dateParseCallback(mt_uti::CLIParser<std::string, bool> &cli) {

  Helper::printTitle("\nDATE PARSE:\n\n");

  mt_uti::Timer::Parser parser;
  parser.implicitYear.active = cli.getAt<bool>("--imply-century");
  parser.scan(cli.getAt<std::string>("-string"));

  if (!parser.hasDate()) {
    std::cerr << "No dates found\n";
    return false;
  }
  else {
    std::cout << "parser.getAllDates()\n";

    for (mt_uti::Timer::Date &date : parser.getAllDates()) {
      std::cout << "  " << date.numericStringify();
    }

    std::cout << "\nparser.getCompletedDates()\n";

    for (mt_uti::Timer::Date &date : parser.getCompletedDates()) {
      std::cout << "  " << date.numericStringify();
    }

    std::cout << "\nparser.getMMYYYYDates()\n";

    for (mt_uti::Timer::Date &date : parser.getMMYYYYDates()) {
      std::cout << "  " << date.numericStringify();
    }
  }

  return true;
}

bool dateStringifyCallback(mt_uti::CLIParser<double> &cli) {

  mt_uti::Timer::Date date(
    cli.getAt<double>("-dd"),
    cli.getAt<double>("-mm"),
    cli.getAt<double>("-yyyy")
  );

  Helper::printTitle("\nDATE STRINGIFY:\n\n");

  std::cout
    << "numericStringify: " << date.numericStringify() << std::endl
    << "longCapitalizedStringify: " << date.longCapitalizedStringify() << std::endl
    << "shortCapitalizedStringify: " << date.shortCapitalizedStringify() << std::endl
    << "longAllCapsStringify: " << date.longAllCapsStringify() << std::endl
    << "shortAllCapsStringify: " << date.shortAllCapsStringify() << std::endl;

  return true;
}

bool spreadCallback(mt_uti::CLIParser<double> &cli) {
  Helper::printTitle("\nSPREAD:\n\n");
  return false;
}

int main(int argc, char *argv[]) {

  /** PARSERS */

  mt::VEC_STR raws = mt_uti::StrTool::argvToStringVector(argc, argv);

  mt_uti::CLIParser<double> stopwatchCLI(
    raws,
    {std::make_pair("-delta-time", 0)}
  );

  mt_uti::CLIParser<std::string, bool> dateParseCLI(
    raws,
    {std::make_pair("-string", "")},
    {std::make_pair("--imply-century", false)}
  );

  mt_uti::CLIParser<double> dateStringifyCLI(
    raws,
    {
      std::make_pair("-dd", 1),
      std::make_pair("-mm", 1),
      std::make_pair("-yyyy", 1)
    }
  );

  mt_uti::CLIParser<double> spreadCLI(
    raws,
    {
      std::make_pair("-dd-start", 1),
      std::make_pair("-mm-start", 1),
      std::make_pair("-yyyy-start", 1),
      std::make_pair("-dd-end", 1),
      std::make_pair("-mm-end", 1),
      std::make_pair("-yyyy-end", 1)
    }
  );

  /** WRAPPERS */

  Helper::CLIWrapper::setNumberOfRuns(4);

  Helper::CLIWrapper::run<double>(
    "--stopwatch",
    "Sleep for given time",
    stopwatchCLI,
    stopwatchCallback
  );

  Helper::CLIWrapper::run<std::string, bool>(
    "--date-parse",
    "Date parse description.",
    dateParseCLI,
    dateParseCallback
  );

  Helper::CLIWrapper::run<double>(
    "--date-stringify",
    "Convert date components to text with separators or month names.",
    dateStringifyCLI,
    dateStringifyCallback
  );

  Helper::CLIWrapper::run<double>(
    "--spread",
    "Spread description.",
    spreadCLI,
    spreadCallback
  );

  return 0;
}
