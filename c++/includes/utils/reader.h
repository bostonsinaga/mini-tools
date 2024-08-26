#ifndef __MINI_TOOLS__UTILS__READER_H__
#define __MINI_TOOLS__UTILS__READER_H__

#include "../types.h"

namespace mini_tools {
namespace utils {

  class Reader {
  public:
    static bool isSeparator(CR_CHR ch);
    static bool isSeparator(CR_STR text, CR_INT i);

    static void getFile(
      CR_STR name,
      std::string &textHook
    );
  };
}}

#endif // __MINI_TOOLS__UTILS__READER_H__