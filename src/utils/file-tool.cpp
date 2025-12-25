#ifndef __MINI_TOOLS__UTILS__FILE_TOOL_CPP__
#define __MINI_TOOLS__UTILS__FILE_TOOL_CPP__

#include "utils/file-tool.hpp"

namespace mini_tools {
namespace utils {

  bool FileTool::createNotExistFile(CR_FS_PATH path) {

    if (!FS::is_regular_file(path)) {
      std::ofstream file(path);

      if (file.is_open()) {
        file.close();
        return true;
      }
    }

    return false;
  }

  bool FileTool::createNotExistDirectory(CR_FS_PATH path) {
    if (!FS::is_directory(path)) {

      if (std::distance(path.begin(), path.end()) > 1) {
        FS::create_directories(path);
      }
      else FS::create_directory(path);

      return true;
    }

    return false;
  }

  FS_PATH FileTool::findPath(
    FS_PATH &path,
    CR_BOL toFile,
    CR_BOL upward
  ) {
    FS_PATH combined;

    if (path.is_absolute()) {
      path = FS::relative(path);
    }

    if (upward) {
      FS_PATH current = FS::current_path();

      while (current != current.root_path()) {
        combined = current / path;

        if ((toFile && FS::is_regular_file(combined)) ||
          (!toFile && FS::is_directory(combined))
        ) {
          return combined;
        }

        current = current.parent_path();
      }
    }
    else for (const std::filesystem::directory_entry& entry:
      FS::recursive_directory_iterator(FS::current_path())
    ) {
      combined = entry.path() / path;

      if ((toFile && FS::is_regular_file(combined)) ||
        (!toFile && FS::is_directory(combined))
      ) {
        return combined;
      }
    }

    return FS::current_path();
  }
}}

#endif // __MINI_TOOLS__UTILS__FILE_TOOL_CPP__