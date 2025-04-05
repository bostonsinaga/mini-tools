#ifndef __MINI_TOOLS__UTILS__SCANNER_CPP__
#define __MINI_TOOLS__UTILS__SCANNER_CPP__

#include "types.h"
#include "utils/scanner.h"

namespace mini_tools {
namespace utils {

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

  bool Scanner::isFileExist(CR_PATH path) {
    if (fs::exists(path)) {
      if (fs::is_regular_file(path)) {
        return true;
      }
      return false;
    }
    return false;
  }

  bool Scanner::isDirectoryExist(CR_PATH path) {
    if (fs::exists(path)) {
      if (fs::is_directory(path)) {
        return true;
      }
      return false;
    }
    return false;
  }

  bool Scanner::createNotExistFile(CR_PATH path) {

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

  bool Scanner::createNotExistDirectory(CR_PATH path) {

    if (!Scanner::isDirectoryExist(path)) {

      if (std::distance(path.begin(), path.end()) > 1) {
        fs::create_directories(path);
      }
      else fs::create_directory(path);

      return true;
    }

    return false;
  }

  fs::path Scanner::findPath(
    fs::path &path,
    CR_BOL toFile,
    CR_BOL upward
  ) {
    fs::path combined;

    if (path.is_absolute()) {
      path = fs::relative(path);
    }

    if (upward) {
      fs::path current = fs::current_path();

      while (!current.root_directory()) {
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
      fs::recursive_directory_iterator(fs::current_path())
    ) {
      combined = entry.path() / path;

      if ((toFile && isFileExist(combined)) ||
        (!toFile && isDirectoryExist(combined))
      ) {
        return combined;
      }
    }

    return fs::current_path();
  }

  /** WARNING. Unable to read '\n' character */
  void Scanner::getFile(
    CR_STR name,
    std::string &textHook
  ) {
    std::string line;
    std::ifstream reader(name);

    while (std::getline(reader, line)) {
      textHook += line;
    }

    reader.close();
  }
}}

#endif // __MINI_TOOLS__UTILS__SCANNER_CPP__