#include "mini-tools.hpp"

/**
 * Register username, pin, and premium status in sequence.
 * -username<WORD> -pin<NUMBER> -premium<TOGGLE>
 */
int main(int argc, char *argv[]) {

  mt_uti::CLIParser<int> cli = mt_uti::CLIParser<int>(
    argc, argv,
    {"-username"},
    {"-pin"},
    {"--premium"}
  );

  if (cli.query({"--test"})) {

    if (cli.enter({"--test", "--help"})) {
      std::cout
        << "\nRegister username, pin, and premium status in sequence.\n"
        << "\033[3m-username<WORD> -pin<NUMBER> -premium<TOGGLE>\033[0m\n";
    }
    else {
      cli.balanceAll(
        {{"-username", ""}},
        {{"-pin", 0}},
        {{"-premium", false}}
      );

      // WORD
      std::cout << "\nUsername:\n";

      for (mt::CR_STR username : cli.getWords("-username")) {
        std::cout << "  " << username << std::endl;
      }

      // NUMBER
      std::cout << "\nPIN:\n";

      for (mt::CR<int> pin : cli.getNumbers("-pin")) {

        if (pin == 0) {
          std::cout << "  " << "empty" << std::endl;
        }
        else if (mt_alg::NumberSequence::countDigits<int>(pin) != 6) {
          std::cout << "  " << "invalid" << std::endl;
        }
        else std::cout << "  " << pin << std::endl;
      }

      // TOGGLE
      std::cout << "\nPremium:\n";

      for (mt::CR_BOL premium : cli.getToggles("-premium")) {
        std::cout << "  " << premium << std::endl;
      }
    }
  }
  else std::cout << "\n\033[31mINVALID ARGUMENTS\033[0m\n";

  return 0;
}

