#ifndef __MINI_TOOLS__TYPES_HPP__
#define __MINI_TOOLS__TYPES_HPP__

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <random>
#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
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
        std::is_same_v<T, char> ||
        std::is_same_v<T, wchar_t> ||
        std::is_same_v<T, std::string>;
    }

    template <typename T>
    constexpr bool isNumber() {
      if constexpr (!isLetter<T>()) {
        return
          std::is_integral_v<T> ||
          std::is_floating_point_v<T>;
      }
      return false;
    }

    template <typename T>
    constexpr bool isPointer() {
      return std::is_pointer_v<T>;
    }

    template <typename T>
    constexpr bool notNullptr() {
      return !std::is_same_v<T, std::nullptr_t>;
    }

    template <typename T>
    concept LETTER =
      std::is_same_v<T, char> ||
      std::is_same_v<T, wchar_t> ||
      std::is_same_v<T, std::string> ||
      std::is_same_v<T, std::wstring>;

    template <typename T>
    concept INTEGRAL =
      std::is_integral_v<T> &&
      !std::is_same_v<T, bool> &&
      !std::is_same_v<T, char> &&
      !std::is_same_v<T, wchar_t>;

    template <typename T>
    concept FLOATING_POINT = std::is_floating_point_v<T>;

    template <typename T>
    concept NUMBER = INTEGRAL<T> || FLOATING_POINT<T>;

    template <typename T>
    concept ALPHANUMERIC = LETTER<T> || NUMBER<T>;

    template <typename T>
    concept NOT_NULLPTR = !std::is_same_v<T, std::nullptr_t>;
  }

  /**
   * Floating point precisions based on IEEE 754 standard:
   * - Float = 6-7 digits.
   * - Double = 15-17 digits.
   * - Long Double = 19-21 digits.
   */
  enum PRECISION_ENUM {
    FLT_PRECISION = 6,
    DBL_PRECISION = 15,
    LD_PRECISION = 19
  };

  /** SHORTENED PRIMITIVE DATA TYPES */

  typedef short int SI;
  typedef long int LI;
  typedef long long int LLI;
  typedef unsigned short int USI;
  typedef unsigned int UI;
  typedef unsigned long int ULI;
  typedef unsigned long long int ULLI;
  typedef long double LD;

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

  /** SHORTENED FILESYSTEM NAMES */

  namespace FS = std::filesystem;
  typedef FS::path FS_PATH;
  typedef const FS_PATH& CR_FS_PATH;

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

  /** SHORTENED ARRAY TEMPLATES */

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

  /** SHORTENED CONSTANT REFERENCE VALUE VECTORS */

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

  /** SHORTENED VALUE PAIRS */

  typedef PAIR<bool> PAIR_BOL;
  typedef PAIR<std::string> PAIR_STR;
  typedef PAIR<char> PAIR_CH;
  typedef PAIR<wchar_t> PAIR_WCH;
  typedef PAIR<int> PAIR_INT;
  typedef PAIR<SI> PAIR_SI;
  typedef PAIR<LI> PAIR_LI;
  typedef PAIR<LLI> PAIR_LLI;
  typedef PAIR<USI> PAIR_USI;
  typedef PAIR<UI> PAIR_UI;
  typedef PAIR<ULI> PAIR_ULI;
  typedef PAIR<ULLI> PAIR_ULLI;
  typedef PAIR<size_t> PAIR_SZ;
  typedef PAIR<time_t> PAIR_TM;
  typedef PAIR<float> PAIR_FLT;
  typedef PAIR<double> PAIR_DBL;
  typedef PAIR<LD> PAIR_LD;

  /** SHORTENED POINTER PAIRS */

  typedef PAIR<bool*> PAIR_BOL_P;
  typedef PAIR<std::string*> PAIR_STR_P;
  typedef PAIR<char*> PAIR_CH_P;
  typedef PAIR<wchar_t*> PAIR_WCH_P;
  typedef PAIR<int*> PAIR_INT_P;
  typedef PAIR<SI*> PAIR_SI_P;
  typedef PAIR<LI*> PAIR_LI_P;
  typedef PAIR<LLI*> PAIR_LLI_P;
  typedef PAIR<USI*> PAIR_USI_P;
  typedef PAIR<UI*> PAIR_UI_P;
  typedef PAIR<ULI*> PAIR_ULI_P;
  typedef PAIR<ULLI*> PAIR_ULLI_P;
  typedef PAIR<size_t*> PAIR_SZ_P;
  typedef PAIR<time_t*> PAIR_TM_P;
  typedef PAIR<float*> PAIR_FLT_P;
  typedef PAIR<double*> PAIR_DBL_P;
  typedef PAIR<LD*> PAIR_LD_P;

  /** SHORTENED CONSTANT REFERENCE VALUE PAIRS */

  typedef const PAIR_BOL& CR_PAIR_BOL;
  typedef const PAIR_STR& CR_PAIR_STR;
  typedef const PAIR_CH& CR_PAIR_CH;
  typedef const PAIR_WCH& CR_PAIR_WCH;
  typedef const PAIR_INT& CR_PAIR_INT;
  typedef const PAIR_SI& CR_PAIR_SI;
  typedef const PAIR_LI& CR_PAIR_LI;
  typedef const PAIR_LLI& CR_PAIR_LLI;
  typedef const PAIR_USI& CR_PAIR_USI;
  typedef const PAIR_UI& CR_PAIR_UI;
  typedef const PAIR_ULI& CR_PAIR_ULI;
  typedef const PAIR_ULLI& CR_PAIR_ULLI;
  typedef const PAIR_SZ& CR_PAIR_SZ;
  typedef const PAIR_TM& CR_PAIR_TM;
  typedef const PAIR_FLT& CR_PAIR_FLT;
  typedef const PAIR_DBL& CR_PAIR_DBL;
  typedef const PAIR_LD& CR_PAIR_LD;

  /** SHORTENED CONSTANT REFERENCE POINTER PAIRS */

  typedef const PAIR_BOL_P& CR_PAIR_BOL_P;
  typedef const PAIR_STR_P& CR_PAIR_STR_P;
  typedef const PAIR_CH_P& CR_PAIR_CH_P;
  typedef const PAIR_WCH_P& CR_PAIR_WCH_P;
  typedef const PAIR_INT_P& CR_PAIR_INT_P;
  typedef const PAIR_SI_P& CR_PAIR_SI_P;
  typedef const PAIR_LI_P& CR_PAIR_LI_P;
  typedef const PAIR_LLI_P& CR_PAIR_LLI_P;
  typedef const PAIR_USI_P& CR_PAIR_USI_P;
  typedef const PAIR_UI_P& CR_PAIR_UI_P;
  typedef const PAIR_ULI_P& CR_PAIR_ULI_P;
  typedef const PAIR_ULLI_P& CR_PAIR_ULLI_P;
  typedef const PAIR_SZ_P& CR_PAIR_SZ_P;
  typedef const PAIR_TM_P& CR_PAIR_TM_P;
  typedef const PAIR_FLT_P& CR_PAIR_FLT_P;
  typedef const PAIR_DBL_P& CR_PAIR_DBL_P;
  typedef const PAIR_LD_P& CR_PAIR_LD_P;

  /** SHORTENED VALUE ARRAYS */

  template <size_t N>
  using ARR_BOL = ARR<bool, N>;

  template <size_t N>
  using ARR_STR = ARR<std::string, N>;

  template <size_t N>
  using ARR_CH = ARR<char, N>;

  template <size_t N>
  using ARR_WCH = ARR<wchar_t, N>;

  template <size_t N>
  using ARR_INT = ARR<int, N>;

  template <size_t N>
  using ARR_SI = ARR<SI, N>;

  template <size_t N>
  using ARR_LI = ARR<LI, N>;

  template <size_t N>
  using ARR_LLI = ARR<LLI, N>;

  template <size_t N>
  using ARR_USI = ARR<USI, N>;

  template <size_t N>
  using ARR_UI = ARR<UI, N>;

  template <size_t N>
  using ARR_ULI = ARR<ULI, N>;

  template <size_t N>
  using ARR_ULLI = ARR<ULLI, N>;

  template <size_t N>
  using ARR_SZ = ARR<size_t, N>;

  template <size_t N>
  using ARR_TM = ARR<time_t, N>;

  template <size_t N>
  using ARR_FLT = ARR<float, N>;

  template <size_t N>
  using ARR_DBL = ARR<double, N>;

  template <size_t N>
  using ARR_LD = ARR<LD, N>;

  template <size_t M, size_t N>
  using ARR2_BOL = ARR<ARR_BOL<M>, N>;

  template <size_t M, size_t N>
  using ARR2_STR = ARR<ARR_STR<M>, N>;

  template <size_t M, size_t N>
  using ARR2_CH = ARR<ARR_CH<M>, N>;

  template <size_t M, size_t N>
  using ARR2_WCH = ARR<ARR_WCH<M>, N>;

  template <size_t M, size_t N>
  using ARR2_INT = ARR<ARR_INT<M>, N>;

  template <size_t M, size_t N>
  using ARR2_SI = ARR<ARR_SI<M>, N>;

  template <size_t M, size_t N>
  using ARR2_LI = ARR<ARR_LI<M>, N>;

  template <size_t M, size_t N>
  using ARR2_LLI = ARR<ARR_LLI<M>, N>;

  template <size_t M, size_t N>
  using ARR2_USI = ARR<ARR_USI<M>, N>;

  template <size_t M, size_t N>
  using ARR2_UI = ARR<ARR_UI<M>, N>;

  template <size_t M, size_t N>
  using ARR2_ULI = ARR<ARR_ULI<M>, N>;

  template <size_t M, size_t N>
  using ARR2_ULLI = ARR<ARR_ULLI<M>, N>;

  template <size_t M, size_t N>
  using ARR2_SZ = ARR<ARR_SZ<M>, N>;

  template <size_t M, size_t N>
  using ARR2_TM = ARR<ARR_TM<M>, N>;

  template <size_t M, size_t N>
  using ARR2_FLT = ARR<ARR_FLT<M>, N>;

  template <size_t M, size_t N>
  using ARR2_DBL = ARR<ARR_DBL<M>, N>;

  template <size_t M, size_t N>
  using ARR2_LD = ARR<ARR_LD<M>, N>;

  /** SHORTENED POINTER ARRAYS */

  template <size_t N>
  using ARR_BOL_P = ARR<bool*, N>;

  template <size_t N>
  using ARR_STR_P = ARR<std::string*, N>;

  template <size_t N>
  using ARR_CH_P = ARR<char*, N>;

  template <size_t N>
  using ARR_WCH_P = ARR<wchar_t*, N>;

  template <size_t N>
  using ARR_INT_P = ARR<int*, N>;

  template <size_t N>
  using ARR_SI_P = ARR<SI*, N>;

  template <size_t N>
  using ARR_LI_P = ARR<LI*, N>;

  template <size_t N>
  using ARR_LLI_P = ARR<LLI*, N>;

  template <size_t N>
  using ARR_USI_P = ARR<USI*, N>;

  template <size_t N>
  using ARR_UI_P = ARR<UI*, N>;

  template <size_t N>
  using ARR_ULI_P = ARR<ULI*, N>;

  template <size_t N>
  using ARR_ULLI_P = ARR<ULLI*, N>;

  template <size_t N>
  using ARR_SZ_P = ARR<size_t*, N>;

  template <size_t N>
  using ARR_TM_P = ARR<time_t*, N>;

  template <size_t N>
  using ARR_FLT_P = ARR<float*, N>;

  template <size_t N>
  using ARR_DBL_P = ARR<double*, N>;

  template <size_t N>
  using ARR_LD_P = ARR<LD*, N>;

  template <size_t M, size_t N>
  using ARR2_BOL_P = ARR<ARR_BOL_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_STR_P = ARR<ARR_STR_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_CH_P = ARR<ARR_CH_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_WCH_P = ARR<ARR_WCH_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_INT_P = ARR<ARR_INT_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_SI_P = ARR<ARR_SI_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_LI_P = ARR<ARR_LI_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_LLI_P = ARR<ARR_LLI_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_USI_P = ARR<ARR_USI_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_UI_P = ARR<ARR_UI_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_ULI_P = ARR<ARR_ULI_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_ULLI_P = ARR<ARR_ULLI_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_SZ_P = ARR<ARR_SZ_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_TM_P = ARR<ARR_TM_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_FLT_P = ARR<ARR_FLT_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_DBL_P = ARR<ARR_DBL_P<M>, N>;

  template <size_t M, size_t N>
  using ARR2_LD_P = ARR<ARR_LD_P<M>, N>;

  /** SHORTENED CONSTANT REFERENCE VALUE ARRAYS */

  template <size_t N>
  using CR_ARR_BOL = const ARR_BOL<N>&;

  template <size_t N>
  using CR_ARR_STR = const ARR_STR<N>&;

  template <size_t N>
  using CR_ARR_CH = const ARR_CH<N>&;

  template <size_t N>
  using CR_ARR_WCH = const ARR_WCH<N>&;

  template <size_t N>
  using CR_ARR_INT = const ARR_INT<N>&;

  template <size_t N>
  using CR_ARR_SI = const ARR_SI<N>&;

  template <size_t N>
  using CR_ARR_LI = const ARR_LI<N>&;

  template <size_t N>
  using CR_ARR_LLI = const ARR_LLI<N>&;

  template <size_t N>
  using CR_ARR_USI = const ARR_USI<N>&;

  template <size_t N>
  using CR_ARR_UI = const ARR_UI<N>&;

  template <size_t N>
  using CR_ARR_ULI = const ARR_ULI<N>&;

  template <size_t N>
  using CR_ARR_ULLI = const ARR_ULLI<N>&;

  template <size_t N>
  using CR_ARR_SZ = const ARR_SZ<N>&;

  template <size_t N>
  using CR_ARR_TM = const ARR_TM<N>&;

  template <size_t N>
  using CR_ARR_FLT = const ARR_FLT<N>&;

  template <size_t N>
  using CR_ARR_DBL = const ARR_DBL<N>&;

  template <size_t N>
  using CR_ARR_LD = const ARR_LD<N>&;

  template <size_t M, size_t N>
  using CR_ARR2_BOL = const ARR2_BOL<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_STR = const ARR2_STR<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_CH = const ARR2_CH<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_WCH = const ARR2_WCH<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_INT = const ARR2_INT<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_SI = const ARR2_SI<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_LI = const ARR2_LI<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_LLI = const ARR2_LLI<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_USI = const ARR2_USI<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_UI = const ARR2_UI<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_ULI = const ARR2_ULI<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_ULLI = const ARR2_ULLI<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_SZ = const ARR2_SZ<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_TM = const ARR2_TM<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_FLT = const ARR2_FLT<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_DBL = const ARR2_DBL<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_LD = const ARR2_LD<M, N>&;

  /** SHORTENED CONSTANT REFERENCE POINTER ARRAYS */

  template <size_t N>
  using CR_ARR_BOL_P = const ARR_BOL_P<N>&;

  template <size_t N>
  using CR_ARR_STR_P = const ARR_STR_P<N>&;

  template <size_t N>
  using CR_ARR_CH_P = const ARR_CH_P<N>&;

  template <size_t N>
  using CR_ARR_WCH_P = const ARR_WCH_P<N>&;

  template <size_t N>
  using CR_ARR_INT_P = const ARR_INT_P<N>&;

  template <size_t N>
  using CR_ARR_SI_P = const ARR_SI_P<N>&;

  template <size_t N>
  using CR_ARR_LI_P = const ARR_LI_P<N>&;

  template <size_t N>
  using CR_ARR_LLI_P = const ARR_LLI_P<N>&;

  template <size_t N>
  using CR_ARR_USI_P = const ARR_USI_P<N>&;

  template <size_t N>
  using CR_ARR_UI_P = const ARR_UI_P<N>&;

  template <size_t N>
  using CR_ARR_ULI_P = const ARR_ULI_P<N>&;

  template <size_t N>
  using CR_ARR_ULLI_P = const ARR_ULLI_P<N>&;

  template <size_t N>
  using CR_ARR_SZ_P = const ARR_SZ_P<N>&;

  template <size_t N>
  using CR_ARR_TM_P = const ARR_TM_P<N>&;

  template <size_t N>
  using CR_ARR_FLT_P = const ARR_FLT_P<N>&;

  template <size_t N>
  using CR_ARR_DBL_P = const ARR_DBL_P<N>&;

  template <size_t N>
  using CR_ARR_LD_P = const ARR_LD_P<N>&;

  template <size_t M, size_t N>
  using CR_ARR2_BOL_P = const ARR2_BOL_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_STR_P = const ARR2_STR_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_CH_P = const ARR2_CH_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_WCH_P = const ARR2_WCH_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_INT_P = const ARR2_INT_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_SI_P = const ARR2_SI_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_LI_P = const ARR2_LI_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_LLI_P = const ARR2_LLI_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_USI_P = const ARR2_USI_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_UI_P = const ARR2_UI_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_ULI_P = const ARR2_ULI_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_ULLI_P = const ARR2_ULLI_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_SZ_P = const ARR2_SZ_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_TM_P = const ARR2_TM_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_FLT_P = const ARR2_FLT_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_DBL_P = const ARR2_DBL_P<M, N>&;

  template <size_t M, size_t N>
  using CR_ARR2_LD_P = const ARR2_LD_P<M, N>&;

  /** SHORTENED ORDERED SET TEMPLATES */

  template <typename T>
  using ORSET = std::set<T>;

  template <typename T>
  using CR_ORSET = CR<ORSET<T>>;

  using ORSET_BOL = ORSET<bool>;
  using ORSET_STR = ORSET<std::string>;
  using ORSET_CH = ORSET<char>;
  using ORSET_WCH = ORSET<wchar_t>;
  using ORSET_INT = ORSET<int>;
  using ORSET_SI = ORSET<SI>;
  using ORSET_LI = ORSET<LI>;
  using ORSET_LLI = ORSET<LLI>;
  using ORSET_USI = ORSET<USI>;
  using ORSET_UI = ORSET<UI>;
  using ORSET_ULI = ORSET<ULI>;
  using ORSET_ULLI = ORSET<ULLI>;
  using ORSET_SZ = ORSET<size_t>;
  using ORSET_TM = ORSET<time_t>;
  using ORSET_FLT = ORSET<float>;
  using ORSET_DBL = ORSET<double>;
  using ORSET_LD = ORSET<LD>;

  using CR_ORSET_BOL = CR<ORSET_BOL>;
  using CR_ORSET_STR = CR<ORSET_STR>;
  using CR_ORSET_CH = CR<ORSET_CH>;
  using CR_ORSET_WCH = CR<ORSET_WCH>;
  using CR_ORSET_INT = CR<ORSET_INT>;
  using CR_ORSET_SI = CR<ORSET_SI>;
  using CR_ORSET_LI = CR<ORSET_LI>;
  using CR_ORSET_LLI = CR<ORSET_LLI>;
  using CR_ORSET_USI = CR<ORSET_USI>;
  using CR_ORSET_UI = CR<ORSET_UI>;
  using CR_ORSET_ULI = CR<ORSET_ULI>;
  using CR_ORSET_ULLI = CR<ORSET_ULLI>;
  using CR_ORSET_SZ = CR<ORSET_SZ>;
  using CR_ORSET_TM = CR<ORSET_TM>;
  using CR_ORSET_FLT = CR<ORSET_FLT>;
  using CR_ORSET_DBL = CR<ORSET_DBL>;
  using CR_ORSET_LD = CR<ORSET_LD>;

  using ORSET_BOL_P = ORSET<bool*>;
  using ORSET_STR_P = ORSET<std::string*>;
  using ORSET_CH_P = ORSET<char*>;
  using ORSET_WCH_P = ORSET<wchar_t*>;
  using ORSET_INT_P = ORSET<int*>;
  using ORSET_SI_P = ORSET<SI*>;
  using ORSET_LI_P = ORSET<LI*>;
  using ORSET_LLI_P = ORSET<LLI*>;
  using ORSET_USI_P = ORSET<USI*>;
  using ORSET_UI_P = ORSET<UI*>;
  using ORSET_ULI_P = ORSET<ULI*>;
  using ORSET_ULLI_P = ORSET<ULLI*>;
  using ORSET_SZ_P = ORSET<size_t*>;
  using ORSET_TM_P = ORSET<time_t*>;
  using ORSET_FLT_P = ORSET<float*>;
  using ORSET_DBL_P = ORSET<double*>;
  using ORSET_LD_P = ORSET<LD*>;

  using CR_ORSET_BOL_P = CR<ORSET_BOL_P>;
  using CR_ORSET_STR_P = CR<ORSET_STR_P>;
  using CR_ORSET_CH_P = CR<ORSET_CH_P>;
  using CR_ORSET_WCH_P = CR<ORSET_WCH_P>;
  using CR_ORSET_INT_P = CR<ORSET_INT_P>;
  using CR_ORSET_SI_P = CR<ORSET_SI_P>;
  using CR_ORSET_LI_P = CR<ORSET_LI_P>;
  using CR_ORSET_LLI_P = CR<ORSET_LLI_P>;
  using CR_ORSET_USI_P = CR<ORSET_USI_P>;
  using CR_ORSET_UI_P = CR<ORSET_UI_P>;
  using CR_ORSET_ULI_P = CR<ORSET_ULI_P>;
  using CR_ORSET_ULLI_P = CR<ORSET_ULLI_P>;
  using CR_ORSET_SZ_P = CR<ORSET_SZ_P>;
  using CR_ORSET_TM_P = CR<ORSET_TM_P>;
  using CR_ORSET_FLT_P = CR<ORSET_FLT_P>;
  using CR_ORSET_DBL_P = CR<ORSET_DBL_P>;
  using CR_ORSET_LD_P = CR<ORSET_LD_P>;

  /** SHORTENED UNORDERED SET TEMPLATES */

  template <typename T>
  using UNORSET = std::unordered_set<T>;

  template <typename T>
  using CR_UNORSET = CR<UNORSET<T>>;

  using UNORSET_BOL = UNORSET<bool>;
  using UNORSET_STR = UNORSET<std::string>;
  using UNORSET_CH = UNORSET<char>;
  using UNORSET_WCH = UNORSET<wchar_t>;
  using UNORSET_INT = UNORSET<int>;
  using UNORSET_SI = UNORSET<SI>;
  using UNORSET_LI = UNORSET<LI>;
  using UNORSET_LLI = UNORSET<LLI>;
  using UNORSET_USI = UNORSET<USI>;
  using UNORSET_UI = UNORSET<UI>;
  using UNORSET_ULI = UNORSET<ULI>;
  using UNORSET_ULLI = UNORSET<ULLI>;
  using UNORSET_SZ = UNORSET<size_t>;
  using UNORSET_TM = UNORSET<time_t>;
  using UNORSET_FLT = UNORSET<float>;
  using UNORSET_DBL = UNORSET<double>;
  using UNORSET_LD = UNORSET<LD>;

  using CR_UNORSET_BOL = CR<UNORSET_BOL>;
  using CR_UNORSET_STR = CR<UNORSET_STR>;
  using CR_UNORSET_CH = CR<UNORSET_CH>;
  using CR_UNORSET_WCH = CR<UNORSET_WCH>;
  using CR_UNORSET_INT = CR<UNORSET_INT>;
  using CR_UNORSET_SI = CR<UNORSET_SI>;
  using CR_UNORSET_LI = CR<UNORSET_LI>;
  using CR_UNORSET_LLI = CR<UNORSET_LLI>;
  using CR_UNORSET_USI = CR<UNORSET_USI>;
  using CR_UNORSET_UI = CR<UNORSET_UI>;
  using CR_UNORSET_ULI = CR<UNORSET_ULI>;
  using CR_UNORSET_ULLI = CR<UNORSET_ULLI>;
  using CR_UNORSET_SZ = CR<UNORSET_SZ>;
  using CR_UNORSET_TM = CR<UNORSET_TM>;
  using CR_UNORSET_FLT = CR<UNORSET_FLT>;
  using CR_UNORSET_DBL = CR<UNORSET_DBL>;
  using CR_UNORSET_LD = CR<UNORSET_LD>;

  using UNORSET_BOL_P = UNORSET<bool*>;
  using UNORSET_STR_P = UNORSET<std::string*>;
  using UNORSET_CH_P = UNORSET<char*>;
  using UNORSET_WCH_P = UNORSET<wchar_t*>;
  using UNORSET_INT_P = UNORSET<int*>;
  using UNORSET_SI_P = UNORSET<SI*>;
  using UNORSET_LI_P = UNORSET<LI*>;
  using UNORSET_LLI_P = UNORSET<LLI*>;
  using UNORSET_USI_P = UNORSET<USI*>;
  using UNORSET_UI_P = UNORSET<UI*>;
  using UNORSET_ULI_P = UNORSET<ULI*>;
  using UNORSET_ULLI_P = UNORSET<ULLI*>;
  using UNORSET_SZ_P = UNORSET<size_t*>;
  using UNORSET_TM_P = UNORSET<time_t*>;
  using UNORSET_FLT_P = UNORSET<float*>;
  using UNORSET_DBL_P = UNORSET<double*>;
  using UNORSET_LD_P = UNORSET<LD*>;

  using CR_UNORSET_BOL_P = CR<UNORSET_BOL_P>;
  using CR_UNORSET_STR_P = CR<UNORSET_STR_P>;
  using CR_UNORSET_CH_P = CR<UNORSET_CH_P>;
  using CR_UNORSET_WCH_P = CR<UNORSET_WCH_P>;
  using CR_UNORSET_INT_P = CR<UNORSET_INT_P>;
  using CR_UNORSET_SI_P = CR<UNORSET_SI_P>;
  using CR_UNORSET_LI_P = CR<UNORSET_LI_P>;
  using CR_UNORSET_LLI_P = CR<UNORSET_LLI_P>;
  using CR_UNORSET_USI_P = CR<UNORSET_USI_P>;
  using CR_UNORSET_UI_P = CR<UNORSET_UI_P>;
  using CR_UNORSET_ULI_P = CR<UNORSET_ULI_P>;
  using CR_UNORSET_ULLI_P = CR<UNORSET_ULLI_P>;
  using CR_UNORSET_SZ_P = CR<UNORSET_SZ_P>;
  using CR_UNORSET_TM_P = CR<UNORSET_TM_P>;
  using CR_UNORSET_FLT_P = CR<UNORSET_FLT_P>;
  using CR_UNORSET_DBL_P = CR<UNORSET_DBL_P>;
  using CR_UNORSET_LD_P = CR<UNORSET_LD_P>;

  /** SHORTENED ORDERED MAP TEMPLATES */

  template <typename T, typename U>
  using ORMAP = std::map<T, U>;

  template <typename T, typename U>
  using CR_ORMAP = CR<ORMAP<T, U>>;

  /** SHORTENED VALUE ORDERED MAPS */

  template <typename T>
  using ORMAP_BOL = ORMAP<bool, T>;

  template <typename T>
  using ORMAP_STR = ORMAP<std::string, T>;

  template <typename T>
  using ORMAP_CH = ORMAP<char, T>;

  template <typename T>
  using ORMAP_WCH = ORMAP<wchar_t, T>;

  template <typename T>
  using ORMAP_INT = ORMAP<int, T>;

  template <typename T>
  using ORMAP_SI = ORMAP<SI, T>;

  template <typename T>
  using ORMAP_LI = ORMAP<LI, T>;

  template <typename T>
  using ORMAP_LLI = ORMAP<LLI, T>;

  template <typename T>
  using ORMAP_USI = ORMAP<USI, T>;

  template <typename T>
  using ORMAP_UI = ORMAP<UI, T>;

  template <typename T>
  using ORMAP_ULI = ORMAP<ULI, T>;

  template <typename T>
  using ORMAP_ULLI = ORMAP<ULLI, T>;

  template <typename T>
  using ORMAP_SZ = ORMAP<size_t, T>;

  template <typename T>
  using ORMAP_TM = ORMAP<time_t, T>;

  template <typename T>
  using ORMAP_FLT = ORMAP<float, T>;

  template <typename T>
  using ORMAP_DBL = ORMAP<double, T>;

  template <typename T>
  using ORMAP_LD = ORMAP<LD, T>;

  /** SHORTENED CONSTANT REFERENCE VALUE ORDERED MAPS */

  template <typename T>
  using CR_ORMAP_BOL = CR<ORMAP_BOL<T>>;

  template <typename T>
  using CR_ORMAP_STR = CR<ORMAP_STR<T>>;

  template <typename T>
  using CR_ORMAP_CH = CR<ORMAP_CH<T>>;

  template <typename T>
  using CR_ORMAP_WCH = CR<ORMAP_WCH<T>>;

  template <typename T>
  using CR_ORMAP_INT = CR<ORMAP_INT<T>>;

  template <typename T>
  using CR_ORMAP_SI = CR<ORMAP_SI<T>>;

  template <typename T>
  using CR_ORMAP_LI = CR<ORMAP_LI<T>>;

  template <typename T>
  using CR_ORMAP_LLI = CR<ORMAP_LLI<T>>;

  template <typename T>
  using CR_ORMAP_USI = CR<ORMAP_USI<T>>;

  template <typename T>
  using CR_ORMAP_UI = CR<ORMAP_UI<T>>;

  template <typename T>
  using CR_ORMAP_ULI = CR<ORMAP_ULI<T>>;

  template <typename T>
  using CR_ORMAP_ULLI = CR<ORMAP_ULLI<T>>;

  template <typename T>
  using CR_ORMAP_SZ = CR<ORMAP_SZ<T>>;

  template <typename T>
  using CR_ORMAP_TM = CR<ORMAP_TM<T>>;

  template <typename T>
  using CR_ORMAP_FLT = CR<ORMAP_FLT<T>>;

  template <typename T>
  using CR_ORMAP_DBL = CR<ORMAP_DBL<T>>;

  template <typename T>
  using CR_ORMAP_LD = CR<ORMAP_LD<T>>;

  /** SHORTENED POINTER ORDERED MAPS */

  template <typename T>
  using ORMAP_BOL_P = ORMAP<bool*, T>;

  template <typename T>
  using ORMAP_STR_P = ORMAP<std::string*, T>;

  template <typename T>
  using ORMAP_CH_P = ORMAP<char*, T>;

  template <typename T>
  using ORMAP_WCH_P = ORMAP<wchar_t*, T>;

  template <typename T>
  using ORMAP_INT_P = ORMAP<int*, T>;

  template <typename T>
  using ORMAP_SI_P = ORMAP<SI*, T>;

  template <typename T>
  using ORMAP_LI_P = ORMAP<LI*, T>;

  template <typename T>
  using ORMAP_LLI_P = ORMAP<LLI*, T>;

  template <typename T>
  using ORMAP_USI_P = ORMAP<USI*, T>;

  template <typename T>
  using ORMAP_UI_P = ORMAP<UI*, T>;

  template <typename T>
  using ORMAP_ULI_P = ORMAP<ULI*, T>;

  template <typename T>
  using ORMAP_ULLI_P = ORMAP<ULLI*, T>;

  template <typename T>
  using ORMAP_SZ_P = ORMAP<size_t*, T>;

  template <typename T>
  using ORMAP_TM_P = ORMAP<time_t*, T>;

  template <typename T>
  using ORMAP_FLT_P = ORMAP<float*, T>;

  template <typename T>
  using ORMAP_DBL_P = ORMAP<double*, T>;

  template <typename T>
  using ORMAP_LD_P = ORMAP<LD*, T>;

  /** SHORTENED CONSTANT REFERENCE POINTER ORDERED MAPS */

  template <typename T>
  using CR_ORMAP_BOL_P = CR<ORMAP_BOL_P<T>>;

  template <typename T>
  using CR_ORMAP_STR_P = CR<ORMAP_STR_P<T>>;

  template <typename T>
  using CR_ORMAP_CH_P = CR<ORMAP_CH_P<T>>;

  template <typename T>
  using CR_ORMAP_WCH_P = CR<ORMAP_WCH_P<T>>;

  template <typename T>
  using CR_ORMAP_INT_P = CR<ORMAP_INT_P<T>>;

  template <typename T>
  using CR_ORMAP_SI_P = CR<ORMAP_SI_P<T>>;

  template <typename T>
  using CR_ORMAP_LI_P = CR<ORMAP_LI_P<T>>;

  template <typename T>
  using CR_ORMAP_LLI_P = CR<ORMAP_LLI_P<T>>;

  template <typename T>
  using CR_ORMAP_USI_P = CR<ORMAP_USI_P<T>>;

  template <typename T>
  using CR_ORMAP_UI_P = CR<ORMAP_UI_P<T>>;

  template <typename T>
  using CR_ORMAP_ULI_P = CR<ORMAP_ULI_P<T>>;

  template <typename T>
  using CR_ORMAP_ULLI_P = CR<ORMAP_ULLI_P<T>>;

  template <typename T>
  using CR_ORMAP_SZ_P = CR<ORMAP_SZ_P<T>>;

  template <typename T>
  using CR_ORMAP_TM_P = CR<ORMAP_TM_P<T>>;

  template <typename T>
  using CR_ORMAP_FLT_P = CR<ORMAP_FLT_P<T>>;

  template <typename T>
  using CR_ORMAP_DBL_P = CR<ORMAP_DBL_P<T>>;

  template <typename T>
  using CR_ORMAP_LD_P = CR<ORMAP_LD_P<T>>;

  /** SHORTENED UNORDERED MAP TEMPLATES */

  template <typename T, typename U>
  using UNORMAP = std::unordered_map<T, U>;

  template <typename T, typename U>
  using CR_UNORMAP = CR<UNORMAP<T, U>>;

  /** SHORTENED VALUE UNORDERED MAPS */

  template <typename T>
  using UNORMAP_BOL = UNORMAP<bool, T>;

  template <typename T>
  using UNORMAP_STR = UNORMAP<std::string, T>;

  template <typename T>
  using UNORMAP_CH = UNORMAP<char, T>;

  template <typename T>
  using UNORMAP_WCH = UNORMAP<wchar_t, T>;

  template <typename T>
  using UNORMAP_INT = UNORMAP<int, T>;

  template <typename T>
  using UNORMAP_SI = UNORMAP<SI, T>;

  template <typename T>
  using UNORMAP_LI = UNORMAP<LI, T>;

  template <typename T>
  using UNORMAP_LLI = UNORMAP<LLI, T>;

  template <typename T>
  using UNORMAP_USI = UNORMAP<USI, T>;

  template <typename T>
  using UNORMAP_UI = UNORMAP<UI, T>;

  template <typename T>
  using UNORMAP_ULI = UNORMAP<ULI, T>;

  template <typename T>
  using UNORMAP_ULLI = UNORMAP<ULLI, T>;

  template <typename T>
  using UNORMAP_SZ = UNORMAP<size_t, T>;

  template <typename T>
  using UNORMAP_TM = UNORMAP<time_t, T>;

  template <typename T>
  using UNORMAP_FLT = UNORMAP<float, T>;

  template <typename T>
  using UNORMAP_DBL = UNORMAP<double, T>;

  template <typename T>
  using UNORMAP_LD = UNORMAP<LD, T>;

  /** SHORTENED CONSTANT REFERENCE VALUE UNORDERED MAPS */

  template <typename T>
  using CR_UNORMAP_BOL = CR<UNORMAP_BOL<T>>;

  template <typename T>
  using CR_UNORMAP_STR = CR<UNORMAP_STR<T>>;

  template <typename T>
  using CR_UNORMAP_CH = CR<UNORMAP_CH<T>>;

  template <typename T>
  using CR_UNORMAP_WCH = CR<UNORMAP_WCH<T>>;

  template <typename T>
  using CR_UNORMAP_INT = CR<UNORMAP_INT<T>>;

  template <typename T>
  using CR_UNORMAP_SI = CR<UNORMAP_SI<T>>;

  template <typename T>
  using CR_UNORMAP_LI = CR<UNORMAP_LI<T>>;

  template <typename T>
  using CR_UNORMAP_LLI = CR<UNORMAP_LLI<T>>;

  template <typename T>
  using CR_UNORMAP_USI = CR<UNORMAP_USI<T>>;

  template <typename T>
  using CR_UNORMAP_UI = CR<UNORMAP_UI<T>>;

  template <typename T>
  using CR_UNORMAP_ULI = CR<UNORMAP_ULI<T>>;

  template <typename T>
  using CR_UNORMAP_ULLI = CR<UNORMAP_ULLI<T>>;

  template <typename T>
  using CR_UNORMAP_SZ = CR<UNORMAP_SZ<T>>;

  template <typename T>
  using CR_UNORMAP_TM = CR<UNORMAP_TM<T>>;

  template <typename T>
  using CR_UNORMAP_FLT = CR<UNORMAP_FLT<T>>;

  template <typename T>
  using CR_UNORMAP_DBL = CR<UNORMAP_DBL<T>>;

  template <typename T>
  using CR_UNORMAP_LD = CR<UNORMAP_LD<T>>;

  /** SHORTENED POINTER UNORDERED MAPS */

  template <typename T>
  using UNORMAP_BOL_P = UNORMAP<bool*, T>;

  template <typename T>
  using UNORMAP_STR_P = UNORMAP<std::string*, T>;

  template <typename T>
  using UNORMAP_CH_P = UNORMAP<char*, T>;

  template <typename T>
  using UNORMAP_WCH_P = UNORMAP<wchar_t*, T>;

  template <typename T>
  using UNORMAP_INT_P = UNORMAP<int*, T>;

  template <typename T>
  using UNORMAP_SI_P = UNORMAP<SI*, T>;

  template <typename T>
  using UNORMAP_LI_P = UNORMAP<LI*, T>;

  template <typename T>
  using UNORMAP_LLI_P = UNORMAP<LLI*, T>;

  template <typename T>
  using UNORMAP_USI_P = UNORMAP<USI*, T>;

  template <typename T>
  using UNORMAP_UI_P = UNORMAP<UI*, T>;

  template <typename T>
  using UNORMAP_ULI_P = UNORMAP<ULI*, T>;

  template <typename T>
  using UNORMAP_ULLI_P = UNORMAP<ULLI*, T>;

  template <typename T>
  using UNORMAP_SZ_P = UNORMAP<size_t*, T>;

  template <typename T>
  using UNORMAP_TM_P = UNORMAP<time_t*, T>;

  template <typename T>
  using UNORMAP_FLT_P = UNORMAP<float*, T>;

  template <typename T>
  using UNORMAP_DBL_P = UNORMAP<double*, T>;

  template <typename T>
  using UNORMAP_LD_P = UNORMAP<LD*, T>;

  /** SHORTENED CONSTANT REFERENCE POINTER UNORDERED MAPS */

  template <typename T>
  using CR_UNORMAP_BOL_P = CR<UNORMAP_BOL_P<T>>;

  template <typename T>
  using CR_UNORMAP_STR_P = CR<UNORMAP_STR_P<T>>;

  template <typename T>
  using CR_UNORMAP_CH_P = CR<UNORMAP_CH_P<T>>;

  template <typename T>
  using CR_UNORMAP_WCH_P = CR<UNORMAP_WCH_P<T>>;

  template <typename T>
  using CR_UNORMAP_INT_P = CR<UNORMAP_INT_P<T>>;

  template <typename T>
  using CR_UNORMAP_SI_P = CR<UNORMAP_SI_P<T>>;

  template <typename T>
  using CR_UNORMAP_LI_P = CR<UNORMAP_LI_P<T>>;

  template <typename T>
  using CR_UNORMAP_LLI_P = CR<UNORMAP_LLI_P<T>>;

  template <typename T>
  using CR_UNORMAP_USI_P = CR<UNORMAP_USI_P<T>>;

  template <typename T>
  using CR_UNORMAP_UI_P = CR<UNORMAP_UI_P<T>>;

  template <typename T>
  using CR_UNORMAP_ULI_P = CR<UNORMAP_ULI_P<T>>;

  template <typename T>
  using CR_UNORMAP_ULLI_P = CR<UNORMAP_ULLI_P<T>>;

  template <typename T>
  using CR_UNORMAP_SZ_P = CR<UNORMAP_SZ_P<T>>;

  template <typename T>
  using CR_UNORMAP_TM_P = CR<UNORMAP_TM_P<T>>;

  template <typename T>
  using CR_UNORMAP_FLT_P = CR<UNORMAP_FLT_P<T>>;

  template <typename T>
  using CR_UNORMAP_DBL_P = CR<UNORMAP_DBL_P<T>>;

  template <typename T>
  using CR_UNORMAP_LD_P = CR<UNORMAP_LD_P<T>>;

  /** Get default value for T */

  template <typename T>
  T getDefaultFromType(CR<std::function<T()>> customDefaultValueGetter = nullptr) {

    // default value for pointer
    if constexpr (inspector::isPointer<T>()) {
      return nullptr;
    }
    else {
      // custom default value callback
      if (customDefaultValueGetter) {
        return customDefaultValueGetter();
      }
      // this may error if T doesn't have default constructor
      return T();
    }
  }
}

#endif // __MINI_TOOLS__TYPES_HPP__