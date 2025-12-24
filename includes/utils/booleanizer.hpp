#ifndef __MINI_TOOLS__UTILS__BOOLEANIZER_HPP__
#define __MINI_TOOLS__UTILS__BOOLEANIZER_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {

  /**
   * Interpret string as boolean.
   */
  class Booleanizer {
  private:
    /**
     * UNORDERED MAPS
     * Default is english.
     * 
     * All strings are expected to be interpreted
     * as representing the boolean values.
     * 
     * The 'falseTerms' is actually used as example of false input in
     * description of user class. The tester only evaluates 'trueTerms'.
     */
    STRUNORMAP<VEC_STR>
      trueTerms = {{ "en", {"TRUE", "YES", "Y"} }},
      falseTerms = {{ "en", {"FALSE", "NO", "N"} }};

  public:
    Booleanizer() {}
    VEC_STR getTrueTerms(CR_STR existingISOCode);
    VEC_STR getFalseTerms(CR_STR existingISOCode);

    /**
     * Compare each selected 'trueTerms' vector with 'input'.
     * Return false if the input is interpreted as:
     * - The string 'false'
     * - The numeric value zero
     * - A term in 'falseTerms'
     * - Or a term not included in the allowed list
     */
    bool test(
      CR_STR existingISOCode,
      std::string input
    );

    /** Modify extension for other languages */

    bool hasISOCode(CR_STR existingISOCode);

    void addTerms(
      CR_STR newISOCode,
      CR_VEC_STR newTrueTerms,
      CR_VEC_STR newFalseTerms
    );

    void changeTerms(
      CR_STR existingISOCode,
      CR_VEC_STR existingTrueTerms,
      CR_VEC_STR existingFalseTerms
    );

    void removeTerms(CR_STR existingISOCode);
  };
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_TPP__