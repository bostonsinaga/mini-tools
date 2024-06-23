#ifndef __UTILS__READER_H__
#define __UTILS__READER_H__

namespace util {

  namespace Reader {
    bool isSeparator(char &ch);

    void getFrom(
      std::string &filename,
      std::string &textHook
    );
  }

  template <class T>
  class Scanner {
  public:
    static std::vector<T> txtToNumbers(
      std::string filename = "resources/sample.txt"
    );

    static std::vector<T> txtToLetters(
      std::string filename = "resources/sample.txt"
    );
  };
}

#include "reader.cpp"
#endif // __UTILS__READER_H__