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
   * CLI input is captured during object construction (in setters if the object is plain),
   * but you can reset all member variables later using the cleaners and setters.
   * 
   * This class does not support the built-in hyphen prefix
   * for word/number with '-' or toggle with '--'.
   * You have to set it manually as part of the keyword.
   * 
   * How to use (sequentially):
   * - Create an object using any constructor or setter below.
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

    /** Abbreviations of keyword-default */

    template <typename U>
    using KEYDEF = PAIR2<std::string, U>;

    template <typename U>
    using CR_KEYDEF = const KEYDEF<U>&;

    template <typename U>
    using VEC_KEYDEF = VEC<KEYDEF<U>>;

    template <typename U>
    using CR_VEC_KEYDEF = const VEC_KEYDEF<U>&;

    typedef KEYDEF<std::string> KEYDEF_WORD;
    typedef KEYDEF<T> KEYDEF_NUMBER;
    typedef KEYDEF<bool> KEYDEF_TOGGLE;

    typedef const KEYDEF_WORD& CR_KEYDEF_WORD;
    typedef const KEYDEF_NUMBER& CR_KEYDEF_NUMBER;
    typedef const KEYDEF_TOGGLE& CR_KEYDEF_TOGGLE;

    typedef VEC<KEYDEF_WORD> VEC_KEYDEF_WORD;
    typedef VEC<KEYDEF_NUMBER> VEC_KEYDEF_NUMBER;
    typedef VEC<KEYDEF_TOGGLE> VEC_KEYDEF_TOGGLE;

    typedef const VEC_KEYDEF_WORD& CR_VEC_KEYDEF_WORD;
    typedef const VEC_KEYDEF_NUMBER& CR_VEC_KEYDEF_NUMBER;
    typedef const VEC_KEYDEF_TOGGLE& CR_VEC_KEYDEF_TOGGLE;

    /** Abbreviations of vector-default */

    template <typename U>
    using PAIR_MAIN = PAIR2<VEC<U>, U>;

    template <typename U>
    using UNORMAP_MAIN = STRUNORMAP<PAIR_MAIN<U>>;

    typedef PAIR_MAIN<std::string> PAIR_WORD;
    typedef PAIR_MAIN<T> PAIR_NUMBER;
    typedef PAIR_MAIN<bool> PAIR_TOGGLE;

    typedef STRUNORMAP<PAIR_WORD> UNORMAP_WORD;
    typedef STRUNORMAP<PAIR_NUMBER> UNORMAP_NUMBER;
    typedef STRUNORMAP<PAIR_TOGGLE> UNORMAP_TOGGLE;

    /**
     * MAIN UNORDERED MAPS
     * Use the getters to interact with these variables.
     * They contain a pair consisting of a vector and a default value.
     */
    UNORMAP_WORD words;
    UNORMAP_NUMBER numbers;
    UNORMAP_TOGGLE toggles;

    /**
     * Indicator for 'raws' iteration in setters
     * to differentiate between input and keyword.
     */

    enum FoundEnum {
      FoundEntry, FoundWord, FoundWordInput,
      FoundNumber, FoundNumberInput,
      FoundToggle, FoundToggleInput
    };

    typedef const FoundEnum& CR_FoundEnum;

    template <typename U>
    constexpr FoundEnum limitFoundEnum() const;

    template <typename U>
    constexpr FoundEnum limitFoundEnumInput() const;

    /**
     * Set the default value for the vector of main
     * unordered maps if only the keyword is specified in 'raws'.
     */

    template <typename U>
    void pushDefault(
      UNORMAP_MAIN<U> unormap,
      CR_STR keyword,
      CR_FoundEnum found
    );

    template <typename U, typename V>
    void pushDefault(
      UNORMAP_MAIN<U> unormap_U,
      UNORMAP_MAIN<V> unormap_V,
      CR_STR keyword,
      CR_FoundEnum found
    );

    void pushDefault(
      CR_STR keyword,
      CR_FoundEnum found
    );

    /**
     * Select the addition of 'raws' to the vector
     * that corresponds to the main unordered map type.
     */
    template <typename U>
    constexpr void pushRaw(
      UNORMAP_MAIN<U> &unormap,
      CR_STR keyword,
      CR_STR raw
    );

    /**
     * Convert string to boolean.
     * 
     * Expected string conversions are:
     * "TRUE", "FALSE", "YES", "NO", "Y", "N"
     * or a number (non-zero is true).
     * 
     * The value of 'str' will come from
     * the 'argv' input after the toggle keyword.
     */
    bool booleanize(std::string str);

    // check 'keyword' existence in unordered map
    template <typename U>
    bool has(
      UNORMAP_MAIN<U> &unormap,
      CR_STR keyword
    );

    /**
     * SETTERS
     * These methods will initialize the main unordered map and
     * parse input as vector to each keyword from the 'raws'.
     */

    template <typename U>
    void set(
      CR_VEC_STR raws,
      UNORMAP_MAIN<U> &unormap,
      CR_VEC_KEYDEF<U> keywordDefaultVector
    );

    template <typename U, typename V>
    void set(
      CR_VEC_STR raws,
      UNORMAP_MAIN<U> &unormap_U,
      UNORMAP_MAIN<V> &unormap_V,
      CR_VEC_KEYDEF<U> keywordDefaultVector_U,
      CR_VEC_KEYDEF<V> keywordDefaultVector_V
    );

    /**
     * Warning! Dynamically allocated memory in vectors is not
     * properly released. So you need to deallocate it manually.
     */
    template <typename U>
    void clean(
      UNORMAP_MAIN<U> &unormap,
      CR_BOL fullyClean
    );

    // find the largest size of an unordered map vector
    template <typename U>
    size_t getMax(
      UNORMAP_MAIN<U> &unormap,
      CR_VEC_KEYDEF<U> keywordPaddingVector
    );

    /**
     * BALANCERS
     * Equalize the vectors of an unordered map
     * with padding values ​​to balance them.
     */

    template <typename U>
    void balance(
      UNORMAP_MAIN<U> &unormap,
      CR_VEC_KEYDEF<U> keywordPaddingVector,
      CR_SZ max
    );

    template <typename U, typename V>
    void balance(
      UNORMAP_MAIN<U> &unormap_U,
      UNORMAP_MAIN<V> &unormap_V,
      CR_VEC_KEYDEF<U> keywordPaddingVector_U,
      CR_VEC_KEYDEF<V> keywordPaddingVector_V
    );

  public:
    /**
     * Creating a plain object but having to call a setter
     * afterwards so that the CLI input can be processed.
     */
    CLIParser() {}

    /**
     * CONSTRUCTORS
     * 
     * The default values will be added to the vectors
     * within the main unordered maps in setters if the
     * detected keywords are specified without arguments.
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
      CR_VEC_KEYDEF_WORD keywordDefaultWords
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_WORD keywordDefaultWords,
      CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers,
      CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_WORD keywordDefaultWords,
      CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_WORD keywordDefaultWords,
      CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers,
      CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
    );

    /**
     * SETTERS
     * 
     * You can use the 'argvToStringVector' method to obtain the 'raws'
     * argument if the sources are parameters of the main function.
     * 
     * Also, you can perform a reset by sequentially
     * using a combination of cleaners and setters.
     */

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_WORD keywordDefaultWords
    );

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers
    );

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
    );

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_WORD keywordDefaultWords,
      CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers
    );

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers,
      CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
    );

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_WORD keywordDefaultWords,
      CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
    );

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF_WORD keywordDefaultWords,
      CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers,
      CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
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

    // check 'expectedEntries' existence inside the entries
    bool enter(CR_VEC_STR expectedEntries); // ordered
    bool query(CR_VEC_STR expectedEntries); // unordered

    // check 'keyword' existence in unordered map
    bool wordsHas(CR_STR keyword);
    bool numbersHas(CR_STR keyword);
    bool togglesHas(CR_STR keyword);

    /**
     * Check 'keyword' existence in unordered map
     * or emptiness of vector at 'keyword'.
     */
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
     * BALANCERS
     * 
     * Equalize the vectors of an unordered map
     * with padding values ​​to balance them.
     * 
     * Call example:
     *   cli.balance(
     *     { std::make_pair("foo-word-1", "A"), std::make_pair("foo-word-2", "B") },
     *     { std::make_pair("foo-number-1", 0), std::make_pair("foo-number-2", 1) },
     *     { std::make_pair("foo-toggle-1", false), std::make_pair("foo-toggle-2", true) }
     *   );
     */

    void balance(
      CR_VEC_KEYDEF_WORD keywordPaddingWords
    );

    void balance(
      CR_VEC_KEYDEF_NUMBER keywordPaddingNumbers
    );

    void balance(
      CR_VEC_KEYDEF_TOGGLE keywordPaddingToggles
    );

    void balance(
      CR_VEC_KEYDEF_WORD keywordPaddingWords,
      CR_VEC_KEYDEF_NUMBER keywordPaddingNumbers
    );

    void balance(
      CR_VEC_KEYDEF_NUMBER keywordPaddingNumbers,
      CR_VEC_KEYDEF_TOGGLE keywordPaddingToggles
    );

    void balance(
      CR_VEC_KEYDEF_WORD keywordPaddingWords,
      CR_VEC_KEYDEF_TOGGLE keywordPaddingToggles
    );

    void balance(
      CR_VEC_KEYDEF_WORD keywordPaddingWords,
      CR_VEC_KEYDEF_NUMBER keywordPaddingNumbers,
      CR_VEC_KEYDEF_TOGGLE keywordPaddingToggles
    );
  };
}}

#include "utils/cli-parser.tpp"
#endif // __MINI_TOOLS__UTILS__CLI_PARSER_HPP__