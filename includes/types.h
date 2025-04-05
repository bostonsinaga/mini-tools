#ifndef __MINI_TOOLS__TYPES_H__
#define __MINI_TOOLS__TYPES_H__

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <type_traits>
#include <concepts>
#include <filesystem>

namespace mini_tools {

  /** TYPE CHECKERS */

  namespace inspector {

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

    template <typename T>
    constexpr bool notNullptr() {
      return !std::is_same<T, std::nullptr_t>::value;
    }

    template <typename T>
    concept LETTER = std::is_same_v<T, char> || std::is_same_v<T, wchar_t> || std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring>;

    template <typename T>
    concept NUMBER = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <typename T>
    concept ALPHANUMERIC = LETTER<T> || NUMBER<T>;

    template <typename T>
    concept NOT_NULLPTR = !std::is_same_v<T, std::nullptr_t>;
  }

  /** SHORTENED PRIMITIVE DATA TYPES */

  typedef short int SI;
  typedef long int LI;
  typedef long long int LLI;
  typedef unsigned short int USI;
  typedef unsigned int UI;
  typedef unsigned long int ULI;
  typedef unsigned long long int ULLI;
  typedef long double LD;

  /** SHORTENED VECTOR TEMPLATES */

  template <typename T>
  using CR = const T&;

  template <typename T>
  using VEC = std::vector<T>;

  template <typename T>
  using VEC2 = std::vector<VEC<T>>;

  template <typename T>
  using CR_VEC = const VEC<T>&;

  template <typename T>
  using CR_VEC2 = const VEC2<T>&;

  /** SHORTENED VECTOR ARRAY TEMPLATES */

  template <typename T, size_t N>
  using ARR = std::array<T, N>;

  template <typename T, size_t N>
  using CR_ARR = const ARR<T, N>&;

  template <typename T, size_t N>
  using VEC_ARR = VEC<ARR<T, N>>;

  template <typename T, size_t N>
  using VEC_ARR2 = VEC<VEC_ARR<T, N>>;

  template <typename T, size_t N>
  using CR_VEC_ARR = const VEC_ARR<T, N>&;

  template <typename T, size_t N>
  using CR_VEC_ARR2 = const VEC_ARR2<T, N>&;

  /** SHORTENED PAIR TEMPLATES */

  template <typename T>
  using PAIR = std::pair<T, T>;

  template <typename T>
  using CR_PAIR = const PAIR<T>&;

  template <typename T, typename U>
  using PAIR2 = std::pair<T, U>;

  template <typename T, typename U>
  using CR_PAIR2 = const PAIR2<T, U>&;

  template <typename T>
  using VEC_PAIR = VEC<PAIR<T>>;

  template <typename T>
  using CR_VEC_PAIR = const VEC_PAIR<T>&;

  template <typename T, typename U>
  using VEC_PAIR2 = VEC<PAIR2<T, U>>;

  template <typename T, typename U>
  using CR_VEC_PAIR2 = const VEC_PAIR2<T, U>&;

  /** SHORTENED VALUE VECTORS */

  typedef VEC<bool> VEC_BOL;
  typedef VEC<std::string> VEC_STR;
  typedef VEC<char> VEC_CH;
  typedef VEC<wchar_t> VEC_WCH;
  typedef VEC<int> VEC_INT;
  typedef VEC<SI> VEC_SI;
  typedef VEC<LI> VEC_LI;
  typedef VEC<LLI> VEC_LLI;
  typedef VEC<USI> VEC_USI;
  typedef VEC<UI> VEC_UI;
  typedef VEC<ULI> VEC_ULI;
  typedef VEC<ULLI> VEC_ULLI;
  typedef VEC<size_t> VEC_SZ;
  typedef VEC<time_t> VEC_TM;
  typedef VEC<float> VEC_FLT;
  typedef VEC<double> VEC_DBL;
  typedef VEC<LD> VEC_LD;

  typedef VEC<VEC_BOL> VEC2_BOL;
  typedef VEC<VEC_STR> VEC2_STR;
  typedef VEC<VEC_CH> VEC2_CH;
  typedef VEC<VEC_WCH> VEC2_WCH;
  typedef VEC<VEC_INT> VEC2_INT;
  typedef VEC<VEC_SI> VEC2_SI;
  typedef VEC<VEC_LI> VEC2_LI;
  typedef VEC<VEC_LLI> VEC2_LLI;
  typedef VEC<VEC_USI> VEC2_USI;
  typedef VEC<VEC_UI> VEC2_UI;
  typedef VEC<VEC_ULI> VEC2_ULI;
  typedef VEC<VEC_ULLI> VEC2_ULLI;
  typedef VEC<VEC_SZ> VEC2_SZ;
  typedef VEC<VEC_TM> VEC2_TM;
  typedef VEC<VEC_FLT> VEC2_FLT;
  typedef VEC<VEC_DBL> VEC2_DBL;
  typedef VEC<VEC_LD> VEC2_LD;

  /** SHORTENED POINTER VECTORS */

  typedef VEC<bool*> VEC_BOL_P;
  typedef VEC<std::string*> VEC_STR_P;
  typedef VEC<char*> VEC_CH_P;
  typedef VEC<wchar_t*> VEC_WCH_P;
  typedef VEC<int*> VEC_INT_P;
  typedef VEC<SI*> VEC_SI_P;
  typedef VEC<LI*> VEC_LI_P;
  typedef VEC<LLI*> VEC_LLI_P;
  typedef VEC<USI*> VEC_USI_P;
  typedef VEC<UI*> VEC_UI_P;
  typedef VEC<ULI*> VEC_ULI_P;
  typedef VEC<ULLI*> VEC_ULLI_P;
  typedef VEC<size_t*> VEC_SZ_P;
  typedef VEC<time_t*> VEC_TM_P;
  typedef VEC<float*> VEC_FLT_P;
  typedef VEC<double*> VEC_DBL_P;
  typedef VEC<LD*> VEC_LD_P;

  typedef VEC<VEC_BOL_P> VEC2_BOL_P;
  typedef VEC<VEC_STR_P> VEC2_STR_P;
  typedef VEC<VEC_CH_P> VEC2_CH_P;
  typedef VEC<VEC_WCH_P> VEC2_WCH_P;
  typedef VEC<VEC_INT_P> VEC2_INT_P;
  typedef VEC<VEC_SI_P> VEC2_SI_P;
  typedef VEC<VEC_LI_P> VEC2_LI_P;
  typedef VEC<VEC_LLI_P> VEC2_LLI_P;
  typedef VEC<VEC_USI_P> VEC2_USI_P;
  typedef VEC<VEC_UI_P> VEC2_UI_P;
  typedef VEC<VEC_ULI_P> VEC2_ULI_P;
  typedef VEC<VEC_ULLI_P> VEC2_ULLI_P;
  typedef VEC<VEC_SZ_P> VEC2_SZ_P;
  typedef VEC<VEC_TM_P> VEC2_TM_P;
  typedef VEC<VEC_FLT_P> VEC2_FLT_P;
  typedef VEC<VEC_DBL_P> VEC2_DBL_P;
  typedef VEC<VEC_LD_P> VEC2_LD_P;

  /** SHORTENED CONSTANT REFERENCES */

  typedef const bool& CR_BOL;
  typedef const std::string& CR_STR;
  typedef const char& CR_CH;
  typedef const wchar_t& CR_WCH;
  typedef const int& CR_INT;
  typedef const SI& CR_SI;
  typedef const LI& CR_LI;
  typedef const LLI& CR_LLI;
  typedef const USI& CR_USI;
  typedef const UI& CR_UI;
  typedef const ULI& CR_ULI;
  typedef const ULLI& CR_ULLI;
  typedef const size_t& CR_SZ;
  typedef const time_t& CR_TM;
  typedef const float& CR_FLT;
  typedef const double& CR_DBL;
  typedef const LD& CR_LD;

  /** SHORTENED CONSTANT REFERENCE VECTORS */

  typedef const VEC_BOL& CR_VEC_BOL;
  typedef const VEC_STR& CR_VEC_STR;
  typedef const VEC_CH& CR_VEC_CH;
  typedef const VEC_WCH& CR_VEC_WCH;
  typedef const VEC_INT& CR_VEC_INT;
  typedef const VEC_SI& CR_VEC_SI;
  typedef const VEC_LI& CR_VEC_LI;
  typedef const VEC_LLI& CR_VEC_LLI;
  typedef const VEC_USI& CR_VEC_USI;
  typedef const VEC_UI& CR_VEC_UI;
  typedef const VEC_ULI& CR_VEC_ULI;
  typedef const VEC_ULLI& CR_VEC_ULLI;
  typedef const VEC_SZ& CR_VEC_SZ;
  typedef const VEC_TM& CR_VEC_TM;
  typedef const VEC_FLT& CR_VEC_FLT;
  typedef const VEC_DBL& CR_VEC_DBL;
  typedef const VEC_LD& CR_VEC_LD;

  typedef const VEC2_BOL& CR_VEC2_BOL;
  typedef const VEC2_STR& CR_VEC2_STR;
  typedef const VEC2_CH& CR_VEC2_CH;
  typedef const VEC2_WCH& CR_VEC2_WCH;
  typedef const VEC2_INT& CR_VEC2_INT;
  typedef const VEC2_SI& CR_VEC2_SI;
  typedef const VEC2_LI& CR_VEC2_LI;
  typedef const VEC2_LLI& CR_VEC2_LLI;
  typedef const VEC2_USI& CR_VEC2_USI;
  typedef const VEC2_UI& CR_VEC2_UI;
  typedef const VEC2_ULI& CR_VEC2_ULI;
  typedef const VEC2_ULLI& CR_VEC2_ULLI;
  typedef const VEC2_SZ& CR_VEC2_SZ;
  typedef const VEC2_TM& CR_VEC2_TM;
  typedef const VEC2_FLT& CR_VEC2_FLT;
  typedef const VEC2_DBL& CR_VEC2_DBL;
  typedef const VEC2_LD& CR_VEC2_LD;

  /** SHORTENED CONSTANT REFERENCE POINTER VECTORS */

  typedef const VEC_BOL_P& CR_VEC_BOL_P;
  typedef const VEC_STR_P& CR_VEC_STR_P;
  typedef const VEC_CH_P& CR_VEC_CH_P;
  typedef const VEC_WCH_P& CR_VEC_WCH_P;
  typedef const VEC_INT_P& CR_VEC_INT_P;
  typedef const VEC_SI_P& CR_VEC_SI_P;
  typedef const VEC_LI_P& CR_VEC_LI_P;
  typedef const VEC_LLI_P& CR_VEC_LLI_P;
  typedef const VEC_USI_P& CR_VEC_USI_P;
  typedef const VEC_UI_P& CR_VEC_UI_P;
  typedef const VEC_ULI_P& CR_VEC_ULI_P;
  typedef const VEC_ULLI_P& CR_VEC_ULLI_P;
  typedef const VEC_SZ_P& CR_VEC_SZ_P;
  typedef const VEC_TM_P& CR_VEC_TM_P;
  typedef const VEC_FLT_P& CR_VEC_FLT_P;
  typedef const VEC_DBL_P& CR_VEC_DBL_P;
  typedef const VEC_LD_P& CR_VEC_LD_P;

  typedef const VEC2_BOL_P& CR_VEC2_BOL_P;
  typedef const VEC2_STR_P& CR_VEC2_STR_P;
  typedef const VEC2_CH_P& CR_VEC2_CH_P;
  typedef const VEC2_WCH_P& CR_VEC2_WCH_P;
  typedef const VEC2_INT_P& CR_VEC2_INT_P;
  typedef const VEC2_SI_P& CR_VEC2_SI_P;
  typedef const VEC2_LI_P& CR_VEC2_LI_P;
  typedef const VEC2_LLI_P& CR_VEC2_LLI_P;
  typedef const VEC2_USI_P& CR_VEC2_USI_P;
  typedef const VEC2_UI_P& CR_VEC2_UI_P;
  typedef const VEC2_ULI_P& CR_VEC2_ULI_P;
  typedef const VEC2_ULLI_P& CR_VEC2_ULLI_P;
  typedef const VEC2_SZ_P& CR_VEC2_SZ_P;
  typedef const VEC2_TM_P& CR_VEC2_TM_P;
  typedef const VEC2_FLT_P& CR_VEC2_FLT_P;
  typedef const VEC2_DBL_P& CR_VEC2_DBL_P;
  typedef const VEC2_LD_P& CR_VEC2_LD_P;
}

#endif // __MINI_TOOLS__TYPES_H__