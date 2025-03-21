#ifndef __MINI_TOOLS__UTILS__PRINTER_TPP__
#define __MINI_TOOLS__UTILS__PRINTER_TPP__

namespace mini_tools {
namespace utils {

  template <typename T>
  std::string Printer<T>::initText(
    CR_STR title,
    CR_INT step
  ) {
    if (step >= 0) {
      return title + ": " + std::to_string(step) + "\n";
    }
    return title + ":\n";
  }

  template <typename T>
  std::string Printer<T>::combine(
    CR_VEC<T> vec,
    CR_STR title,
    CR_INT step
  ) {
    if constexpr (!CheckType::isLetter<T>()) {
      constexpr bool stringify_and_combine_error = false;
      static_assert(stringify_and_combine_error, "only for numbers and letters");
    }
    else {
      std::string text = Printer<T>::initText(title, step);

      for (int i = 0; i < vec.size(); i++) {
        text += vec[i] + ", ";
      }

      return text + "\n\n";
    }
  }

  template <typename T>
  std::string Printer<T>::stringify(
    CR_VEC<T> vec,
    CR_BOL asBar,
    CR_STR title,
    CR_INT step
  ) {
    if constexpr (!CheckType::isNumber<T>()) {
      return Printer<T>::combine(vec, step, title);
    }
    else {
      std::string text = Printer<T>::initText(title, step);

      if (asBar) {
        for (int i = 0; i < vec.size(); i++) {
          text += std::string(vec[i], '=') + "\n";
        }
        text += "\n";
      }
      else {
        for (int i = 0; i < vec.size(); i++) {
          text += std::to_string(vec[i]) + ", ";
        }
        text += "\n\n";
      }

      return text;
    }
  }

  template <typename T>
  void Printer<T>::log(
    CR_VEC<T> vec,
    CR_BOL asBar,
    CR_STR title,
    CR_INT step
  ) {
    std::cout << Printer<T>::stringify(vec, asBar, title, step);
  }

  template <typename T>
  void Printer<T>::logf(
    CR_VEC<T> vec,
    CR_STR filename,
    CR_BOL asBar,
    CR_BOL extended,
    CR_STR title,
    CR_INT step
  ) {
    std::ofstream writer;

    if (extended) {
      writer.open(filename, std::ios_base::app);
    }
    else writer.open(filename);

    writer << Printer<T>::stringify(vec, asBar, title, step);
    writer.close();
  }
}}

#endif // __MINI_TOOLS__UTILS__PRINTER_TPP__