#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_HPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_HPP__

namespace mini_tools {
namespace utils {

  /**
   * Note that 'titles' are inputs without keywords.
   * They can also be considered initial inputs
   * that control the keywords that follow.
   */
  class CLIParser final {
  public:
    CLIParser() = delete;

    static void assignLast(
      CR_INT argc,
      char *argv[],
      STRUNORMAP_BOL &titles,
      STRUNORMAP_DBL &numbers,
      STRUNORMAP_STR &words
    );

    static void assignVector(
      CR_INT argc,
      char *argv[],
      STRUNORMAP_BOL &titles,
      STRUNORMAP<VEC_DBL> &numbers,
      STRUNORMAP<VEC_STR> &words
    );
  };
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_HPP__