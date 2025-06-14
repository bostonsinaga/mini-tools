#include "helper.hpp"

int main(int argc, char *argv[]) {

  helper::CLIWrapper<int>(
    // help and error message
    helper::Helperr(
      "Enter product name, price, and edibility in sequence.",
      "--test -name<WORD> -price<NUMBER> -edible<TOGGLE>"
    ),
    // CLI registration
    mt_uti::CLIParser<int>(
      mt_uti::CLIParser<int>::argvToStringVector(argc, argv),
      {std::make_pair("-name", "Noname")},
      {std::make_pair("-price", 0)},
      {std::make_pair("--edible", true)}
    ),
    // on 'cli->enter("--test")'
    [](mt_uti::CLIParser<int> *cli)->bool {
      cli->balance(
        {std::make_pair("-name", "Unknown")},
        {std::make_pair("-price", 0)},
        {std::make_pair("--edible", false)}
      );

      // word input
      std::cout << "\nName:\n";

      for (mt::CR_STR name : cli->getVectorAtWords("-name")) {
        std::cout << "  " << name << std::endl;
      }

      // number input
      std::cout << "\nPrice:\n";

      for (mt::CR<int> price : cli->getVectorAtNumbers("-price")) {

        if (price <= 0) {
          std::cout << "  " << "free" << std::endl;
        }
        else std::cout << "  " << price << std::endl;
      }

      // toggle input
      std::cout << "\nEdibility:\n";

      for (mt::CR_BOL edible : cli->getVectorAtToggles("--edible")) {
        std::cout << "  " << (edible ? "Edible" : "Not Edible") << std::endl;
      }

      // clear and release all unordered maps
      std::cout << "\nUNORDERED MAP SIZES AND CLEANED:\n";

      /** Show proofs of cleaning */

      std::cout << " Entries from " << cli->getEntriesSize();
      cli->cleanEntries(true);
      std::cout << " to " << cli->getEntriesSize() << std::endl;

      std::cout << " Words from " << cli->getSizeAtWords("-name");
      cli->cleanWords(true);
      std::cout << " to " << cli->getSizeAtWords("-name") << std::endl;

      std::cout << " Numbers from " << cli->getSizeAtNumbers("-price");
      cli->cleanNumbers(true);
      std::cout << " to " << cli->getSizeAtNumbers("-price") << std::endl;

      std::cout << " Toggles from " << cli->getSizeAtToggles("--edible");
      cli->cleanToggles(true);
      std::cout << " to " << cli->getSizeAtToggles("--edible") << std::endl;

      return true;
    }
  );

  return 0;
}

