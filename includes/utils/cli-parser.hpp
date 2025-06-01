#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_HPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_HPP__

#include "types.hpp"
#include "str-tools.hpp"

namespace mini_tools {
namespace utils {

  template <inspector::NUMBER T>
  class CLIParser {
  private:
    /**
     * This is a collection of keywords used as a function selection
     * to be executed by the program or can also be used as basic string input
     * if you do not want to use the 3 unordered maps below.
     * 
     * They contain boolean values ​​as markers of their existence.
     * To get the collection of keywords, use the extractor method.
     */
    STRUNORMAP_BOL entries;

    // use getters and extractors to interact with these
    STRUNORMAP<VEC_STR> words;
    STRUNORMAP<VEC<T>> numbers;
    STRUNORMAP<VEC_BOL> toggles;

    /**
     * Expected string conversions are:
     * "TRUE", "FALSE", "YES", "NO", "Y", "N"
     * or a number (non-zero is true).
     * 
     * The value of 'str' will come from
     * the 'argv' input after the toggle keyword.
     */
    bool booleanize(std::string &str);

    // find the largest size of an unordered map vector
    template <typename U>
    size_t getMax(
      STRUNORMAP<VEC<U>> &unormap,
      CR_VEC_PAIR2<std::string, U> keywordPaddingVector
    );

    /**
     * Equalize the vectors of an unordered map
     * with padding values ​​to balance them.
     */
    template <typename U>
    void balance(
      STRUNORMAP<VEC<U>> &unormap,
      CR_VEC_PAIR2<std::string, U> keywordPaddingVector,
      CR_SZ max
    );

  public:
    CLIParser() = delete;

    /**
     * The 'argc' is expected to have a value that corresponds
     * to the actual number of 'argv' or both are parameters of the main function.
     * 
     * How to use (sequentially):
     * - Create object.
     * - Check expected entries with 'enter'.
     * - Obtain the parameters (unordered maps) value with getters.
     * 
     * You do not need to exclusively specify the 'entries'.
     * Ask their existence with 'enter'.
     * 
     * This class does not provide a default value.
     * Except to keyword toggle that specified
     * without input, will push the vector of unordered
     * map at keyword with 1 'true' by default.
     */
    CLIParser(
      CR_INT argc,
      char *argv[],
      CR_VEC_STR wordKeywords,
      CR_VEC_STR numberKeywords,
      CR_VEC_STR toggleKeywords
    );

    /**
     * Check 'expectedEntries' existence inside the 'entries'.
     * The order of 'expectedEntries' is ignored.
     */
    bool enter(CR_VEC_STR expectedEntries);

    /** CHECKERS */

    // check for the existence of an unordered map
    bool wordsHas(CR_STR keyword);
    bool numbersHas(CR_STR keyword);
    bool togglesHas(CR_STR keyword);

    // check for the existence of a vector or unordered map itself
    bool wordContains(CR_STR keyword);
    bool numberContains(CR_STR keyword);
    bool toggleContains(CR_STR keyword);

    /** GETTERS */

    std::string getWordAt(CR_STR keyword, CR_SZ index);
    T getNumberAt(CR_STR keyword, CR_SZ index);
    bool getToggleAt(CR_STR keyword, CR_SZ index);

    // extract keywords of 'entries'
    VEC_STR extractBasicStrings();

    VEC_STR getWords(
      CR_STR keyword,
      CR_BOL needClean = false
    );

    VEC<T> getNumbers(
      CR_STR keyword,
      CR_BOL needClean = false
    );

    VEC_BOL getToggles(
      CR_STR keyword,
      CR_BOL needClean = false
    );

    /**
     * SIZE GETTERS
     * Will return 0 for an empty vector or unregistered unordered map.
     */
    size_t getWordSize(CR_STR keyword);
    size_t getNumberSize(CR_STR keyword);
    size_t getToggleSize(CR_STR keyword);

    /**
     * BALANCERS
     * Equalize the vectors of an unordered map
     * with padding values ​​to balance them.
     */

    void balanceWords(CR_VEC_PAIR<std::string> keywordPaddingVector);
    void balanceNumbers(CR_VEC_PAIR<T> keywordPaddingVector);
    void balanceToggles(CR_VEC_PAIR<bool> keywordPaddingVector);

    /**
     * Equalize the vectors of multiple unordered maps
     * with padding values ​​to balance them.
     * 
     * Call example:
     * 
     * cli.balanceAll(
     *   { {"word_A", "A"}, {"word_A", "A"} },
     *   { {"number_A", 1}, {"number_A", 1} },
     *   { {"toggle_A", false}, {"toggle_A", false} }
     * );
     */
    void balanceAll(
      CR_VEC_PAIR2<std::string, std::string> keywordPaddingWords,
      CR_VEC_PAIR2<std::string, T> keywordPaddingNumbers,
      CR_VEC_PAIR2<std::string, bool> keywordPaddingToggles
    );
  };
}}

#include "utils/cli-parser.tpp"
#endif // __MINI_TOOLS__UTILS__CLI_PARSER_HPP__