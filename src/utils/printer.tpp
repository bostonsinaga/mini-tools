#ifndef __MINI_TOOLS__UTILS__PRINTER_TPP__
#define __MINI_TOOLS__UTILS__PRINTER_TPP__

#include "utils/file-tool.hpp"

namespace mini_tools {
namespace utils {

  template <inspector::ALPHANUMERIC T>
  std::string Printer::getHeader(CR_SZ endNewlinesCount) {

    std::string text = Printer::title + ": ";

    if constexpr (inspector::isNumber<T>()) {
      text += std::to_string(Printer::tag<T>);
    }
    else text += Printer::tag<T>;

    return Printer::getNewlines(text, endNewlinesCount);
  }

  template <inspector::ALPHANUMERIC T>
  std::string Printer::stringify(
    CR_VEC<T> vec,
    CR_SZ endNewlinesCount,
    CR_STR separator
  ) {
    std::string text;

    for (size_t i = 0; i < vec.size(); i++) {

      if constexpr (inspector::isNumber<T>()) {
        text += std::to_string(vec[i]) + separator;
      }
      else text += vec[i] + separator;
    }

    return Printer::getNewlines(text, endNewlinesCount);
  }

  template <inspector::NUMBER T>
  std::string Printer::barStringify(
    CR_VEC<T> vec,
    CR_SZ endNewlinesCount,
    CR_STR barStyle
  ) {
    std::string text;

    for (int i = 0; i < vec.size(); i++) {
      text += std::string(vec[i], barStyle) + "\n";
    }

    return Printer::getNewlines(text, endNewlinesCount);
  }

  template <inspector::ALPHANUMERIC T>
  void Printer::log(
    CR_VEC<T> vec,
    CR_SZ endNewlinesCount,
    CR_STR separator
  ) {
    std::cout << Printer::getHeader<T>(endNewlinesCount)
      << Printer::stringify<T>(vec, endNewlinesCount, separator);
  }

  template <inspector::NUMBER T>
  void Printer::barLog(
    CR_VEC<T> vec,
    CR_SZ endNewlinesCount,
    CR_STR barStyle
  ) {
    std::cout << Printer::getHeader<T>(endNewlinesCount)
      << Printer::barStringify<T>(vec, endNewlinesCount, barStyle);
  }

  template <inspector::ALPHANUMERIC T>
  bool Printer::writeFileString(
    CR_VEC<T> vec,
    CR_FS_PATH path,
    CR_BOL extended,
    CR_SZ endNewlinesCount,
    CR_STR separator
  ) {
    return Printer::writeFileString(
      Printer::stringify<T>(vec, endNewlinesCount, separator),
      path, extended, endNewlinesCount
    );
  }

  template <typename T>
  bool Printer::writeFileBinary(
    T data,
    CR_FS_PATH path,
    CR_BOL extended
  ) {
    FileTool::createNotExistFile(path);
    std::ofstream output;

    if (extended) {
      output.open(path, std::ios::binary | std::ios::app);
    }
    else output.open(path, std::ios::binary);

    if (output.is_open()) {
      output.write(reinterpret_cast<char*>(&data), sizeof(T));
      output.close();
      return true;
    }

    return false;
  }

  template <inspector::ALPHANUMERIC T>
  bool Printer::logf(
    CR_VEC<T> vec,
    CR_FS_PATH path,
    CR_BOL extended,
    CR_SZ endNewlinesCount,
    CR_STR separator
  ) {
    return Printer::writeFileString(
      Printer::getHeader<T>(endNewlinesCount) +
      Printer::stringify<T>(vec, endNewlinesCount, separator),
      path, extended, endNewlinesCount
    );
  }

  template <inspector::NUMBER T>
  bool Printer::barLogf(
    CR_VEC<T> vec,
    CR_FS_PATH path,
    CR_BOL extended,
    CR_SZ endNewlinesCount,
    CR_STR barStyle
  ) {
    return Printer::writeFileString(
      Printer::getHeader<T>(endNewlinesCount) +
      Printer::barStringify<T>(vec, endNewlinesCount, barStyle),
      path, extended, endNewlinesCount
    );
  }
}}

#endif // __MINI_TOOLS__UTILS__PRINTER_TPP__