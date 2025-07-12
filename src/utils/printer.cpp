#ifndef __MINI_TOOLS__UTILS__PRINTER_CPP__
#define __MINI_TOOLS__UTILS__PRINTER_CPP__

#include "utils/printer.hpp"

namespace mini_tools {
namespace utils {

  std::string Printer::getNewlines(
    CR_STR text,
    CR_SZ endNewlinesCount
  ) {
    return text + std::string(endNewlinesCount, '\n');
  }

  void Printer::write(
    CR_STR text,
    CR_FS_PATH filename,
    CR_BOL extended,
    CR_SZ endNewlinesCount
  ) {
    std::ofstream output;

    if (extended) {
      output.open(filename, std::ios_base::app);
    }
    else output.open(filename);

    output << Printer::getNewlines(text, endNewlinesCount);
    output.close();
  }
}}

#endif // __MINI_TOOLS__UTILS__PRINTER_CPP__