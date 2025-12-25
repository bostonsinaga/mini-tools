#ifndef __MINI_TOOLS__UTILS__FILE_TOOL_HPP__
#define __MINI_TOOLS__UTILS__FILE_TOOL_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {

  class FileTool final {
  public:
    FileTool() = delete;
    static bool createNotExistFile(CR_FS_PATH path);
    static bool createNotExistDirectory(CR_FS_PATH path);

    static FS_PATH findPath(
      FS_PATH &path,
      CR_BOL toFile,
      CR_BOL upward
    );

    static FS_PATH findFile(
      FS_PATH path,
      CR_BOL upward
    ) { return findPath(path, true, upward); }

    static FS_PATH findDirectory(
      FS_PATH path,
      CR_BOL upward
    ) { return findPath(path, false, upward); }
  };
}}

#endif // __MINI_TOOLS__UTILS__FILE_TOOL_HPP__