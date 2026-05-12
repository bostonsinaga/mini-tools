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

// string codes for distribution method
std::string 
  discode_str_each_days = "each-days",
  discode_str_each_months = "each-months",
  discode_str_each_years = "each-years",
  discode_str_fixed_number = "fixed-number";

bool spreadCallback(mt_uti::CLIParser<double, bool, std::string> &cli) {
  Helper::printTitle("\nSPREAD:\n\n");

  // integer codes for distribution method
  enum distribution_int_code {
    discode_int_each_days,
    discode_int_each_months,
    discode_int_each_years,
    discode_int_fixed_number
  } discode;

  // get string distribution code from the 'cli'
  std::string strCode = cli.getAt<std::string>("--distribution-method");
  mt_uti::StrTool::modifyStringToLowercase(strCode);

  // change distribdistributionute code from string to integer
  if (strCode == discode_str_each_days) discode = discode_int_each_days;
  else if (strCode == discode_str_each_months) discode = discode_int_each_months;
  else if (strCode == discode_str_each_years) discode = discode_int_each_years;
  else discode = discode_int_fixed_number;

  mt_uti::Timer::Date dateStart(
    cli.getAt<double>("-dd-start"),
    cli.getAt<double>("-mm-start"),
    cli.getAt<double>("-yyyy-start")
  );

  mt_uti::Timer::Date dateEnd(
    cli.getAt<double>("-dd-end"),
    cli.getAt<double>("-mm-end"),
    cli.getAt<double>("-yyyy-end")
  );

  std::cout << "dateStart: " << dateStart.numericStringify()
    << "\ndateEnd: " << dateEnd.numericStringify();

  mt_uti::Timer::Spread spread(dateStart, dateEnd);
  bool inclusive = cli.getAt<bool>("--inclusive");

  /** Information line for status of value boundary */

  std::cout << "\nboundary: " << (inclusive ? "inclusive" : "exclusive") << std::endl;

  if (inclusive) spread.setInclusive();
  else spread.setExclusive();

  /** Assignment to corresponding distribution method */

  std::string spreadTitle;
  mt::VEC<mt_uti::Timer::Date> spreadDates;
  size_t quantity = cli.getAt<double>("-quantity");

  if (discode == discode_int_each_days) {
    spreadTitle = "spread.everyDaysDistribute";
    spreadDates = spread.everyDaysDistribute(quantity);
  }
  else if (discode == discode_int_each_months) {
    spreadTitle = "spread.everyMonthsDistribute";
    spreadDates = spread.everyMonthsDistribute(quantity);
  }
  else if (discode == discode_int_each_years) {
    spreadTitle = "spread.everyYearsDistribute";
    spreadDates = spread.everyYearsDistribute(quantity);
  }
  else {
    spreadTitle = "spread.fixedNumberDistribute";
    spreadDates = spread.fixedNumberDistribute(quantity);
  }

  /** Display the result */

  int atLeastOne = 0;
  std::cout << "\n" << spreadTitle << ":\n";

  for (mt::CR<mt_uti::Timer::Date> date : spreadDates) {
    std::cout << "  " << date.numericStringify() << std::endl;
    atLeastOne++;
  }

  return atLeastOne;
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

  mt_uti::CLIParser<double, bool, std::string> spreadCLI(
    raws,
    {
      std::make_pair("-dd-start", 1),
      std::make_pair("-mm-start", 1),
      std::make_pair("-yyyy-start", 1),
      std::make_pair("-dd-end", 1),
      std::make_pair("-mm-end", 1),
      std::make_pair("-yyyy-end", 1),
      std::make_pair("-quantity", 1),
    },
    {
      std::make_pair("--inclusive", false)
    },
    {
      std::make_pair("--distribution-method", discode_str_fixed_number)
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
    "Parse potential dates from a long text",
    dateParseCLI,
    dateParseCallback
  );

  Helper::CLIWrapper::run<double>(
    "--date-stringify",
    "Convert date components to text with separators or month names",
    dateStringifyCLI,
    dateStringifyCallback
  );

  Helper::CLIWrapper::run<double, bool, std::string>(
    "--spread",
    "Spread dates between 2 dates (the interval)",
    spreadCLI,
    spreadCallback
  );

  return 0;
}
