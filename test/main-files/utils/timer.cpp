#include "helper.hpp"

bool stringifyCallback(mt_uti::CLIParser<double> &cli) {

  mt_uti::Timer::Date date(
    cli.getAt<double>("-dd"),
    cli.getAt<double>("-mm"),
    cli.getAt<double>("-yyyy")
  );

  std::cout << "numericStringify: " << date.numericStringify() << std::endl;
  std::cout << "longCapitalizedStringify: " << date.longCapitalizedStringify() << std::endl;
  std::cout << "shortCapitalizedStringify: " << date.shortCapitalizedStringify() << std::endl;
  std::cout << "longAllCapsStringify: " << date.longAllCapsStringify() << std::endl;
  std::cout << "shortAllCapsStringify: " << date.shortAllCapsStringify() << std::endl;

  return true;
}

int main(int argc, char *argv[]) {

  /** PARSERS */

  mt_uti::CLIParser<double> stringifyCLI(
    mt_uti::StrTools::argvToStringVector(argc, argv),
    {
      std::make_pair("-dd", 1),
      std::make_pair("-mm", 1),
      std::make_pair("-yyyy", 1)
    }
  );

  /** WRAPPERS */

  Helper::CLIWrapper::run<double>(
    "--stringify",
    "Convert date components to text with separators or month names.",
    stringifyCLI,
    stringifyCallback
  );

  return 0;
}
