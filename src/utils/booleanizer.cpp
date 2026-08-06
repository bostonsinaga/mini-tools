#ifndef __MINI_TOOLS__UTILS__BOOLEANIZER_CPP__
#define __MINI_TOOLS__UTILS__BOOLEANIZER_CPP__

#include "utils/scanner.hpp"
#include "utils/str-tool.hpp"
#include "utils/booleanizer.hpp"

namespace mini_tools{
namespace utils {

  VEC_STR Booleanizer::getTrueTerms(CR_STR existingISOCode) {
    if (hasISOCode(existingISOCode)) {
      return trueTerms[existingISOCode];
    }
    return {};
  }

  VEC_STR Booleanizer::getFalseTerms(CR_STR existingISOCode) {
    if (hasISOCode(existingISOCode)) {
      return falseTerms[existingISOCode];
    }
    return {};
  }

  BOOLEANIZER_CODE Booleanizer::test(
    CR_STR existingISOCode,
    CR_STR input
  ) {
    // input is zero or text
    if (!Scanner::stringToNumber<int>(input)) {

      // terms are always case-insensitive
      std::string uppercase = StrTool::copyStringToUppercase(input),
        lowercase = StrTool::copyStringToLowercase(input);

      if (hasISOCode(existingISOCode)) {
        // false
        for (CR_STR term : falseTerms[existingISOCode]) {
          if (uppercase == term) return BOOLEANIZER_FALSE;
          else if (lowercase == term) return BOOLEANIZER_FALSE;
        }

        // true
        for (CR_STR term : trueTerms[existingISOCode]) {
          if (uppercase == term) return BOOLEANIZER_TRUE;
          else if (lowercase == term) return BOOLEANIZER_TRUE;
        }
      }

      // input does not match any terms
      return BOOLEANIZER_OTHER;
    }

    // input is not zero
    return BOOLEANIZER_TRUE;
  }

  bool Booleanizer::hasISOCode(CR_STR existingISOCode) {
    return trueTerms.find(existingISOCode) != trueTerms.end();
  }

  void Booleanizer::addTerms(
    CR_STR newISOCode,
    CR_VEC_STR newTrueTerms,
    CR_VEC_STR newFalseTerms
  ) {
    trueTerms[newISOCode] = newTrueTerms;
    falseTerms[newISOCode] = newFalseTerms;
  }

  void Booleanizer::changeTerms(
    CR_STR existingISOCode,
    CR_VEC_STR existingTrueTerms,
    CR_VEC_STR existingFalseTerms
  ) {
    if (hasISOCode(existingISOCode)) {
      addTerms(
        existingISOCode,
        existingTrueTerms,
        existingFalseTerms
      );
    }
  }

  void Booleanizer::removeTerms(CR_STR existingISOCode) {
    trueTerms.erase(existingISOCode);
    falseTerms.erase(existingISOCode);
  }
}}

#endif // __MINI_TOOLS__UTILS__BOOLEANIZER_CPP__