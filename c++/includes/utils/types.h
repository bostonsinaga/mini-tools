#ifndef __UTILS__TYPES_H__
#define __UTILS__TYPES_H__

#include <iostream>
#include <fstream>
#include <vector>

namespace util {
  namespace Types {

    template <typename T>
    constexpr bool isLetter() {
      return
        std::is_same<T, char>::value ||
        std::is_same<T, wchar_t>::value ||
        std::is_same<T, std::string>::value;
    }

    template <typename T>
    constexpr bool isNumber() {
      if (!isLetter<T>()) {
        return
          std::is_integral<T>::value ||
          std::is_floating_point<T>::value;
      }
      return false;
    }
  }
}

#endif // __UTILS__TYPES_H__