#include <iostream>

/**
 * Print status label in blue color.
 */
int main(int argc, char *argv[]) {

  std::cout << "\x1b[34m";

  for (int i = 1; i < argc; i++) {
    std::cout << argv[i] << ' ';
  }

  std::cout << "\x1b[0m";

  return 0;
}
