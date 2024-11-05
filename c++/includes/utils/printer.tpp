#ifndef __MINI_TOOLS__UTILS__PRINTER_CPP__ 
#define __MINI_TOOLS__UTILS__PRINTER_CPP__

namespace mini_tools {
namespace utils {

  template <typename T>
  std::string Printer<T>::initText(
    CR_INT step,
    CR_STR title
  ) {
    if (step >= 0) {
      return title + ": " + std::to_string(step) + "\n";
    }
    return title + ":\n";
  }

  template <typename T>
  std::string Printer<T>::combine(
    CR_VEC<T> vec,
    CR_INT step,
    CR_STR title
  ) {
    if constexpr (!CheckType::isLetter<T>()) {
      constexpr bool stringify_and_combine_error = false;
      static_assert(stringify_and_combine_error, "only for numbers and letters");
    }
    else {
      std::string text = Printer<T>::initText(step, title);

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
    CR_INT step,
    CR_STR title
  ) {
    if constexpr (!CheckType::isNumber<T>()) {
      return Printer<T>::combine(vec, step, title);
    }
    else {
      std::string text = Printer<T>::initText(step, title);

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
    std::cout << Printer<T>::stringify(vec, asBar, step, title);
  }

  template <typename T>
  void Printer<T>::logf(
    CR_VEC<T> vec,
    CR_BOL asBar,
    CR_BOL extended,
    CR_STR filename,
    CR_STR title,
    CR_INT step
  ) {
    std::ofstream writer;

    if (extended) {
      writer.open(filename, std::ios_base::app);
    }
    else writer.open(filename);

    writer << Printer<T>::stringify(vec, asBar, step, title);
    writer.close();
  }
}}

#endif // __MINI_TOOLS__UTILS__PRINTER_CPP__