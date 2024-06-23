#ifndef __MINI_TOOLS__UTILS__PRINTER_H__
#define __MINI_TOOLS__UTILS__PRINTER_H__

namespace mini_tools {
namespace utils {

  template <class T>
  class Printer {
  private:
    static std::string initText(int &step, std::string &title) {
      if (step >= 0) {
        return title + ": " + std::to_string(step) + "\n";
      }
      return title + ":\n";
    }

    static std::string combine(
      std::vector<T> &vec,
      int &step,
      std::string &title
    );

    static std::string stringify(
      std::vector<T> &vec,
      bool &asBar,
      int &step,
      std::string &title
    );

  public:
    static void log(
      std::vector<T> &vec,
      bool asBar,
      int step,
      std::string title = "Step"
    );

    static void log(
      std::vector<T> &vec,
      bool asBar,
      std::string title = "Result"
    );

    static void logf(
      std::vector<T> &vec,
      bool asBar,
      bool extended, // 'false' will overwrite
      int step,
      std::string title = "Step",
      std::string filename
    );

    static void logf(
      std::vector<T> &vec,
      bool asBar,
      bool extended, // 'false' will overwrite
      std::string title = "Result",
      std::string filename
    );
  };
}}

#include "printer.cpp"
#endif // __MINI_TOOLS__UTILS__PRINTER_H__