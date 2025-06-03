#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_HPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_HPP__

#include "types.hpp"
#include "str-tools.hpp"

namespace mini_tools {
namespace utils {

  /**
   * CLI Parser uses 'std::unordered_map' to store values,
   * instead of 'std::vector' to avoid keyword duplication.
   * 
   * This class does not support the built-in hyphen prefix
   * for word/number with '-' or toggle with '--'.
   * You have to set it manually as part of the keyword.
   * 
   * Also this class does not provide a default value.
   * Except to keyword toggle that specified without arguments
   * will push the vector at keyword with 1 'true' by default.
   */
  template <inspector::NUMBER T>
  class CLIParser {
  private:
    /**
     * This is an unordered map which used as function selection that will
     * be executed by the program or can also be used as basic string
     * input if you don't want to use the main unordered maps below.
     * 
     * They store an integer for the order of registration index.
     * To get a set of keywords or the basic strings,
     * use the 'extractBasicStrings' method.
     */
    STRUNORMAP_UI entries;

    /**
     * Main Unordered Maps:
     * Use the getters to interact with these variables.
     */
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
     * - Create the object using constructor.
     * - Verify expected entries or keywords using the inquiries.
     * - [OPTIONAL] Use the balancers to equalize the vectors of some unordered maps.
     * - Retrieve parameters stored as a vector in main unordered maps using the getters.
     * 
     * You are not required to specify the entries exclusively.
     * Verify their existence using the inquiries.
     */
    CLIParser(
      CR_INT argc,
      char *argv[],
      CR_VEC_STR wordKeywords,
      CR_VEC_STR numberKeywords,
      CR_VEC_STR toggleKeywords
    );

    /** INQUIRIES */

    /**
     * Check for the existence of
     * 'expectedEntries' inside the 'entries'.
     */
    bool enter(CR_VEC_STR expectedEntries); // ordered
    bool query(CR_VEC_STR expectedEntries); // unordered

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

    // extract keywords from the 'entries'
    VEC_STR extractBasicStrings();

    /**
     * If 'onlyCopy' is set to false, the vector at keyword will be moved to
     * the container that receives the return and then the vector will be emptied.
     */

    VEC_STR getWords(
      CR_STR keyword,
      CR_BOL onlyCopy = true
    );

    VEC<T> getNumbers(
      CR_STR keyword,
      CR_BOL onlyCopy = true
    );

    VEC_BOL getToggles(
      CR_STR keyword,
      CR_BOL onlyCopy = true
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
     *   { {"foo-word", "A"}, {"foo-word", "A"} },
     *   { {"foo-number", 1}, {"foo-number", 1} },
     *   { {"foo-toggle", false}, {"foo-toggle", false} }
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