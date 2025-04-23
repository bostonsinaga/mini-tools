#ifndef __MINI_TOOLS__TYPES_HPP__
#define __MINI_TOOLS__TYPES_HPP__

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <utility>
#include <functional>
#include <type_traits>
#include <concepts>
#include <chrono>
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

  /** SHORTENED STRING UNORDERED MAP TEMPLATES */

  template <typename T>
  using STRUNORMAP = std::unordered_map<std::string, T>;

  template <typename T>
  using CR_STRUNORMAP = const STRUNORMAP<T>&;

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

  /** SHORTENED VALUE STRING UNORDERED MAPS */

  typedef STRUNORMAP<bool> STRUNORMAP_BOL;
  typedef STRUNORMAP<std::string> STRUNORMAP_STR;
  typedef STRUNORMAP<char> STRUNORMAP_CH;
  typedef STRUNORMAP<wchar_t> STRUNORMAP_WCH;
  typedef STRUNORMAP<int> STRUNORMAP_INT;
  typedef STRUNORMAP<SI> STRUNORMAP_SI;
  typedef STRUNORMAP<LI> STRUNORMAP_LI;
  typedef STRUNORMAP<LLI> STRUNORMAP_LLI;
  typedef STRUNORMAP<USI> STRUNORMAP_USI;
  typedef STRUNORMAP<UI> STRUNORMAP_UI;
  typedef STRUNORMAP<ULI> STRUNORMAP_ULI;
  typedef STRUNORMAP<ULLI> STRUNORMAP_ULLI;
  typedef STRUNORMAP<size_t> STRUNORMAP_SZ;
  typedef STRUNORMAP<time_t> STRUNORMAP_TM;
  typedef STRUNORMAP<float> STRUNORMAP_FLT;
  typedef STRUNORMAP<double> STRUNORMAP_DBL;
  typedef STRUNORMAP<LD> STRUNORMAP_LD;

  /** SHORTENED POINTER STRING UNORDERED MAPS */

  typedef STRUNORMAP<bool*> STRUNORMAP_BOL_P;
  typedef STRUNORMAP<std::string*> STRUNORMAP_STR_P;
  typedef STRUNORMAP<char*> STRUNORMAP_CH_P;
  typedef STRUNORMAP<wchar_t*> STRUNORMAP_WCH_P;
  typedef STRUNORMAP<int*> STRUNORMAP_INT_P;
  typedef STRUNORMAP<SI*> STRUNORMAP_SI_P;
  typedef STRUNORMAP<LI*> STRUNORMAP_LI_P;
  typedef STRUNORMAP<LLI*> STRUNORMAP_LLI_P;
  typedef STRUNORMAP<USI*> STRUNORMAP_USI_P;
  typedef STRUNORMAP<UI*> STRUNORMAP_UI_P;
  typedef STRUNORMAP<ULI*> STRUNORMAP_ULI_P;
  typedef STRUNORMAP<ULLI*> STRUNORMAP_ULLI_P;
  typedef STRUNORMAP<size_t*> STRUNORMAP_SZ_P;
  typedef STRUNORMAP<time_t*> STRUNORMAP_TM_P;
  typedef STRUNORMAP<float*> STRUNORMAP_FLT_P;
  typedef STRUNORMAP<double*> STRUNORMAP_DBL_P;
  typedef STRUNORMAP<LD*> STRUNORMAP_LD_P;

  /** SHORTENED CONSTANT REFERENCE VALUE STRING UNORDERED MAPS */

  typedef const STRUNORMAP_BOL& CR_STRUNORMAP_BOL;
  typedef const STRUNORMAP_STR& CR_STRUNORMAP_STR;
  typedef const STRUNORMAP_CH& CR_STRUNORMAP_CH;
  typedef const STRUNORMAP_WCH& CR_STRUNORMAP_WCH;
  typedef const STRUNORMAP_INT& CR_STRUNORMAP_INT;
  typedef const STRUNORMAP_SI& CR_STRUNORMAP_SI;
  typedef const STRUNORMAP_LI& CR_STRUNORMAP_LI;
  typedef const STRUNORMAP_LLI& CR_STRUNORMAP_LLI;
  typedef const STRUNORMAP_USI& CR_STRUNORMAP_USI;
  typedef const STRUNORMAP_UI& CR_STRUNORMAP_UI;
  typedef const STRUNORMAP_ULI& CR_STRUNORMAP_ULI;
  typedef const STRUNORMAP_ULLI& CR_STRUNORMAP_ULLI;
  typedef const STRUNORMAP_SZ& CR_STRUNORMAP_SZ;
  typedef const STRUNORMAP_TM& CR_STRUNORMAP_TM;
  typedef const STRUNORMAP_FLT& CR_STRUNORMAP_FLT;
  typedef const STRUNORMAP_DBL& CR_STRUNORMAP_DBL;
  typedef const STRUNORMAP_LD& CR_STRUNORMAP_LD;

  /** SHORTENED CONSTANT REFERENCE POINTER STRING UNORDERED MAPS */

  typedef const STRUNORMAP_BOL_P& CR_STRUNORMAP_BOL_P;
  typedef const STRUNORMAP_STR_P& CR_STRUNORMAP_STR_P;
  typedef const STRUNORMAP_CH_P& CR_STRUNORMAP_CH_P;
  typedef const STRUNORMAP_WCH_P& CR_STRUNORMAP_WCH_P;
  typedef const STRUNORMAP_INT_P& CR_STRUNORMAP_INT_P;
  typedef const STRUNORMAP_SI_P& CR_STRUNORMAP_SI_P;
  typedef const STRUNORMAP_LI_P& CR_STRUNORMAP_LI_P;
  typedef const STRUNORMAP_LLI_P& CR_STRUNORMAP_LLI_P;
  typedef const STRUNORMAP_USI_P& CR_STRUNORMAP_USI_P;
  typedef const STRUNORMAP_UI_P& CR_STRUNORMAP_UI_P;
  typedef const STRUNORMAP_ULI_P& CR_STRUNORMAP_ULI_P;
  typedef const STRUNORMAP_ULLI_P& CR_STRUNORMAP_ULLI_P;
  typedef const STRUNORMAP_SZ_P& CR_STRUNORMAP_SZ_P;
  typedef const STRUNORMAP_TM_P& CR_STRUNORMAP_TM_P;
  typedef const STRUNORMAP_FLT_P& CR_STRUNORMAP_FLT_P;
  typedef const STRUNORMAP_DBL_P& CR_STRUNORMAP_DBL_P;
  typedef const STRUNORMAP_LD_P& CR_STRUNORMAP_LD_P;
}

#endif // __MINI_TOOLS__TYPES_HPP__