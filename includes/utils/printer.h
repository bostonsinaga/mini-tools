#ifndef __MINI_TOOLS__UTILS__PRINTER_H__
#define __MINI_TOOLS__UTILS__PRINTER_H__

namespace mini_tools {
namespace utils {

  template <class T>
  class Printer {
  private:
    static std::string initText(
      CR_STR title,
      CR_INT step
    );

    static std::string combine(
      CR_VEC<T> vec,
      CR_STR title,
      CR_INT step
    );

    static std::string stringify(
      CR_VEC<T> vec,
      CR_BOL asBar,
      CR_STR title,
      CR_INT step
    );

  public:
    static void log(
      CR_VEC<T> vec,
      CR_BOL asBar,
      CR_STR title = "Step",
      CR_INT step = -1
    );

    /**
     * Set the 'extended' parameter to determine
     * whether to overwrite or continue the file.
     */

    static void logf(
      CR_VEC<T> vec,
      CR_STR filename,
      CR_BOL asBar,
      CR_BOL extended,
      CR_STR title = "Step",
      CR_INT step = -1
    );

    static void write(
      CR_VEC<T> vec,
      CR_STR filename,
      CR_BOL extended
    ) {
      Printer<T>::logf(
        vec, filename, false, extended, ""
      );
    }
  };
}}

#include "utils/printer.tpp"
#endif // __MINI_TOOLS__UTILS__PRINTER_H__