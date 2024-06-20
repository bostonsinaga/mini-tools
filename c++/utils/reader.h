#ifndef __UTILS__READER_H__
#define __UTILS__READER_H__

#include <fstream>

namespace utils {

  class Reader {
  public:
    static std::vector<int> txtToNumbers(
      std::string filename = "sample.txt"
    ) {
      /** Read file */

      std::ifstream reader(filename);
      std::string text, line;

      while (std::getline(reader, line)) { text += line; }
      reader.close();

      /** Convert to numbers */

      std::vector<int> numbers;
      std::string numStr;

      for (int i = 0; i < text.length(); i++) {
        if (std::isdigit(text[i])) {
          numStr += text[i];
        }
        else if (text[i] == ' ' || i == text.length() - 1) {
          numbers.push_back(std::stoi(numStr));
          numStr = "";
        }
      }

      return numbers;
    }
  };
}

#endif // __UTILS__READER_H__