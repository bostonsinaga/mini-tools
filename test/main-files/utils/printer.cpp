#include "helper.hpp"

struct Foo {
  std::string name;
  int value;
};

bool writeBinaryCallback(mt_uti::CLIParser<std::string> &cli) {
  Foo foo("Foothing", 100);
  std::string filename = cli.getAt<std::string>("-path", 0);
  mt_uti::Printer::writeFileBinary<Foo>(foo, filename, false);
  return true;
}

int main(int argc, char *argv[]) {

  /** PARSERS */

  mt_uti::CLIParser<std::string> writeBinaryCLI(
    mt_uti::StrTools::argvToStringVector(argc, argv),
    {std::make_pair("-path", "")}
  );

  /** WRAPPERS */

  Helper::CLIWrapper::run<std::string>(
    "--write-binary",
    "Write any type of class into a binary file.",
    writeBinaryCLI,
    writeBinaryCallback
  );

  return 0;
}
