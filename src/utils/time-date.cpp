#ifndef __MINI_TOOLS__UTILS__TIME_DATE_CPP__
#define __MINI_TOOLS__UTILS__TIME_DATE_CPP__

#include "utils/time-date.hpp"
#include "utils/scanner.hpp"
#include "utils/str-tools.hpp"

namespace mini_tools {
namespace utils {
namespace Timer {

  //___________|
  // STOPWATCH |
  //___________|

  /** SETTERS */

  void Stopwatch::reset() {
    prior = std::chrono::high_resolution_clock::now();
    difference = std::chrono::nanoseconds::zero();
  }

  void Stopwatch::check() {
    TP now = std::chrono::high_resolution_clock::now();
    difference = now - Stopwatch::prior;
    prior = now;
  }

  void Stopwatch::setTitle(CR_STR title_in) {
    title = title_in;
  }

  /** GETTERS */

  double Stopwatch::getMilliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
      Stopwatch::difference
    ).count();
  }

  double Stopwatch::getSeconds() {
    return difference.count();
  }

  double Stopwatch::getMinutes() {
    return getSeconds() / 60;
  }

  double Stopwatch::getHours() {
    return getMinutes() / 60;
  }

  /** DISPLAYERS */

  void Stopwatch::printInMilliseconds() {
    std::cout << title << std::endl;
    std::cout << Stopwatch::getMilliseconds() << "ms\n";
  }

  void Stopwatch::printInSeconds() {
    std::cout << title << std::endl;
    std::cout << Stopwatch::getSeconds() << "s\n";
  }

  void Stopwatch::printInMinutes() {
    std::cout << title << std::endl;
    std::cout << Stopwatch::getMinutes() << "m\n";
  }

  void Stopwatch::printInHours() {
    std::cout << title << std::endl;
    std::cout << Stopwatch::getHours() << "m\n";
  }

  //______|
  // DATE |
  //______|

  Date::ImplicitCentury Date::implicitCentury;

  const int Date::monthDays[12][2] {
    {31, 31}, // January
    {28, 29}, // February
    {31, 31}, // March
    {30, 30}, // April
    {31, 31}, // May
    {30, 30}, // June
    {31, 31}, // July
    {31, 31}, // August
    {30, 30}, // September
    {31, 31}, // October
    {30, 30}, // November
    {31, 31}  // December
  };

  STRUNORMAP<ARR2_STR<12, 2>> Date::monthNames = {
    {"en", ARR2_STR<12, 2>{
      ARR_STR<12>{ // long
        "january", "february", "march",
        "april", "may", "june",
        "july", "august", "september",
        "october", "november", "december"
      },
      ARR_STR<12>{ // short
        "jan", "feb", "mar", "apr",
        "may", "jun", "jul", "aug",
        "sep", "oct", "nov", "dec"
      }
    }}
  };

  STRUNORMAP<PAIR_STR> Date::christTimeSign = {{"en", {"BC", "AD"}}};

  Date::Date(
    CR_INT dd_in,
    CR_INT mm_in,
    CR_INT yyyy_in,
    const Stopwatch &stopwatch_in
  ) {
    dd = dd_in;
    mm = mm_in;
    yyyy = yyyy_in;
    stopwatch = stopwatch_in;

    /** Zero Handlers */

    // zero year
    if (yyyy == 0) yyyy = -1;

    // zero month
    if (mm == 0) {
      mm = 12;
      yyyy--;
      if (yyyy == 0) yyyy = -1;
    }

    // zero day
    if (dd == 0) {
      mm--;

      // zero month
      if (mm == 0) {
        mm = 12;
        yyyy--;
        if (yyyy == 0) yyyy = -1;
      }

      // last day of the month
      dd = monthDays[mm-1][isLeapYear()];
    }

    /** Solve excessive months */

    int mm_sign = std::abs(mm) / mm;
    mm = std::abs(mm);

    while (mm > 12) {
      mm -= 12;
      yyyy += mm_sign;
    }

    /** Solve excessive days */

    int mm_index = mm - 1;
    int leapIndex = isLeapYear();
    int dd_sign = std::abs(dd) / dd;
    dd = std::abs(dd);

    while (dd > monthDays[mm_index][leapIndex]) {
      dd -= monthDays[mm_index][leapIndex];
      mm_index += dd_sign;

      // go to next year
      if (mm_index == 12) {
        yyyy++;
        mm_index = 0;
        if (yyyy == 0) yyyy = 1;
        leapIndex = isLeapYear();
      }
      // go to previous year
      else if (mm_index == -1) {
        yyyy--;
        mm_index = 11;
        if (yyyy == 0) yyyy = -1;
        leapIndex = isLeapYear();
      }
    }

    mm = mm_index + 1;

    // value sign of BC or AD
    yearSign = std::abs(yyyy) / yyyy;
  }

  bool Date::isLanguageKeyExist(CR_STR languageKey_in) {
    return STRUNORMAP_FOUND<ARR2_STR<12, 2>>(Date::monthNames, languageKey_in);
  }

  std::string Date::getCapitalizedNamedMonth(CR_INT longShortIndex) const {
    return StrTools::copyCharToUppercase(
      Date::monthNames[Date::languageKey][longShortIndex][mm - 1], 0
    );
  }

  std::string Date::getAllCapsNamedMonth(CR_INT longShortIndex) const {
    return StrTools::copyStringToUppercase(
      Date::monthNames[Date::languageKey][longShortIndex][mm - 1]
    );
  }

  /** STATIC METHODS */

  void Date::setUnsignedChristTimeYear(CR_INT yyyy_in) {
    if (yyyy_in == 0) unsignedChristTimeYear = 1;
    else unsignedChristTimeYear = yyyy_in;
  }

  void Date::setRecognizedYearsInterval(CR_PAIR_INT yyyy_pair) {
    if (yyyy_pair.first > yyyy_pair.second) {
      Date::recognizedYearsInterval.first = yyyy_pair.second;
      Date::recognizedYearsInterval.second = yyyy_pair.first;
    }
    else Date::recognizedYearsInterval = yyyy_pair;
  }

  PAIR_INT Date::getRecognizedYearsInterval() {
    return Date::recognizedYearsInterval;
  }

  /** MULTILINGUAL TERM SETTERS */

  void Date::setMonthNames(
    CR_ARR_STR<2> january, CR_ARR_STR<2> february, CR_ARR_STR<2> march,
    CR_ARR_STR<2> april,   CR_ARR_STR<2> may,      CR_ARR_STR<2> june,
    CR_ARR_STR<2> july,    CR_ARR_STR<2> august,   CR_ARR_STR<2> september,
    CR_ARR_STR<2> october, CR_ARR_STR<2> november, CR_ARR_STR<2> december
  ) {
    for (int i = 0; i < 2; i++) {
      Date::monthNames[Date::languageKey][0][i]  = january[i];
      Date::monthNames[Date::languageKey][1][i]  = february[i];
      Date::monthNames[Date::languageKey][2][i]  = march[i];
      Date::monthNames[Date::languageKey][3][i]  = april[i];
      Date::monthNames[Date::languageKey][4][i]  = may[i];
      Date::monthNames[Date::languageKey][5][i]  = june[i];
      Date::monthNames[Date::languageKey][6][i]  = july[i];
      Date::monthNames[Date::languageKey][7][i]  = august[i];
      Date::monthNames[Date::languageKey][8][i]  = september[i];
      Date::monthNames[Date::languageKey][9][i]  = october[i];
      Date::monthNames[Date::languageKey][10][i] = november[i];
      Date::monthNames[Date::languageKey][11][i] = december[i];
    }
  }

  void Date::setChristTimeSign(
    CR_STR beforeChristTerm,
    CR_STR annoDominiTerm
  ) {
    Date::christTimeSign[Date::languageKey] = {
      beforeChristTerm, annoDominiTerm
    };
  }

  /** FROM STRING PARSER */

  VEC<Date> Date::parseDates(CR_STR text, CR_BOL implyCentury) {
    enum value_code {
      value_other,
      value_number,
      value_word
    };

    VEC_PAIR2<std::string, value_code> valcod;
    ARR<value_code, 2> eqdiff;
    value_code first_value = value_other;

    /** Potential Values Separation */

    for (int i = 0; i < text.length(); i++) {

      // start only from number or word
      if (StrTools::isDigit(text[i])) {
        first_value = value_number;
      }
      else if (StrTools::isLetter(text[i])) {
        first_value = value_word;
      }

      if (first_value) {
        // initialization
        valcod = {{"", first_value}};
        eqdiff = {first_value, first_value};

        for (int j = i; j < text.length(); j++) {
          eqdiff[0] = eqdiff[1];

          if (StrTools::isDigit(text[j])) {
            eqdiff[1] = value_number;
          }
          else if (StrTools::isLetter(text[j])) {
            eqdiff[1] = value_word;
          }
          else { // non-number and non-word
            eqdiff[1] = value_other;
            continue;
          }

          // continue the last 'valcod'
          if (eqdiff[0] == eqdiff[1]) {
            valcod.back().first += text[j];
          }
          // add new 'valcod'
          else valcod.push_back({
            std::string(1, text[j]), eqdiff[1]
          });
        }

        break;
      }
    }

    /** Evaluate Patterns */

    VEC<Date> dates;
    bool needReset = true;
    int buffer, might_dd = 0, might_mm = 0, might_yyyy = 0;

    /**
     * Will be assigned with 1 function from 3 versions which have
     * different order of 3 date component detection conditions.
     */
    std::function<void()> detect = [&](){};

    // reset when 'needReset' is true
    std::function<void()> reset = [&]() {
      might_dd = 0;
      might_mm = 0;
      might_yyyy = 0;
    };

    // apply implicit century
    std::function<void()> implyCenturyToBuffer = [&]() {
      if (implyCentury) {

        // temporary variables
        int absAffixYear = std::abs(Date::implicitCentury.affixYear);
        int absBuffer = std::abs(buffer);
        int absBufferDiv = absBuffer;
        int bufferDigitsCount = 0;

        // find buffer digits count
        while (absBufferDiv > 0) {
          absBufferDiv /= 10;
          bufferDigitsCount++;
        }

        // buffer digits count is equals to year pattern digits count
        if (bufferDigitsCount == Date::implicitCentury.patternDigitsCount) {

          int vsignAffixYear = 1;
          int vsignBuffer = 1;
          int multiplier = 1;
          absBufferDiv = absBuffer;

          // find value signs
          if (absAffixYear != 0) vsignAffixYear = absAffixYear / Date::implicitCentury.affixYear;
          if (absBuffer != 0) vsignBuffer = absBuffer / buffer;

          // find power of ten multiplier
          while (absBufferDiv > 0) {
            absBufferDiv /= 10;
            multiplier *= 10;
          }

          // stick 'affixYear' with 'buffer' (e.g. 20 with 25 = 2025)
          buffer = (
            // final value sign
            vsignAffixYear * vsignBuffer
            // make 'absAffixYear' have enough 0 digits to be filled by 'absBuffer'
            * (absAffixYear * multiplier + absBuffer)
          );
        }
      }
    };

    // limited by years interval
    std::function<bool()> isInRecognizedYearsInterval = [&]()->bool {
      if (buffer >= Date::recognizedYearsInterval.first &&
        buffer <= Date::recognizedYearsInterval.second
      ) {
        might_yyyy = buffer;
        return true;
      }
      return false;
    };

    // 'might_mm' and 'might_yyyy' should have been found
    std::function<void()> pushValidDate = [&]() {

      // limited by different maximum days in a month
      if (might_dd <= Date::monthDays[Date::isLeapYear(might_yyyy)][might_mm - 1]) {

        dates.push_back(Date(
          might_dd, might_mm, might_yyyy
        ));
      }
    };

    // conditional function selection
    switch (Date::formatCode) {
      case LITTLE_ENDIAN: {
        detect = [&]() {
          if (!might_dd && buffer < 31) { // day
            might_dd = buffer;
            needReset = false;
          }
          else if (might_dd && !might_mm && buffer < 12) { // month
            might_mm = buffer;
            needReset = false;
          }
          else if (might_dd && might_mm) { // year
            implyCenturyToBuffer();
            if (isInRecognizedYearsInterval()) pushValidDate();
          }
        };
      break;}
      case MIDDLE_ENDIAN: {
        detect = [&]() {
          if (!might_mm && buffer < 12) { // month
            might_mm = buffer;
            needReset = false;
          }
          else if (might_mm && !might_dd && buffer < 31) { // day
            might_dd = buffer;
            needReset = false;
          }
          else if (might_mm && might_dd) { // year
            implyCenturyToBuffer();
            if (isInRecognizedYearsInterval()) pushValidDate();
          }
        };
      break;}
      case BIG_ENDIAN: {
        detect = [&]() {
          if (!might_yyyy) { // year
            implyCenturyToBuffer();
            if (isInRecognizedYearsInterval()) needReset = false;
          }
          else if (might_yyyy && !might_mm && buffer < 12) { // month
            might_mm = buffer;
            needReset = false;
          }
          else if (might_yyyy && might_mm) {
            might_dd = buffer;
            pushValidDate();
          }
        };
      break;}
    }

    // string-code iteration 
    for (int i = 0; i < valcod.size(); i++) {
      if (valcod[i].second == value_number) {

        // this number is a potential date component
        buffer = Scanner::stringToNumber<int>(valcod[i].first);
        detect();

        // reset valid or invalid pattern
        if (needReset) reset();
        needReset = false;
      }
      else { // 'value_word': string that might be a named month
        if (!might_yyyy) continue;
        int detected_mm = 0;

        // convert to lowercase
        StrTools::modifyStringToLowercase(valcod[i].first);

        // 2D array loop
        for (int j = 0; j < 2; j++) {
          for (int k = 0; k < Date::monthNames[Date::languageKey][j].size(); k++) {

            // named month found and loop stopped
            if (valcod[i].first == Date::monthNames[Date::languageKey][j][k]) {
              detected_mm = k + 1;
              break;
            }
          }

          if (detected_mm) break;
        }

        if (detected_mm) {
          // month already exist
          if (might_mm) reset();
          // valid pattern (saved)
          else might_mm = detected_mm;
        }
        // named month not found
        else reset();
      }
    }

    return dates;
  }

  /** LEAP YEARS COUNTERS */

  bool Date::isLeapYear(int yyyy_test) {
    if (yyyy_test < 0) yyyy_test++;
    return (yyyy_test % 4 == 0 && yyyy_test % 100 != 0) || yyyy_test % 400 == 0;
  }

  bool Date::isLeapYear() const {
    return (yyyy % 4 == 0 && yyyy % 100 != 0) || yyyy % 400 == 0;
  }

  int Date::countLeapYearsFromZero(int yyyy_test) {
    if (yyyy_test < 0) yyyy_test++;
    return yyyy_test / 4 - yyyy_test / 100 + yyyy_test / 400;
  }

  int Date::countLeapYearsFromZero() const {
    return yyyy / 4 - yyyy / 100 + yyyy / 400;
  }

  int Date::countLeapYearsFrom(const Date &date) const {
    return countLeapYearsFromZero() - date.countLeapYearsFromZero();
  }

  /** DAYS COUNTERS */

  int Date::countDaysThisYear() const {
    int count = 0;

    for (int i = 0; i < mm - 1; i++) {
      count += Date::monthDays[i][isLeapYear()];
    }

    return count + dd - 1;
  }

  int Date::reverseCountDaysThisYear() const {
    int count = 0, leapIndex = isLeapYear();

    for (int i = 11; i > mm - 1; i--) {
      count += Date::monthDays[i][leapIndex];
    }

    return count + Date::monthDays[mm - 1][leapIndex] - dd;
  }

  int Date::countDaysFromZero() const {
    // years in days
    int count = (yyyy - yearSign) * 365;
    count + Date::countLeapYearsFromZero();

    // this year in days
    if (yearSign > 0) {
      return count + countDaysThisYear();
    }
    return count + reverseCountDaysThisYear();
  }

  int Date::countDaysFrom(const Date &date) const {
    int dateDays = date.countDaysFromZero();

    if (dateDays < 0) dateDays -= 366;

    return countDaysFromZero() - dateDays;
  }

  /** MONTHS COUNTERS */

  int Date::countMonthsThisYear() const { return mm - 1; }
  int Date::reverseCountMonthsThisYear() const { return 12 - mm; }

  int Date::countMonthsFromZero() const {
    // years in months
    int count = (yyyy - yearSign) * 12;

    // this year in months
    if (yearSign > 0) {
      return count + countMonthsThisYear();
    }
    return count + reverseCountMonthsThisYear();
  }

  int Date::countMonthsFrom(const Date &date) const {
    return countMonthsFromZero() - date.countMonthsFromZero();
  }

  /** YEARS COUNTERS */

  int Date::countYearsFromZero(const Date &date) const {
    return yyyy - yearSign;
  }

  int Date::countYearsFrom(const Date &date) const {
    int dateYear = date.yyyy;

    if (date.yearSign < yearSign) dateYear++;
    else if (date.yearSign > yearSign) dateYear--;

    return yyyy - dateYear;
  }

  /** STRINGIFIERS */

  std::string Date::applyChristTimeSign() const {

    if (yyyy < Date::unsignedChristTimeYear) {
      if (yyyy / std::abs(yyyy) > 0) {
        return ' ' + Date::christTimeSign[Date::languageKey].second;
      }
      return ' ' + Date::christTimeSign[Date::languageKey].first;
    }

    return "";
  }

  std::string Date::applyZeroPrefixDate() const {
    return (dd < 10 ? '0' : '\0') + std::to_string(dd);
  }

  std::string Date::applyZeroPrefixMonth() const {
    return (mm < 10 ? '0' : '\0') + std::to_string(mm);
  }

  std::string Date::applyZeroPrefixYearWithChristTimeSign() const {
    return std::string(4 - std::log10(std::abs(yyyy)), '0')
      + std::to_string(std::abs(yyyy)) + applyChristTimeSign();
  }

  std::string Date::applyZeroPrefixYearWithNumberSign() const {
    return (yyyy < 0 ? '-' : '\0')
      + std::string(4 - std::log10(std::abs(yyyy)), '0')
      + std::to_string(std::abs(yyyy));
  }

  std::string Date::numericStringify() const {
    switch (Date::formatCode) {
      case LITTLE_ENDIAN:
        return applyZeroPrefixDate()
          + Date::separator + applyZeroPrefixMonth()
          + Date::separator + applyZeroPrefixYearWithChristTimeSign();
      case MIDDLE_ENDIAN:
        return applyZeroPrefixMonth()
          + Date::separator + applyZeroPrefixDate()
          + Date::separator + applyZeroPrefixYearWithChristTimeSign();
      case BIG_ENDIAN:
        return applyZeroPrefixYearWithNumberSign()
          + Date::separator + applyZeroPrefixMonth()
          + Date::separator + applyZeroPrefixDate();
      default: return "";
    }
  }

  std::string Date::capitalizedStringify(CR_INT longShortIndex) const {
    switch (Date::formatCode) {
      case LITTLE_ENDIAN:
        return applyZeroPrefixDate()
          + ' ' + getCapitalizedNamedMonth(longShortIndex)
          + ' ' + applyZeroPrefixYearWithChristTimeSign();
      case MIDDLE_ENDIAN:
        return getCapitalizedNamedMonth(longShortIndex)
          + ' ' + applyZeroPrefixDate()
          + ' ' + applyZeroPrefixYearWithChristTimeSign();
      case BIG_ENDIAN:
        return applyZeroPrefixYearWithNumberSign()
          + ' ' + getCapitalizedNamedMonth(longShortIndex)
          + ' ' + applyZeroPrefixDate();
      default: return "";
    }
  }

  std::string Date::allCapsStringify(CR_INT longShortIndex) const {
    switch (Date::formatCode) {
      case LITTLE_ENDIAN:
        return applyZeroPrefixDate()
          + ' ' + getAllCapsNamedMonth(longShortIndex)
          + ' ' + applyZeroPrefixYearWithChristTimeSign();
      case MIDDLE_ENDIAN:
        return getAllCapsNamedMonth(longShortIndex)
          + ' ' + applyZeroPrefixDate()
          + ' ' + applyZeroPrefixYearWithChristTimeSign();
      case BIG_ENDIAN:
        return applyZeroPrefixYearWithNumberSign()
          + ' ' + getAllCapsNamedMonth(longShortIndex)
          + ' ' + applyZeroPrefixDate();
      default: return "";
    }
  }

  std::string Date::longCapitalizedStringify() const {
    return capitalizedStringify(0);
  }

  std::string Date::shortCapitalizedStringify() const {
    return capitalizedStringify(1);
  }

  std::string Date::longAllCapsStringify() const {
    return allCapsStringify(0);
  }

  std::string Date::shortAllCapsStringify() const {
    return allCapsStringify(1);
  }

  bool Date::operator==(const Date &withDate) const {
    return (
      yyyy == withDate.yyyy &&
      mm == withDate.mm &&
      dd == withDate.dd
    );
  }

  bool Date::operator<(const Date &withDate) const {
    return (
      (yyyy < withDate.yyyy) ||
      (yyyy == withDate.yyyy && mm < withDate.mm) ||
      (yyyy == withDate.yyyy && mm == withDate.mm && dd < withDate.dd)
    );
  }

  bool Date::operator>(const Date &withDate) const {
    return (
      (yyyy > withDate.yyyy) ||
      (yyyy == withDate.yyyy && mm > withDate.mm) ||
      (yyyy == withDate.yyyy && mm == withDate.mm && dd > withDate.dd)
    );
  }

  bool Date::operator<=(const Date &withDate) const {
    return (
      (yyyy < withDate.yyyy) ||
      (yyyy == withDate.yyyy && mm < withDate.mm) ||
      (yyyy == withDate.yyyy && mm == withDate.mm && dd < withDate.dd)
    ) || (
      (yyyy < withDate.yyyy) ||
      (yyyy == withDate.yyyy && mm < withDate.mm) ||
      (yyyy == withDate.yyyy && mm == withDate.mm && dd < withDate.dd)
    );
  }

  bool Date::operator>=(const Date &withDate) const {
    return (
      (yyyy < withDate.yyyy) ||
      (yyyy == withDate.yyyy && mm < withDate.mm) ||
      (yyyy == withDate.yyyy && mm == withDate.mm && dd < withDate.dd)
    ) || (
      (yyyy > withDate.yyyy) ||
      (yyyy == withDate.yyyy && mm > withDate.mm) ||
      (yyyy == withDate.yyyy && mm == withDate.mm && dd > withDate.dd)
    );
  }

  //________|
  // SPREAD |
  //________|

  // only 1 of the 3 parameters will have a value
  VEC<Date> Spread::everyDateDistribute(
    CR_INT dd_diff,
    CR_INT mm_diff,
    CR_INT yyyy_diff
  ) {
    VEC<Date> dates;
    if (inclusive) dates.push_back(interval.first);

    // only 1 of the 3 parameters will have a non-zero value
    if (dd_diff != 0 || mm_diff != 0 || yyyy_diff != 0) {

      // initial part
      Date part = Date(
        interval.first.getDay() + dd_diff,
        interval.first.getMonth() + mm_diff,
        interval.first.getYear() + yyyy_diff
      );

      while (part < interval.second) {
        dates.push_back(part);

        // next part
        part = Date(
          dates.back().getDay() + dd_diff,
          dates.back().getMonth() + mm_diff,
          dates.back().getYear() + yyyy_diff
        );
      }
    }

    if (inclusive) dates.push_back(interval.second);
    return dates;
  }

  VEC<Date> Spread::everyDaysDistribute(CR_INT difference) {
    return everyDateDistribute(difference, 0, 0);
  }

  VEC<Date> Spread::everyMonthsDistribute(CR_INT difference) {
    return everyDateDistribute(0, difference, 0);
  }

  VEC<Date> Spread::everyYearsDistribute(CR_INT difference) {
    return everyDateDistribute(0, 0, difference);
  }

  VEC<Date> Spread::fixedNumberDistribute(CR_INT quantity) {
    if (quantity != 0) {
      return everyDaysDistribute(
        interval.second.countDaysFrom(interval.first) / quantity
      );
    }
    else if (inclusive) {
      return {interval.first, interval.second};
    }
    return {};
  }
}}}

#endif // __MINI_TOOLS__UTILS__TIME_DATE_CPP__