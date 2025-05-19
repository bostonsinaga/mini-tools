#include "mini_tools.hpp"
#include "helper.hpp"

typedef mt_ds::LinkedList LL;

class Node : public LL {
public:
  std::string name;

  Node(mt::CR_STR name_in) {
    name = name_in;
  }

  void print() {
    std::cout << "  " << name << std::endl;
  }
};

void iterateNodes(
  const LL::DIRECTION &dir,
  Node* &current,
  mt::CR_STR title
) {
  std::cout << "\n" + title + ":\n";

  current->head()->iterate(dir, [](LL *object)->bool {
    static_cast<Node*>(object)->print();
    return true;
  });
}

int main(int argc, char *argv[]) {

  mt_uti::CLI_Parser<int> parser(
    argc, argv, {"-name"}, {"-amount"}
  );

  // minimum value is 1
  int count = parser.CLI_NumberParser::last("-amount");

  // title as entry point
  if (parser.CLI_TitleParser::has("--test")) {

    if (!count) { // the amount is 0
      std::cerr << "\nPlease specify the 'amount' parameter\n";
      return 0;
    }

    Node *middle = nullptr;
    std::string name = parser.CLI_WordParser::last("-name");

    if (!name.empty()) name += ' ';

    // initialization
    Node *current = new Node(name + "1");

    // connecting
    for (int i = 1; i < count; i++) {
      current->accept(new Node(
        name + std::to_string(i+1)
      ));

      if (i == count / 2) middle = current;
      current = static_cast<Node*>(current->next());
    }

    if (current && middle) {

      // initial iterations
      iterateNodes(LL::RIGHT, current, "Initial[RIGHT]");
      iterateNodes(LL::LEFT, current, "Initial[LEFT]");

      /** Slice */

      Node *sliced = static_cast<Node*>(middle->slice());

      if (sliced) {
        iterateNodes(LL::RIGHT, sliced, "Sliced");
        iterateNodes(LL::RIGHT, middle, "Middle");
      }

      /** Merge */

      middle->merge(sliced);
      iterateNodes(LL::RIGHT, middle, "Middle merged to Sliced");
    }
    else std::cout << "\nJust a lonely " + name + "1\n";

    // deallocation
    current->annihilate();
  }
  else std::cerr << "\nUnknown entry title\n";

  return 0;
}

