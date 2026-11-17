#ifndef __MINI_TOOLS__UTILS__PRINTER_HPP__
#define __MINI_TOOLS__UTILS__PRINTER_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {

  class Printer final {
  private:
    static std::string getNewlines(
      CR_STR text,
      CR_SZ endNewlinesCount
    );

    // output example: "Error: 404"
    template <STRNUMERIC T>
    static std::string getHeader(CR_SZ endNewlinesCount);

  /**
   * The 'endNewlinesCount' parameter controls
   * the newlines of generated 'text' at the end.
   */
  public:
    Printer() = delete;

    /** VARIABLES */

    inline static std::string title = "Step";

    template <STRNUMERIC T>
    inline static T tag = T();

    /** METHODS */

    template <STRNUMERIC T>
    static std::string stringify(
      CR_VEC<T> vec,
      CR_SZ endNewlinesCount = 0,
      CR_STR separator = "\n"
    );

    /** Warning! Floating numbers will be rounded down */
    template <NUMBER T>
    static std::string barStringify(
      CR_VEC<T> vec,
      CR_SZ endNewlinesCount = 0,
      CR_STR barStyle = "="
    );

    template <STRNUMERIC T>
    static void log(
      CR_VEC<T> vec,
      CR_SZ endNewlinesCount = 0,
      CR_STR separator = "\n"
    );

    template <NUMBER T>
    static void barLog(
      CR_VEC<T> vec,
      CR_SZ endNewlinesCount = 0,
      CR_STR barStyle = "="
    );

    /**
     * Set the 'extended' parameter to determine
     * whether to overwrite or continue the file.
     * 
     * If the path or filename is valid, permission is granted,
     * and the disk is still available, the file will be created
     * and these methods will return true.
     */

    static bool writeFileString(
      CR_STR text,
      CR_FS_PATH path,
      CR_BOL extended,
      CR_SZ endNewlinesCount = 0
    );

    template <STRNUMERIC T>
    static bool writeFileString(
      CR_VEC<T> vec,
      CR_FS_PATH path,
      CR_BOL extended,
      CR_SZ endNewlinesCount = 0,
      CR_STR separator = "\n"
    );

    template <typename T>
    static bool writeFileBinary(
      T data,
      CR_FS_PATH path,
      CR_BOL extended
    );

    template <STRNUMERIC T>
    static bool logf(
      CR_VEC<T> vec,
      CR_FS_PATH path,
      CR_BOL extended,
      CR_SZ endNewlinesCount = 0,
      CR_STR separator = "\n"
    );

    template <NUMBER T>
    static bool barLogf(
      CR_VEC<T> vec,
      CR_FS_PATH path,
      CR_BOL extended,
      CR_SZ endNewlinesCount = 0,
      CR_STR barStyle = "="
    );
  };
}}

#include "utils/printer.tpp"
#endif // __MINI_TOOLS__UTILS__PRINTER_HPP__