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

  bool Printer::write(
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

    // invalid path, invalid filename, permission not granted, or disk full
    if (!output.is_open()) return false;

    // write text into file
    output << Printer::getNewlines(text, endNewlinesCount);
    output.close();
    return true;
  }
}}

#endif // __MINI_TOOLS__UTILS__PRINTER_CPP__