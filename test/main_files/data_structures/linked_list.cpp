#include "mini_tools.hpp"
#include "helper.hpp"

class Node : public mt_ds::LinkedList {
public:
  std::string name;

  Node(mt::CR_STR name_in) {
    name = name_in;
  }

  void print() {
    std::cout << "  " << name << std::endl;
  }
};

int main(int argc, char *argv[]) {

  mt_uti::CLI_Parser<int> parser(
    argc, argv, {"-name"}, {"-amount"}
  );

  if (parser.CLI_TitleParser::has("--test")) {

    Node *current = new Node(
      parser.CLI_WordParser::last("-name") + " 1"
    );

    for (int i = 1; i < parser.CLI_NumberParser::last("-amount"); i++) {
      current->accept(new Node(
        parser.CLI_WordParser::last("-name") + ' ' + std::to_string(i+1)
      ));

      current = static_cast<Node*>(current->next());
    }

    if (current) {
      std::cout << "\niterateRight:\n";

      current->head()->iterateRight([](mt_ds::LinkedList *object)->bool {
        static_cast<Node*>(object)->print();
        return true;
      });

      std::cout << "\niterateLeft:\n";

      current->tail()->iterateLeft([](mt_ds::LinkedList *object)->bool {
        static_cast<Node*>(object)->print();
        return true;
      });

      current->annihilate();
    }
  }

  return 0;
}

