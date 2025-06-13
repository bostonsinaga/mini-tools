#include "helper.hpp"

int main(int argc, char *argv[]) {

  helper::Helperr helperr(
    "Register username, pin, and premium status in sequence.",
    "--test -username<WORD> -pin<NUMBER> -premium<TOGGLE>"
  );

  // registration
  mt_uti::CLIParser<int> cli(
    mt_uti::CLIParser<int>::argvToStringVector(argc, argv),
    {std::make_pair("-username", "Noname")},
    {std::make_pair("-pin", 0)},
    {std::make_pair("--premium", false)}
  );

  // entry
  if (cli.enter({"--test"})) {

    // help
    if (cli.enter({"--test", "--help"}) ||
      cli.enter({"--test", "-h"})
    ) {
      helperr.printDescription();
    }
    // parse inputs
    else if (cli.enter({"--test"})) {
      cli.balance(
        {std::make_pair("-username", "")},
        {std::make_pair("-pin", 0)},
        {std::make_pair("--premium", false)}
      );

      // word input
      std::cout << "\nUsername:\n";

      for (mt::CR_STR username : cli.getVectorAtWords("-username")) {
        std::cout << "  " << username << std::endl;
      }

      // number input
      std::cout << "\nPIN:\n";

      for (mt::CR<int> pin : cli.getVectorAtNumbers("-pin")) {

        if (pin == 0) {
          std::cout << "  " << "empty" << std::endl;
        }
        else if (mt_alg::NumberSequence::countDigits<int>(pin) != 6) {
          std::cout << "  " << "invalid" << std::endl;
        }
        else std::cout << "  " << pin << std::endl;
      }

      // toggle input
      std::cout << "\nPremium:\n";

      for (mt::CR_BOL premium : cli.getVectorAtToggles("-premium")) {
        std::cout << "  " << premium << std::endl;
      }

      // clear and release all unordered maps
      cli.cleanAll(true);
      std::cout << "\n\033[3mAll unordered maps are cleared and released\033[0m\n";

      // show proof of cleaning
      std::cout << " Entries Size = " << cli.getEntriesSize() << std::endl;
      std::cout << " Words Size = " << cli.getWordsSize() << std::endl;
      std::cout << " Numbers Size = " << cli.getNumbersSize() << std::endl;
      std::cout << " Toggles Size = " << cli.getTogglesSize() << std::endl;
    }
  }
  else if (cli.enter({"--help"}) || cli.enter({"-h"})) {
    helperr.printDescription();
  }
  // error
  else helperr.printInvalid();

  return 0;
}

