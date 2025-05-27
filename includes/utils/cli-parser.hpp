#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_HPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_HPP__

#include "types.hpp"
#include "utils/str-tools.hpp"
#include "utils/vec-tools.hpp"

namespace mini_tools {
namespace utils {

  /**
   * TITLES
   * 
   * Note that the map 'titles' are inputs without keywords
   * or you can consider the program name to be their keyword.
   * They can also be considered as initial inputs
   * that control the keywords that follow.
   * 
   * You can call the 'has()' method for selecting the type
   * or group of commands before the next process or if you are
   * using 'CLI_Parser' you can call 'entry()' for a more concise way.
   */
  class CLI_TitleParser {
  protected:
    VEC_STR raws;
    STRUNORMAP_BOL titles;
    std::string lastEntry;

  public:
    CLI_TitleParser() = delete;

    CLI_TitleParser(
      CR_INT argc,
      char *argv[],
      CR_VEC_STR keywords = {}
    );

    /**
     * Set map at 'raw' to true and
     * assign the keyword to 'lastEntry'.
     */
    void assign(CR_STR raw);

    // check keyword existence in map
    bool has(CR_STR keyword);

    // get size without giving access to map
    size_t size();

    /**
     * This is actually similar to the 'has' method.
     * Will return empty string if not found.
     */
    std::string at(CR_STR keyword);

    // get last added keyword
    std::string last();

    // convert map keywords to a string vector
    VEC_STR extract();
  };

  //_______|
  // WORDS |
  //_______|

  class CLI_WordParser : public virtual CLI_TitleParser {
  protected:
    STRUNORMAP<VEC_STR> words;
    static constexpr int typeIndex = 0;

  public:
    CLI_WordParser() = delete;

    CLI_WordParser(
      CR_INT argc,
      char *argv[],
      CR_VEC_STR keywords = {},
      CR_BOL assigning = true
    );

    // capture arguments of keyword into the vector maps
    void assign();

    // check keyword existence in vectors
    bool has(CR_STR keyword);

    // get size without giving access to vector at keyword
    size_t size(CR_STR keyword);

    // get value of vector at keyword
    std::string at(CR_STR keyword, CR_SZ index);
    std::string last(CR_STR keyword);

    // move and empty vector at keyword
    VEC_STR extract(CR_STR keyword);
  };

  //_________|
  // NUMBERS |
  //_________|

  template <inspector::NUMBER T>
  class CLI_NumberParser : public virtual CLI_TitleParser {
  protected:
    STRUNORMAP<VEC<T>> numbers;
    static constexpr int typeIndex = 1;

    void assignTryCatch(CR_INT i, CR_INT j);

  public:
    CLI_NumberParser() = delete;

    CLI_NumberParser(
      CR_INT argc,
      char *argv[],
      CR_VEC_STR keywords = {},
      CR_BOL assigning = true
    );

    void assign();
    bool has(CR_STR keyword);
    size_t size(CR_STR keyword);

    T at(CR_STR keyword, CR_SZ index);
    T last(CR_STR keyword);
    VEC<T> extract(CR_STR keyword);
  };

  //_________|
  // TOGGLES |
  //_________|

  class CLI_ToggleParser : public virtual CLI_TitleParser {
  protected:
    STRUNORMAP<VEC_BOL> toggles;
    static constexpr int typeIndex = 2;

    bool booleanize(std::string &input);

  public:
    CLI_ToggleParser() = delete;

    CLI_ToggleParser(
      CR_INT argc,
      char *argv[],
      CR_VEC_STR keywords = {},
      CR_BOL assigning = true
    );

    void assign();
    bool has(CR_STR keyword);
    size_t size(CR_STR keyword);

    bool at(CR_STR keyword, CR_SZ index);
    bool last(CR_STR keyword);
    VEC_BOL extract(CR_STR keyword);
  };

  //________|
  // UNITED |
  //________|

  /**
   * If you want a method of a specific parser type,
   * you should call it by its class namespace.
   * 
   * For example:
   *   mt::VEC_INT extractedNumbers = CLI_NumberParser<int>::extract("my-keyword");
   *
   * Set such a variable to just get a vector of numbers at 'my-keyword'
   * without having to assign with redundant 'std::tuple'.
   */
  template <inspector::NUMBER T>
  class CLI_Parser final :
    public CLI_WordParser,
    public CLI_NumberParser<T>,
    public CLI_ToggleParser {

  private:
    typedef std::tuple<std::string, std::string, T, bool> CLI_VAL_TUPLE;
    typedef std::tuple<VEC_STR, VEC_STR, VEC<T>, VEC_BOL> CLI_VEC_TUPLE;

  public:
		CLI_Parser() = delete;

		CLI_Parser(
			CR_INT argc,
			char *argv[],
			CR_VEC_STR wordKeywords = {},
      CR_VEC_STR numberKeywords = {},
      CR_VEC_STR toggleKeywords = {}
		);

    /**
     * Check 'titles' to select the type
     * or group of commands before the next process.
     */
    bool entry(CR_STR input = "");

    /**
     * These methods will interact with
     * the 4 classes above.
     */

    void assign();
		bool has(CR_STR keyword);

    size_t size(CR_STR keyword);
    ARR_SZ<4> sizes(CR_STR keyword);

    CLI_VAL_TUPLE at(CR_STR keyword, CR_SZ index);
    CLI_VAL_TUPLE last(CR_STR keyword);
    CLI_VEC_TUPLE extract(CR_STR keyword);
  };
}}

#include "utils/cli-parser.tpp"
#endif // __MINI_TOOLS__UTILS__CLI_PARSER_HPP__