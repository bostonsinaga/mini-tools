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
  private:
    VEC_STR raws;
    STRUNORMAP_BOL titles;

    STRUNORMAP_DBL latestNumber;
    STRUNORMAP_STR latestWord;

    STRUNORMAP<VEC_DBL> numberVectors;
    STRUNORMAP<VEC_STR> wordVectors;

    inline bool isLatestKeyword(CR_STR test);
    inline bool isVectorKeyword(CR_STR test);

  public:
    CLIParser() = delete;

    CLIParser(
      CR_INT argc,
      char *argv[],
      CR_VEC_STR numberKeywords,
      CR_VEC_STR wordKeywords
    );

    bool hasTitle(CR_STR keyword);
    VEC_STR extractTitles();

    void assignLatest();
    double getLatestNumber(CR_STR keyword);
    std::string getLatestWord(CR_STR keyword);

    void assignVectors();
    VEC_DBL getVectorNumber(CR_STR keyword);
    VEC_STR getVectorWord(CR_STR keyword);
  };
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_HPP__