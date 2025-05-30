#include "mini-tools.hpp"

int main(int argc, char *argv[]) {

  mt_uti::CLIParser<int> cli = mt_uti::CLIParser<int>(
    argc, argv,
    {"username"},
    {"pin"},
    {"premium"}
  );

  if (cli.enter({"test"})) {

    std::cout << "\nUsername:\n";

    for (mt::CR_STR username : cli.getWords("username")) {
      std::cout << "  " << username << std::endl;
    }

    std::cout << "\nPin:\n";

    for (mt::CR<int> pin : cli.getNumbers("pin")) {
      std::cout << "  " << pin << std::endl;
    }

    std::cout << "\nPremium:\n";

    for (mt::CR_BOL premium : cli.getToggles("premium")) {
      std::cout << "  " << premium << std::endl;
    }
  }
  else std::cout << "\n\033[31mENTRY ERROR\033[0m\n";

  return 0;
}

