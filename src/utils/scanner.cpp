#ifndef __MINI_TOOLS__UTILS__SCANNER_CPP__
#define __MINI_TOOLS__UTILS__SCANNER_CPP__

#include "types.h"
#include "utils/scanner.h"

namespace mini_tools {
namespace utils {

  /** Simple Detectors */

  VEC_CH Scanner::separators_ch {' ', ',', '\n'};
  VEC_STR Scanner::separators_str {" ", ",", "\n"};

  bool Scanner::isSeparator(CR_CH ch) {
    for (CR_CH c : separators_ch) {
      if (ch == c) return true;
    }
    return false;
  }

  bool Scanner::isSeparator(CR_STR str) {
    for (CR_STR s : separators_str) {
      if (str == s) return true;
    }
    return false;
  }

  bool Scanner::isSeparator(CR_STR text, CR_INT idx) {
    if (idx >= 0 && idx < text.length()) {
      if (Scanner::isSeparator(text[idx]) ||
        idx == text.length() - 1
      ) {
        return true;
      }
      return false;
    }
    return false;
  }

  bool Scanner::isSeparator(CR_VEC_STR textVec, CR_INT idx) {
    if (idx >= 0 && idx < textVec.size()) {
      if (Scanner::isSeparator(textVec[idx]) ||
        idx == textVec.size() - 1
      ) {
        return true;
      }
      return false;
    }
    return false;
  }

  /** Text File or Directory Readers */

  bool Scanner::isFileExist(CR_FS_PATH path) {
    if (FS::exists(path)) {
      if (FS::is_regular_file(path)) {
        return true;
      }
      return false;
    }
    return false;
  }

  bool Scanner::isDirectoryExist(CR_FS_PATH path) {
    if (FS::exists(path)) {
      if (FS::is_directory(path)) {
        return true;
      }
      return false;
    }
    return false;
  }

  bool Scanner::createNotExistFile(CR_FS_PATH path) {

    if (!Scanner::isFileExist(path)) {
      std::ofstream file(path);

      if (file.is_open()) {
        file.close();
        return true;
      }

      return false;
    }

    return false;
  }

  bool Scanner::createNotExistDirectory(CR_FS_PATH path) {

    if (!Scanner::isDirectoryExist(path)) {

      if (std::distance(path.begin(), path.end()) > 1) {
        FS::create_directories(path);
      }
      else FS::create_directory(path);

      return true;
    }

    return false;
  }

  FS_PATH Scanner::findPath(
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

        if ((toFile && isFileExist(combined)) ||
          (!toFile && isDirectoryExist(combined))
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

      if ((toFile && isFileExist(combined)) ||
        (!toFile && isDirectoryExist(combined))
      ) {
        return combined;
      }
    }

    return FS::current_path();
  }

  /** WARNING. Unable to read '\n' character */
  void Scanner::getFile(
    CR_FS_PATH path,
    std::string &textHook
  ) {
    std::string line;
    std::ifstream reader(path);

    while (std::getline(reader, line)) {
      textHook += line;
    }

    reader.close();
  }
}}

#endif // __MINI_TOOLS__UTILS__SCANNER_CPP__