#ifndef __MINI_TOOLS__UTILS__BOOLEANIZER_HPP__
#define __MINI_TOOLS__UTILS__BOOLEANIZER_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {

  enum BOOLEANIZER_CODE {
    BOOLEANIZER_FALSE,
    BOOLEANIZER_TRUE,
    BOOLEANIZER_OTHER
  };

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
     */
    UNORMAP_STR<VEC_STR>
      trueTerms = {{ "en", {"TRUE", "YES", "Y"} }},
      falseTerms = {{ "en", {"FALSE", "NO", "N"} }};

  public:
    Booleanizer() {}
    VEC_STR getTrueTerms(CR_STR existingISOCode);
    VEC_STR getFalseTerms(CR_STR existingISOCode);

    /**
     * Compare each selected 'falseTerms' and 'trueTerms' vectors with given input.
     * Return 'BOOLEANIZER_OTHER' if the input is not included in the terms list.
     */
    BOOLEANIZER_CODE test(
      CR_STR existingISOCode,
      CR_STR input
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