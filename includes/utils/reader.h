#ifndef __MINI_TOOLS__UTILS__SCANNER_H__
#define __MINI_TOOLS__UTILS__SCANNER_H__

namespace mini_tools {
namespace utils {

  class Reader {
  public:
    static VEC_CH separators_ch;
    static VEC_STR separators_str;

    static bool isSeparator(CR_CH ch);
    static bool isSeparator(CR_STR str);
    static bool isSeparator(CR_STR text, CR_INT idx);
    static bool isSeparator(CR_VEC_STR textVec, CR_INT idx);

    static void getFile(
      CR_STR name,
      std::string &textHook
    );
  };
}}

#endif // __MINI_TOOLS__UTILS__SCANNER_CPP__