#ifndef __MINI_TOOLS__UTILS__BOOLEANIZER_CPP__
#define __MINI_TOOLS__UTILS__BOOLEANIZER_CPP__

#include "utils/scanner.hpp"
#include "utils/str-tools.hpp"
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

  // only evaluate the 'trueTerms' to return true
  bool Booleanizer::test(
    CR_STR existingISOCode,
    std::string input
  ) {
    // 'input' is zero
    if (!Scanner::stringToNumber<int>(input)) {
      StrTools::modifyStringToUppercase(input);

      if (hasISOCode(existingISOCode)) {
        for (CR_STR term : trueTerms[existingISOCode]) {
          if (input == term) return true;
        }
      }

      // 'input' does not match any 'trueTerms'
      return false;
    }

    // 'input' is not zero
    return true;
  }

  bool Booleanizer::hasISOCode(CR_STR existingISOCode) {
    return STRUNORMAP_FOUND<VEC_STR>(trueTerms, existingISOCode);
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