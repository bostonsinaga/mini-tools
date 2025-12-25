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

  bool Printer::writeFileString(
    CR_STR text,
    CR_FS_PATH path,
    CR_BOL extended,
    CR_SZ endNewlinesCount
  ) {
    std::ofstream output;

    if (extended) {
      output.open(path, std::ios::app);
    }
    else output.open(path);

    // invalid path, invalid filename, permission not granted, or disk full
    if (!output.is_open()) return false;

    // write text into file
    output << Printer::getNewlines(text, endNewlinesCount);
    output.close();
    return true;
  }
}}

#endif // __MINI_TOOLS__UTILS__PRINTER_CPP__