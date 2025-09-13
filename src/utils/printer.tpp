#ifndef __MINI_TOOLS__UTILS__PRINTER_TPP__
#define __MINI_TOOLS__UTILS__PRINTER_TPP__

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
  bool Printer::write(
    CR_VEC<T> vec,
    CR_FS_PATH filename,
    CR_BOL extended,
    CR_SZ endNewlinesCount,
    CR_STR separator
  ) {
    return Printer::write(
      Printer::stringify<T>(vec, endNewlinesCount, separator),
      filename, extended, endNewlinesCount
    );
  }

  template <inspector::ALPHANUMERIC T>
  bool Printer::logf(
    CR_VEC<T> vec,
    CR_FS_PATH filename,
    CR_BOL extended,
    CR_SZ endNewlinesCount,
    CR_STR separator
  ) {
    return Printer::write(
      Printer::getHeader<T>(endNewlinesCount) +
      Printer::stringify<T>(vec, endNewlinesCount, separator),
      filename, extended, endNewlinesCount
    );
  }

  template <inspector::NUMBER T>
  bool Printer::barLogf(
    CR_VEC<T> vec,
    CR_FS_PATH filename,
    CR_BOL extended,
    CR_SZ endNewlinesCount,
    CR_STR barStyle
  ) {
    return Printer::write(
      Printer::getHeader<T>(endNewlinesCount) +
      Printer::barStringify<T>(vec, endNewlinesCount, barStyle),
      filename, extended, endNewlinesCount
    );
  }
}}

#endif // __MINI_TOOLS__UTILS__PRINTER_TPP__