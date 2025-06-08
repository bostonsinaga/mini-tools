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
   * Input is captured during object construction, but you can
   * reset all member variables later using cleaners and setters.
   * 
   * This class does not support the built-in hyphen prefix
   * for word/number with '-' or toggle with '--'.
   * You have to set it manually as part of the keyword.
   * 
   * How to use (sequentially):
   * - Create an object using any of the constructors below.
   * - Verify expected entries or keywords using the inquiries.
   * - [OPTIONAL] Use the balancers to equalize the vectors of some unordered maps.
   * - Retrieve parameters stored as a vector in main unordered maps using the getters.
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
     * 
     * You don't need to specify the entries exclusively like the main
     * unordered maps since they are just basic string inputs.
     * Verify their existence using the inquiries.
     */
    STRUNORMAP_UI entries;

    /** Abbreviations of the main types */

    template <typename U>
    using PAIR_MAIN = PAIR2<VEC<U>, U>;

    template <typename U>
    using MAIN_STRUNORMAP = STRUNORMAP<PAIR_MAIN<U>>;

    /**
     * MAIN UNORDERED MAPS
     * Use the getters to interact with these variables.
     * They contain a pair consisting of a vector and a default value.
     */

    typedef PAIR_MAIN<std::string> PAIR_WORD;
    typedef PAIR_MAIN<T> PAIR_NUMBER;
    typedef PAIR_MAIN<bool> PAIR_TOGGLE;

    STRUNORMAP<PAIR_WORD> words;
    STRUNORMAP<PAIR_NUMBER> numbers;
    STRUNORMAP<PAIR_TOGGLE> toggles;

    /** Indicators for the basic setter method */

    enum FoundEnum {
      FoundEntry, FoundWord, FoundNumber, FoundToggle
    };

    typedef const FoundEnum& CR_FoundEnum;

    /**
     * Set the default value for the vector of main
     * unordered maps if only the keyword is specified in 'raws'.
     */
    void pushDefault(
      CR_STR keyword,
      CR_FoundEnum found
    );

    /**
     * KEYWORD IGNORED VECTORS GENERATOR
     * Convert vectors of keywords into vectors of keyword-default pairs,
     * where the default values are either empty, zero, or false.
     */

    typedef std::tuple<
      VEC_PAIR<std::string>,
      VEC_PAIR2<std::string, T>,
      VEC_PAIR2<std::string, bool>
    > KeywordIgnoredVectorsTuple;

    KeywordIgnoredVectorsTuple convertKeywordIgnoredVectorsTuple(
      CR_VEC_STR wordKeywords,
      CR_VEC_STR numberKeywords,
      CR_VEC_STR toggleKeywords
    );

    /**
     * KEYWORD PREDEFINED VECTORS GENERATOR
     * Convert vectors of keywords into vectors of keyword-default pairs,
     * where the default values are predefined in the setters.
     */
    template <typename U>
    VEC_PAIR2<std::string, U> convertKeywordPredefinedVector(
      MAIN_STRUNORMAP<U> &unormap,
      CR_VEC_STR keywords
    );

    /**
     * Expected string conversions are:
     * "TRUE", "FALSE", "YES", "NO", "Y", "N"
     * or a number (non-zero is true).
     * 
     * The value of 'str' will come from
     * the 'argv' input after the toggle keyword.
     */
    bool booleanize(std::string str);

    /**
     * Warning! Dynamically allocated memory in vectors is not
     * properly released. So you need to deallocate it manually.
     */
    template <typename U>
    void clean(
      MAIN_STRUNORMAP<U> &unormap,
      CR_BOL fullyClean
    );

    // find the largest size of an unordered map vector
    template <typename U>
    size_t getMax(
      MAIN_STRUNORMAP<U> &unormap,
      CR_VEC_PAIR2<std::string, U> keywordPaddingVector
    );

    /**
     * BASIC BALANCERS
     * Equalize the vectors of an unordered map
     * with padding values ​​to balance them.
     */

    // explicit
    template <typename U>
    void balance(
      MAIN_STRUNORMAP<U> &unormap,
      CR_VEC_PAIR2<std::string, U> keywordPaddingVector,
      CR_SZ max
    );

    // ignored
    template <typename U>
    void balance(
      MAIN_STRUNORMAP<U> &unormap,
      CR_VEC_STR keywords
    );

  public:
    CLIParser() {}

    /**
     * EXPLICIT CONSTRUCTORS
     * 
     * The default values will be added to the vectors
     * within the main unordered maps in the setters
     * if the detected keywords are specified without arguments.
     * 
     * Call example:
     *   CLIParser<int> cli(
     *     CLIParser<int>::argvToStringVector(argc, argv),
     *     { std::make_pair("foo-word-1", "A"), std::make_pair("foo-word-2", "B") },
     *     { std::make_pair("foo-number-1", 0), std::make_pair("foo-number-2", 1) },
     *     { std::make_pair("foo-toggle-1", false), std::make_pair("foo-toggle-2", true) }
     *   );
     */

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_PAIR<std::string> keywordDefaultWords,
      CR_VEC_PAIR2<std::string, T> keywordDefaultNumbers,
      CR_VEC_PAIR2<std::string, bool> keywordDefaultToggles
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_PAIR<std::string> keywordDefaultWords
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_PAIR2<std::string, T> keywordDefaultNumbers
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_PAIR2<std::string, bool> keywordDefaultToggles
    );

    /**
     * IGNORED CONSTRUCTORS
     * 
     * They basically use the setters.
     * The default values will be empty, zero, or false.
     * 
     * Call example:
     *   CLIParser<int> cli(
     *     CLIParser<int>::argvToStringVector(argc, argv),
     *     { "foo-word-1", "foo-word-2" },
     *     { "foo-number-1", "foo-number-2" },
     *     { "foo-toggle-1", "foo-toggle-2" }
     *   );
     */

    /**
     * The keyword-only constructor has no variations,
     * as all of its parameters are identical string vectors,
     * making them indistinguishable for overloading.
     * It can only rely on the order of parameters.
     */
    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_STR wordKeywords,
      CR_VEC_STR numberKeywords,
      CR_VEC_STR toggleKeywords
    );

    static CLIParser createWords(
      CR_VEC_STR raws,
      CR_VEC_STR keywords
    );

    static CLIParser createNumbers(
      CR_VEC_STR raws,
      CR_VEC_STR keywords
    );

    static CLIParser createToggles(
      CR_VEC_STR raws,
      CR_VEC_STR keywords
    );

    /**
     * SETTERS
     * 
     * These methods will initialize the main unordered maps and
     * parse inputs as vector to each keywords from the 'raws'.
     * 
     * You can use the 'argvToStringVector' method to obtain the 'raws'
     * argument if the sources are parameters of the main function.
     * 
     * Also, you can perform a reset by sequentially
     * using a combination of cleaners and setters.
     */

    /** EXPLICIT SETTERS */

    void setAll(
      CR_VEC_STR raws,
      CR_VEC_PAIR<std::string> newKeywordDefaultWords,
      CR_VEC_PAIR2<std::string, T> newKeywordDefaultNumbers,
      CR_VEC_PAIR2<std::string, bool> newKeywordDefaultToggles
    );

    void setWords(
      CR_VEC_STR raws,
      CR_VEC_PAIR<std::string> keywordDefaultVector
    );

    void setNumbers(
      CR_VEC_STR raws,
      CR_VEC_PAIR2<std::string, T> keywordDefaultVector
    );

    void setToggles(
      CR_VEC_STR raws,
      CR_VEC_PAIR2<std::string, bool> keywordDefaultVector
    );

    /** IGNORED SETTERS */

    void setAll(
      CR_VEC_STR raws,
      CR_VEC_STR wordKeywords,
      CR_VEC_STR numberKeywords,
      CR_VEC_STR toggleKeywords
    );

    void setWords(
      CR_VEC_STR raws,
      CR_VEC_STR keywords
    );

    void setNumbers(
      CR_VEC_STR raws,
      CR_VEC_STR keywords
    );

    void setToggles(
      CR_VEC_STR raws,
      CR_VEC_STR keywords
    );

    /**
     * CLEANERS
     * If 'fullyClean' is true, all vectors and unordered
     * maps will be cleared, and their memory will be deallocated.
     * However, this does not apply to dynamically allocated memory.
     * You need to deallocate it manually.
     */
    void cleanAll(CR_BOL fullyClean = false);
    void cleanEntries(CR_BOL fullyClean = false);
    void cleanWords(CR_BOL fullyClean = false);
    void cleanNumbers(CR_BOL fullyClean = false);
    void cleanToggles(CR_BOL fullyClean = false);

    /**
     * INQUIRIES
     * Verify expected entries or keywords.
     */

    /**
     * Check for the existence of
     * 'expectedEntries' inside the entries.
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

    // extract keywords from the entries
    VEC_STR extractBasicStrings();

    /**
     * If 'onlyCopy' is set to false, the vector at keyword will be moved to
     * the container that receives the return and then the vector will be emptied.
     */

    VEC_STR getVectorAtWords(
      CR_STR keyword,
      CR_BOL onlyCopy = true
    );

    VEC<T> getVectorAtNumbers(
      CR_STR keyword,
      CR_BOL onlyCopy = true
    );

    VEC_BOL getVectorAtToggles(
      CR_STR keyword,
      CR_BOL onlyCopy = true
    );

    /**
     * The 'argc' is expected to have a value that corresponds
     * to the actual number of 'argv' or both are parameters of the main function.
     */
    static VEC_STR argvToStringVector(
      CR_INT argc,
      char *argv[]
    );

    /**
     * SIZE GETTERS
     * Will return 0 for an empty vector or unregistered unordered map.
     */
    size_t getSizeAtWords(CR_STR keyword);
    size_t getSizeAtNumbers(CR_STR keyword);
    size_t getSizeAtToggles(CR_STR keyword);

    // unordered maps size getters
    size_t getEntriesSize() { return entries.size(); }
    size_t getWordsSize() { return words.size(); }
    size_t getNumbersSize() { return numbers.size(); }
    size_t getTogglesSize() { return toggles.size(); }

    /**
     * EXPLICIT BALANCERS
     * Equalize the vectors of multiple unordered maps
     * with padding values ​​to balance them.
     * 
     * Call example:
     *   cli.balance(
     *     { std::make_pair("foo-word-1", "A"), std::make_pair("foo-word-2", "B") },
     *     { std::make_pair("foo-number-1", 0), std::make_pair("foo-number-2", 1) },
     *     { std::make_pair("foo-toggle-1", false), std::make_pair("foo-toggle-2", true) }
     *   );
     */

    void balanceWords(CR_VEC_PAIR<std::string> keywordPaddingVector);
    void balanceNumbers(CR_VEC_PAIR<T> keywordPaddingVector);
    void balanceToggles(CR_VEC_PAIR<bool> keywordPaddingVector);

    void balanceAll(
      CR_VEC_PAIR<std::string> keywordPaddingWords,
      CR_VEC_PAIR2<std::string, T> keywordPaddingNumbers,
      CR_VEC_PAIR2<std::string, bool> keywordPaddingToggles
    );

    /**
     * IGNORED BALANCERS
     * Similar to the above, but it will use the default
     * values of the main unordered maps as the padding values.
     * 
     * Call example:
     *   cli.balance(
     *     { "foo-word-1", "foo-word-2" },
     *     { "foo-number-1", "foo-number-2" },
     *     { "foo-toggle-1", "foo-toggle-2" }
     *   );
     */

    void balanceWords(CR_VEC_STR keywords);
    void balanceNumbers(CR_VEC_STR keywords);
    void balanceToggles(CR_VEC_STR keywords);

    void balanceAll(
      CR_VEC_STR wordKeywords,
      CR_VEC_STR numberKeywords,
      CR_VEC_STR toggleKeywords
    );
  };
}}

#include "utils/cli-parser.tpp"
#endif // __MINI_TOOLS__UTILS__CLI_PARSER_HPP__