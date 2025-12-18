#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_HPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_HPP__

#include "types.hpp"
#include "scanner.hpp"
#include "booleanizer.hpp"

namespace mini_tools {
namespace utils {

  /** Template Parameter Constraints */

  template <typename T>
  concept CLIType =
    std::is_same_v<T, std::string> ||
    std::is_same_v<T, LD> ||
    std::is_same_v<T, bool>;

  template <typename T, typename U, typename V>
  concept CLIUniqueType =
    CLIType<T> && CLIType<U> && CLIType<V> &&
    !std::is_same_v<T, U> &&
    !std::is_same_v<U, V> &&
    !std::is_same_v<V, T>;

  /** Default Template Arguments */

  struct CLIDefault_T {
    using type = std::string;
  };

  template <CLIType T>
  struct CLIDefault_U {
    using type = std::conditional_t<
      std::is_same_v<T, std::string>,
      LD, std::conditional_t<
        std::is_same_v<T, LD>,
        bool, std::string
      >
    >;
  };

  template <CLIType T, CLIType U>
  struct CLIDefault_V {
    using type = std::conditional_t<
      (std::is_same_v<T, std::string> && std::is_same_v<U, LD>) ||
      (std::is_same_v<T, LD> && std::is_same_v<U, std::string>),
      bool, std::conditional_t<
        (std::is_same_v<T, LD> && std::is_same_v<U, bool>) ||
        (std::is_same_v<T, bool> && std::is_same_v<U, LD>),
        std::string, int
      >
    >;
  };

  /**
   * CLI Parser uses 'std::unordered_map' to store values,
   * instead of 'std::vector' to avoid keyword duplication.
   * 
   * CLI input is captured during object construction (in setters if the object is plain),
   * but you can reset all member variables later using the cleaners and setters.
   * 
   * This class does not support the built-in hyphen prefix
   * for word/number with '-' or boolean with '--'.
   * You have to set it manually as part of the keyword.
   * 
   * How to use (sequentially):
   * - Create an object using any constructor or setter below.
   * - Verify expected entries or keywords using the inquiries.
   * - [OPTIONAL] Use the balancers to equalize the vectors of some unordered maps.
   * - Retrieve parameters stored as a vector in main unordered maps using the getters.
   */
  template <
    typename T = CLIDefault_T::type,
    typename U = CLIDefault_U<T>::type,
    typename V = CLIDefault_V<T, U>::type
  >
  requires CLIUniqueType<T, U, V>
  class CLIParser {
  private:
    /**
     * This is an unordered map which used as function selection that will
     * be executed by the program or can also be used as initial string
     * input if you don't want to use the main unordered maps below.
     * 
     * They store an integer for the order of registration index.
     * To get a set of initial strings, use the 'extractStringsFromEntries' method.
     * 
     * You don't need to specify the entries exclusively like the main
     * unordered maps since they are just initial string inputs.
     * Verify their existence using the inquiries.
     */
    STRUNORMAP_UI entries;

    /** Abbreviations of keyword-default */

    template <typename W>
    using KEYDEF = PAIR2<std::string, W>;

    template <typename W>
    using CR_KEYDEF = const KEYDEF<W>&;

    template <typename W>
    using VEC_KEYDEF = VEC<KEYDEF<W>>;

    template <typename W>
    using CR_VEC_KEYDEF = const VEC_KEYDEF<W>&;

    /** Abbreviations of vector-default */

    template <typename W>
    using PAIR_MAIN = PAIR2<VEC<W>, W>;

    template <typename W>
    using UNORMAP_MAIN = STRUNORMAP<PAIR_MAIN<W>>;

    /**
     * MAIN UNORDERED MAPS
     * Use the getters to interact with these variables.
     * They contain a pair consisting of a vector and a default value.
     */
    UNORMAP_MAIN<T> mainUnormap_T;
    UNORMAP_MAIN<U> mainUnormap_U;
    UNORMAP_MAIN<V> mainUnormap_V;

    /**
     * Indicator for 'raws' iteration in setters
     * to differentiate between input and keyword.
     */
    enum FoundEnum {
      FoundEntry,
      Found_T, FoundInput_T,
      Found_U, FoundInput_U,
      Found_V, FoundInput_V
    };

    // multilingual term for type
    inline static std::string
      stringified_T = "WORD",
      stringified_U = "NUMBER",
      stringified_V = "BOOLEAN";

    // select a main unordered map
    template <typename W>
    UNORMAP_MAIN<W> &selectMainUnormap();

    /**
     * Set the default value for the vector of main
     * unordered maps if only the keyword is specified in 'raws'.
     */

    enum FoundCountEnum {
      FoundCountOne, FoundCountTwo, FoundCountThree
    };

    template <FoundCountEnum N>
    void pushDefault(
      CR_STR keyword,
      const FoundEnum &found
    );

    /**
     * Select the addition of 'raws' to the vector
     * that corresponds to the main unordered map type.
     */
    template <typename W>
    void pushRaw(
      CR_STR keyword,
      CR_STR raw
    );

    // find the largest size of an unordered map vector
    template <typename W>
    size_t getMax(CR_VEC_KEYDEF<W> keywordPaddingVector);

    /**
     * Equalize the vectors of an unordered map
     * with padding values ​​to balance them.
     */
    template <typename W>
    void balance(
      CR_VEC_KEYDEF<W> keywordPaddingVector_W,
      CR_SZ max
    );

    /**
     * Get strings free from spaces on the left and right.
     * The only spaces will not be included.
     */
    VEC_STR getTrimmedRaws(CR_VEC_STR raws);

  public:
    /** Interpret string as boolean */

    Booleanizer booleanizer;
    std::string booleanizerISOCode = "en";

    void setBooleanizerISOCode(CR_STR newISOCode) {
      booleanizerISOCode = newISOCode;
    }

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
     * The 'Raws' will be cleaned with 'getTrimmedRaws' before use.
     * 
     * Call example:
     *   CLIParser<std::string, int, bool> cli(
     *     StrTools::argvToStringVector(argc, argv),
     *     { std::make_pair("foo-word-1", "A"), std::make_pair("foo-word-2", "B") },
     *     { std::make_pair("foo-number-1", 0), std::make_pair("foo-number-2", 1) },
     *     { std::make_pair("foo-boolean-1", false), std::make_pair("foo-boolean-2", true) }
     *   );
     */

    CLIParser(CR_VEC_STR raws);

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF<T> keywordDefault_T
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF<T> keywordDefault_T,
      CR_VEC_KEYDEF<U> keywordDefault_U
    );

    CLIParser(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF<T> keywordDefault_T,
      CR_VEC_KEYDEF<U> keywordDefault_U,
      CR_VEC_KEYDEF<V> keywordDefault_V
    );

    /**
     * SETTERS
     * 
     * These methods will initialize the main unordered map and
     * parse input as vector to each keyword from the 'raws'.
     * 
     * You can use the 'StrTools::argvToStringVector' method to obtain the 'raws'
     * argument if the sources are parameters of the main function.
     * 
     * Also, you can perform a reset by sequentially
     * using a combination of cleaners and setters.
     */

    void set(CR_VEC_STR raws);

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF<T> keywordDefaultVector_T
    );

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF<T> keywordDefaultVector_T,
      CR_VEC_KEYDEF<U> keywordDefaultVector_U
    );

    void set(
      CR_VEC_STR raws,
      CR_VEC_KEYDEF<T> keywordDefaultVector_T,
      CR_VEC_KEYDEF<U> keywordDefaultVector_U,
      CR_VEC_KEYDEF<V> keywordDefaultVector_V
    );

    /**
     * CLEANERS
     * If 'fullyClean' is true, all vectors and unordered
     * maps will be cleared, and their memory will be deallocated.
     * However, this does not apply to dynamically allocated memory.
     * You need to deallocate it manually.
     */

    template <typename W>
    void clean(CR_BOL fullyClean);

    void cleanAll(CR_BOL fullyClean = false);
    void cleanEntries(CR_BOL fullyClean = false);

    /**
     * ENTRY INQUIRIES
     * 
     * Check 'expectedEntries' existence inside the entries.
     * 
     * Set 'fromAllEntries' to false if you only want to check
     * whether 'expectedEntries' are included in entries.
     *
     * Set 'fromAllEntries' to true if 'expectedEntries' should
     * represent all entries, with any others considered as random entries.
     */

    // ordered
    bool enter(
      CR_VEC_STR expectedEntries,
      CR_BOL fromAllEntries = true
    );

    // unordered
    bool query(
      CR_VEC_STR expectedEntries,
      CR_BOL fromAllEntries = true
    );

    /**
     * KEYWORD INQUIRIES
     * Check 'keyword' existence in main unordered map.
     */
    template <typename W>
    bool has(CR_STR keyword);

    /**
     * VECTOR INQUIRIES
     * Check 'keyword' existence in main unordered map
     * or emptiness of vector at 'keyword'.
     */
    template <typename W>
    bool contains(CR_STR keyword);

    /** GETTERS */

    template <typename W>
    W getAt(CR_STR keyword, CR_SZ index);

    // extract strings from the entries
    VEC_STR extractStringsFromEntries();

    // extract strings from a main unordered map
    template <typename W>
    VEC_STR extractStringsFromMainUnormap();

    /**
     * If 'onlyCopy' is set to false, the vector at keyword will be moved to
     * the container that receives the return and then the vector will be emptied.
     */
    template <typename W>
    VEC<W> getVectorAt(
      CR_STR keyword,
      CR_BOL onlyCopy = true
    );

    /**
     * SIZE GETTERS
     * Will return 0 for an empty vector or unregistered unordered map.
     */

    template <typename W>
    size_t getSizeAt(CR_STR keyword);

    template <typename W>
    size_t getSize() { return selectMainUnormap<W>().size(); }

    size_t getEntriesSize() { return entries.size(); }

    /**
     * BALANCERS
     * 
     * Equalize the vectors of main unordered
     * maps with padding values ​​to balance them.
     * 
     * Call example:
     *   cli.balance(
     *     { std::make_pair("foo-word-1", "A"), std::make_pair("foo-word-2", "B") },
     *     { std::make_pair("foo-number-1", 0), std::make_pair("foo-number-2", 1) },
     *     { std::make_pair("foo-boolean-1", false), std::make_pair("foo-boolean-2", true) }
     *   );
     */

    void balance(CR_VEC_KEYDEF<T> keywordPaddingVector_T);

    void balance(
      CR_VEC_KEYDEF<T> keywordPaddingVector_T,
      CR_VEC_KEYDEF<U> keywordPaddingVector_U
    );

    void balance(
      CR_VEC_KEYDEF<T> keywordPaddingVector_T,
      CR_VEC_KEYDEF<U> keywordPaddingVector_U,
      CR_VEC_KEYDEF<V> keywordPaddingVector_V
    );

    /** Multilingual term for type */

    template <typename W>
    static std::string getStringifiedType();

    template <typename W>
    static void setStringifiedType(CR_STR term);
  };
}}

#include "utils/cli-parser.tpp"
#endif // __MINI_TOOLS__UTILS__CLI_PARSER_HPP__