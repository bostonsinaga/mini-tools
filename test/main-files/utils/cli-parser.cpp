#include "helper.hpp"

int main(int argc, char *argv[]) {

  helper::CLIWrapper<int, std::string>(
    // help and error message
    helper::CLIMessage(
      "Register product name, price, and edibility in sequence.",
      "--test -name<WORD> -price<NUMBER> -edible<TOGGLE>"
    ),
    // CLI registration
    mt_uti::CLIParser<int, std::string>(
      mt_uti::CLIParser<int, std::string>::argvToStringVector(argc, argv),
      {std::make_pair("-name", "Noname")},
      {std::make_pair("-price", 0)},
      {std::make_pair("--edible", true)}
    ),
    // on 'cli->enter("--test")'
    [](mt_uti::CLIParser<int, std::string> *cli)->bool {
      cli->balance(
        {std::make_pair("-name", "Unknown")},
        {std::make_pair("-price", 0)},
        {std::make_pair("--edible", false)}
      );

      // word input
      std::cout << "\nName:\n";

      for (std::string &name : cli->getVectorAt<std::string>("-name")) {
        std::cout << "  " << name << std::endl;
      }

      // number input
      std::cout << "\nPrice:\n";

      for (int &price : cli->getVectorAt<int>("-price")) {

        if (price <= 0) {
          std::cout << "  " << "free" << std::endl;
        }
        else std::cout << "  " << price << std::endl;
      }

      // toggle input
      std::cout << "\nEdibility:\n";

      for (bool &edible : cli->getVectorAt<bool>("--edible")) {
        std::cout << "  " << (edible ? "Edible" : "Not Edible") << std::endl;
      }

      // clear and release all unordered maps
      std::cout << "\nUNORDERED MAP SIZES AND CLEANED:\n";

      /** Show proofs of cleaning */

      std::cout << " Entries from " << cli->getEntriesSize();
      cli->cleanEntries(true);
      std::cout << " to " << cli->getEntriesSize() << std::endl;

      std::cout << " Words from " << cli->getSizeAt<std::string>("-name");
      cli->clean<std::string>(true);
      std::cout << " to " << cli->getSizeAt<std::string>("-name") << std::endl;

      std::cout << " Numbers from " << cli->getSizeAt<int>("-price");
      cli->clean<int>(true);
      std::cout << " to " << cli->getSizeAt<int>("-price") << std::endl;

      std::cout << " Toggles from " << cli->getSizeAt<bool>("--edible");
      cli->clean<bool>(true);
      std::cout << " to " << cli->getSizeAt<bool>("--edible") << std::endl;

      return true;
    }
  );

  return 0;
}

