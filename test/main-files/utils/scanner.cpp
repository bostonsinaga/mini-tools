#include "helper.hpp"

bool readBinaryCallback(mt_uti::CLIParser<std::string> &cli) {
  std::cout << "READ CALLED\n";
  return true;
}

int main(int argc, char *argv[]) {

  /** PARSERS */

  mt_uti::CLIParser<std::string> readBinaryCLI(
    mt_uti::StrTools::argvToStringVector(argc, argv),
    {std::make_pair("-in", "")}
  );

  /** WRAPPERS */

  Helper::CLIWrapper::run<std::string>(
    "--read-binary",
    "No description.",
    readBinaryCLI,
    readBinaryCallback
  );

  return 0;
}
