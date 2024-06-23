#ifndef __UTILS__PRINTER_CPP__ 
#define __UTILS__PRINTER_CPP__

namespace util {

  template <typename T>
  std::string Printer<T>::combine(
    std::vector<T> &vec,
    int &step,
    std::string &title
  ) {
    if constexpr (!Types::isLetter<T>()) {
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
    std::vector<T> &vec,
    bool &asBar,
    int &step,
    std::string &title
  ) {
    if constexpr (!Types::isNumber<T>()) {
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
    std::vector<T> &vec,
    bool asBar,
    int step,
    std::string title
  ) {
    std::cout << Printer<T>::stringify(vec, asBar, step, title);
  }

  template <typename T>
  void Printer<T>::log(
    std::vector<T> &vec,
    bool asBar,
    std::string title
  ) {
    Printer<T>::log(vec, asBar, -1, title);
  }

  template <typename T>
  void Printer<T>::logf(
    std::vector<T> &vec,
    bool asBar,
    bool extended,
    int step,
    std::string title,
    std::string filename
  ) {
    std::ofstream writer;

    if (extended) {
      writer.open(filename, std::ios_base::app);
    }
    else writer.open(filename);

    writer << Printer<T>::stringify(vec, asBar, step, title);
    writer.close();
  }

  template <typename T>
  void Printer<T>::logf(
    std::vector<T> &vec,
    bool asBar,
    bool extended,
    std::string title,
    std::string filename
  ) {
    Printer<T>::logf(vec, asBar, extended, -1, title, filename);
  }
}

#endif // __UTILS__PRINTER_CPP__