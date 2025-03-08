#ifndef __MINI_TOOLS__UTILS__PRINTER_H__
#define __MINI_TOOLS__UTILS__PRINTER_H__

namespace mini_tools {
namespace utils {

  template <class T>
  class Printer {
  private:
    static std::string initText(
      CR_INT step,
      CR_STR title
    );

    static std::string combine(
      CR_VEC<T> vec,
      CR_INT step,
      CR_STR title
    );

    static std::string stringify(
      CR_VEC<T> vec,
      CR_BOL asBar,
      CR_INT step,
      CR_STR title
    );

  public:
    static void log(
      CR_VEC<T> vec,
      CR_BOL asBar,
      CR_STR title = "Step",
      CR_INT step = -1
    );

    static void logf(
      CR_VEC<T> vec,
      CR_BOL asBar,
      CR_BOL extended, // 'false' will overwrite
      CR_STR filename,
      CR_STR title = "Step",
      CR_INT step = -1
    );
  };
}}

#include "utils/printer.tpp"
#endif // __MINI_TOOLS__UTILS__PRINTER_H__