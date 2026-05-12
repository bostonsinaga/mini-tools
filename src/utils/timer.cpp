#ifndef __MINI_TOOLS__UTILS__TIMER_CPP__
#define __MINI_TOOLS__UTILS__TIMER_CPP__

#include "algorithms/number-sequence.hpp"
#include "utils/timer.hpp"
#include "utils/scanner.hpp"
#include "utils/str-tool.hpp"

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

  std::string Stopwatch::getMillisecondsString(CR_STR timeUnit) {
    return std::to_string(Stopwatch::getMilliseconds()) + timeUnit;
  }

  std::string Stopwatch::getSecondsString(CR_STR timeUnit) {
    return std::to_string(Stopwatch::getSeconds()) + timeUnit;
  }

  std::string Stopwatch::getMinutesString(CR_STR timeUnit) {
    return std::to_string(Stopwatch::getMinutes()) + timeUnit;
  }

  std::string Stopwatch::getHoursString(CR_STR timeUnit) {
    return std::to_string(Stopwatch::getHours()) + timeUnit;
  }

  //______|
  // DATE |
  //______|

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
  }

  bool Date::isLanguageKeyExist(CR_STR languageKey_in) {
    return STRUNORMAP_FOUND<ARR2_STR<12, 2>>(Date::monthNames, languageKey_in);
  }

  std::string Date::getCapitalizedNamedMonth(CR_INT longShortIndex) const {
    return StrTool::copyCharToUppercase(
      Date::monthNames[Date::languageKey][longShortIndex][mm - 1], 0
    );
  }

  std::string Date::getAllCapsNamedMonth(CR_INT longShortIndex) const {
    return StrTool::copyStringToUppercase(
      Date::monthNames[Date::languageKey][longShortIndex][mm - 1]
    );
  }

  /** STATIC METHODS */

  void Date::setUnsignedChristTimeYear(CR_INT yyyy_in) {
    if (yyyy_in == 0) unsignedChristTimeYear = 1;
    else unsignedChristTimeYear = yyyy_in;
  }

  /** MULTILINGUAL TERM SETTERS */

  void Date::setMonthNames(
    CR_ARR_STR<2> january, CR_ARR_STR<2> february, CR_ARR_STR<2> march,
    CR_ARR_STR<2> april,   CR_ARR_STR<2> may,      CR_ARR_STR<2> june,
    CR_ARR_STR<2> july,    CR_ARR_STR<2> august,   CR_ARR_STR<2> september,
    CR_ARR_STR<2> october, CR_ARR_STR<2> november, CR_ARR_STR<2> december
  ) {
    for (int i = 0; i < 2; i++) {
      Date::monthNames[Date::languageKey][i][0]  = january[i];
      Date::monthNames[Date::languageKey][i][1]  = february[i];
      Date::monthNames[Date::languageKey][i][2]  = march[i];
      Date::monthNames[Date::languageKey][i][3]  = april[i];
      Date::monthNames[Date::languageKey][i][4]  = may[i];
      Date::monthNames[Date::languageKey][i][5]  = june[i];
      Date::monthNames[Date::languageKey][i][6]  = july[i];
      Date::monthNames[Date::languageKey][i][7]  = august[i];
      Date::monthNames[Date::languageKey][i][8]  = september[i];
      Date::monthNames[Date::languageKey][i][9]  = october[i];
      Date::monthNames[Date::languageKey][i][10] = november[i];
      Date::monthNames[Date::languageKey][i][11] = december[i];
    }
  }

  std::string Date::getMonthName(CR_INT index, CR_BOL isShortened) {
    return Date::monthNames[Date::languageKey][isShortened][index];
  }

  Date::NamedMonthLengths Date::createNamedMonthLengths() {
    NamedMonthLengths lengths;

    for (int i = 0; i < 12; i++) {
      lengths.longArray[i] = Date::monthNames[Date::languageKey][0][i].length();
    }

    for (int i = 0; i < 12; i++) {
      lengths.shortArray[i] = Date::monthNames[Date::languageKey][1][i].length();
    }

    return lengths;
  }

  void Date::setChristTimeSign(
    CR_STR beforeChristTerm,
    CR_STR annoDominiTerm
  ) {
    Date::christTimeSign[Date::languageKey] = {
      beforeChristTerm, annoDominiTerm
    };
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
    int count = (yyyy - (yyyy / std::abs(yyyy))) * 365;
    count + Date::countLeapYearsFromZero();

    // this year in days
    if (yyyy > 0) {
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
    int count = (yyyy - (yyyy / std::abs(yyyy))) * 12;

    // this year in months
    if (yyyy > 0) {
      return count + countMonthsThisYear();
    }
    return count + reverseCountMonthsThisYear();
  }

  int Date::countMonthsFrom(const Date &date) const {
    return countMonthsFromZero() - date.countMonthsFromZero();
  }

  /** YEARS COUNTERS */

  int Date::countYearsFromZero(const Date &date) const {
    return yyyy - (yyyy / std::abs(yyyy));
  }

  int Date::countYearsFrom(const Date &date) const {
    int dateYear = date.yyyy;
    int thisYearSign = yyyy / std::abs(yyyy);
    int dateYearSign = dateYear / std::abs(dateYear);

    if (dateYearSign < thisYearSign) dateYear++;
    else if (dateYearSign > thisYearSign) dateYear--;

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
    return (dd < 10 && Date::usingZeroPrefix ? '0' : '\0') + std::to_string(dd);
  }

  std::string Date::applyZeroPrefixMonth() const {
    return (mm < 10 && Date::usingZeroPrefix ? '0' : '\0') + std::to_string(mm);
  }

  int Date::countLeadingZeros() const {
    int absYear = std::abs(yyyy);
    int numberOfLeadingZeros = Date::maxNumberOfLeadingZeros;

    while (absYear >= 10 && numberOfLeadingZeros > 0) {
      absYear /= 10;
      numberOfLeadingZeros--;
    }

    return numberOfLeadingZeros;
  }

  std::string Date::applyZeroPrefixYearWithChristTimeSign() const {
    return (Date::usingZeroPrefix ? std::string(countLeadingZeros(), '0') : "")
      + std::to_string(std::abs(yyyy)) + applyChristTimeSign();
  }

  std::string Date::applyZeroPrefixYearWithNumberSign() const {
    return (yyyy < 0 ? '-' : '\0')
      + (Date::usingZeroPrefix ? std::string(countLeadingZeros(), '0') : "")
      + std::to_string(std::abs(yyyy));
  }

  std::string Date::numericStringify(CR_STR separator) const {
    switch (Date::formatCode) {
      case LITTLE_ENDIAN:
        return applyZeroPrefixDate()
          + separator + applyZeroPrefixMonth()
          + separator + applyZeroPrefixYearWithChristTimeSign();
      case MIDDLE_ENDIAN:
        return applyZeroPrefixMonth()
          + separator + applyZeroPrefixDate()
          + separator + applyZeroPrefixYearWithChristTimeSign();
      case BIG_ENDIAN:
        return applyZeroPrefixYearWithNumberSign()
          + separator + applyZeroPrefixMonth()
          + separator + applyZeroPrefixDate();
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
  // PARSER |
  //________|

  Parser::DATE_COMPLETENESS_CODE Parser::checkDate() {

    /** 1st: The year test */

    int yyyy = Scanner::stringToNumber<int>(com_str_arr[idx[YYYY_K]]);

    // outside of possible recognized years
    if (yyyy < recognizedYearsInterval.min() ||
      yyyy > recognizedYearsInterval.max()
    ) {
      if (implicitYear.active) {
        algorithms::NumberSequence::Digits digits = algorithms::NumberSequence::countDigits<int>(yyyy);

        if (digits.count == implicitYear.numberOfPatternDigits) {
          yyyy = 10 * digits.valsign * implicitYear.affixYear * digits.pow10 + yyyy;
        }
        else return Parser::DATE_INVALID;
      }
      else return Parser::DATE_INVALID;
    }

    /** 2nd: The month test */

    int mm = Scanner::stringToNumber<int>(com_str_arr[idx[MM_J]]);

    // 'mm' may be a word
    if (mm == 0) {
      bool break_i = false;
      StrTool::modifyStringToLowercase(com_str_arr[idx[MM_J]]);

      for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {

          // month name detected
          if (com_str_arr[idx[MM_J]] == Date::getMonthName(i, j)) {
            mm = i + 1;
            break_i = true;
            break;
          }
        }

        if (break_i) break;
      }

      // the test string is empty
      if (!break_i) return Parser::DATE_INVALID;
    }
    // outside of possible numeric month
    else if (mm < 1 || mm > 12) {
      return Parser::DATE_INVALID;
    }

    /** 3rd: The day test */

    int dd = Scanner::stringToNumber<int>(com_str_arr[idx[DD_I]]);
    bool isLeapYYYY = Date::isLeapYear(yyyy);

    // outside of possible month days
    if (dd <= 0 ||
      dd > Date::monthDays[mm - 1][isLeapYYYY]
    ) {
      seqs.temporary = new Sequence(
        Date(randomizeUnknownDD ?
          (std::rand() % Date::monthDays[mm - 1][isLeapYYYY] + 1) : 1,
          mm, yyyy
        ), false
      );

      return Parser::DATE_MM_YYYY;
    }

    // the 'com_str_arr' is a valid date
    Sequence *newFixedSeqs = new Sequence(
      Date(dd, mm, yyyy), true
    );

    // the 'seqs.fixed' is always at the tail
    if (seqs.fixed) seqs.fixed->accept(newFixedSeqs);
    seqs.fixed = newFixedSeqs;

    return Parser::DATE_COMPLETED;
  }

  Parser::WordNode* Parser::spaceSplit(CR_STR text) {
    bool anyWhiteSpace = false;

    // text node initialization
    WordNode *wordNode = new WordNode();

    for (CR_CH ch : text) {
      // whitespace detected, add new node
      if (StrTool::isWhitespace(ch)) {
        if (!anyWhiteSpace) {
          anyWhiteSpace = true;
          wordNode->accept(new WordNode());
          wordNode = static_cast<WordNode*>(wordNode->next());
        }
      }
      else { // not a whitespace
        anyWhiteSpace = false;
        static_cast<WordNode*>(wordNode)->value.push_back(ch);
      }
    }

    /**
     * The last node will have an empty value
     * if the text has a whitespace at the end.
     * It's removed to reduce unnecessary empty string checks.
     */
    if (wordNode->value.empty()) {
      wordNode->destroy();
    }

    // reset to head
    wordNode = static_cast<WordNode*>(wordNode->head());
    return wordNode;
  }

  Parser::WordNode* Parser::distinctSplit(WordNode *wordNode) {

    // indexes of array 'chTypes'
    enum { _current, _previous };

    // codes that represent changes in character type
    enum ch_type { ch_unset, ch_number, ch_letter, ch_other };
    ch_type chTypes[2];

    /**
     * Cannot delete nodes in an iteration,
     * so they are stored here first before being deleted later.
     */
    VEC<DS_LinkedList*> emptyNodes;

    wordNode->forEach(
      DS_LinkedList::RIGHT,
      [&](DS_LinkedList *node)->bool {

        // reset at each node to only compare characters in their values
        chTypes[_current] = ch_unset;
        chTypes[_previous] = ch_unset;

        // store only similar type of characters
        std::string buffer;

        // detect changes in character type in a string
        for (CR_CH ch : static_cast<WordNode*>(node)->value) {

          // alphanumeric conditions
          bool isDigit = StrTool::isDigit(ch);
          bool isLetter = StrTool::isLetter(ch);

          // shift current to previous
          chTypes[_previous] = chTypes[_current];

          // assign current to detected type
          if (isDigit) {
            chTypes[_current] = ch_number;
          }
          else if (isLetter) {
            chTypes[_current] = ch_letter;
          }
          else chTypes[_current] = ch_other;

          // current is not similar with the previous
          if (chTypes[_current] != chTypes[_previous] &&
            chTypes[_previous] != ch_unset &&
            !buffer.empty()
          ) {
            // add new node as previous of node
            WordNode *newNode = new WordNode(buffer);

            // node is the head
            if (node->atFront()) newNode->merge(node);
            // node is after the head
            else node->prev()->accept(newNode);

            buffer = "";
          }

          // collect similar type of 'ch'
          if (isDigit || isLetter) buffer += ch;
        }

        // will be removed
        if (buffer.empty()) {
          emptyNodes.push_back(node);
        }
        else { // keep the remaining alphanumeric
          static_cast<WordNode*>(node)->value = buffer;
        }

        return true;
      }
    );

    // nodes are removed to reduce unnecessary empty string checks
    for (DS_LinkedList *node : emptyNodes) {
      node->destroy();
    }

    // reset to head
    wordNode = static_cast<WordNode*>(wordNode->head());
    return wordNode;
  }

  void Parser::scan(CR_STR text) {

    // use current time as random seed
    if (randomizeUnknownDD) {
      std::srand(std::time(0));
    }

    // container of string array for joined check
    std::string comStrBuffer = "";
    int comCtr = DD_I;

    // directing 'idx' to corresponding date format position
    if (Date::formatCode == Date::LITTLE_ENDIAN) {
      idx[DD_I] = 0;
      idx[MM_J] = 1;
      idx[YYYY_K] = 2;
    }
    else if (Date::formatCode == Date::MIDDLE_ENDIAN) {
      idx[DD_I] = 1;
      idx[MM_J] = 0;
      idx[YYYY_K] = 2;
    }
    else if (Date::formatCode == Date::BIG_ENDIAN) {
      idx[DD_I] = 2;
      idx[MM_J] = 1;
      idx[YYYY_K] = 0;
    }

    // split text to words
    WordNode *wordNode = distinctSplit(spaceSplit(text));

    // the previous only MM and YYYY detected date is approved for inclusion
    std::function<void()> approveMMYYYYSequence = [&]()->void {
      if (seqs.fixed) {
        seqs.fixed->accept(seqs.temporary);
      }
      else seqs.fixed = seqs.temporary;
    };

    wordNode->forEach(
      DS_LinkedList::RIGHT,
      [&](DS_LinkedList *node)->bool {

        // three-phase assignment
        com_str_arr[comCtr] = static_cast<WordNode*>(node)->value;
        comCtr++;

        // after three-phase check
        if (comCtr > YYYY_K) {
          DATE_COMPLETENESS_CODE completenessCode = checkDate();

          // invalid or MM/YYYY
          if (completenessCode != DATE_COMPLETED) {
            if (seqs.temporary) {
              approveMMYYYYSequence();
            }
            else { // shift 'com_str_arr' to the right one step
              com_str_arr[DD_I] = com_str_arr[MM_J];
              com_str_arr[MM_J] = com_str_arr[YYYY_K];
              comCtr = YYYY_K;
              return true;
            }
          }

          // reset temporary sequence and all 'com_str_arr'
          seqs.temporary = nullptr;
          comCtr = DD_I;
        }

        return true;
      }
    );

    /**
     * The 'WordNode' is done. All detected dates are now stored in 'Sequence'.
     */
    wordNode->annihilate();

    /**
     * Include the temporary sequence if the three-phase assignment is not checked.
     */
    if (seqs.temporary) {
      approveMMYYYYSequence();
      seqs.temporary = nullptr;
    }
  }

  void Parser::RecognizedYearsInterval::set(CR_PAIR_INT yyyy_pair) {
    if (yyyy_pair.first > yyyy_pair.second) {
      pair.first = yyyy_pair.second;
      pair.second = yyyy_pair.first;
    }
    else pair = yyyy_pair;
  }

  algorithms::NumberSequence::Digits Parser::RecognizedYearsInterval::minDigits() {
    int minInterval = std::abs(pair.first);

    if (minInterval > std::abs(pair.second)) {
      minInterval = pair.second;
    }
    else minInterval = pair.first;

    return algorithms::NumberSequence::countDigits<int>(minInterval);
  }

  algorithms::NumberSequence::Digits Parser::RecognizedYearsInterval::maxDigits() {
    int maxInterval = std::abs(pair.second);

    if (maxInterval < std::abs(pair.first)) {
      maxInterval = pair.first;
    }
    else maxInterval = pair.second;

    return algorithms::NumberSequence::countDigits<int>(maxInterval);
  }

  VEC<Date> Parser::getAllDates() {
    VEC<Date> dates;

    seqs.fixed->forEach(
      DS_LinkedList::RIGHT,
      [&](DS_LinkedList *node)->bool {
        dates.push_back(static_cast<Sequence*>(node)->date);
        return true;
      }
    );

    return dates;
  }

  VEC<Date> Parser::getCompletedDates() {
    VEC<Date> dates;

    seqs.fixed->forEach(
      DS_LinkedList::RIGHT,
      [&](DS_LinkedList *node)->bool {

        if (static_cast<Sequence*>(node)->completed) {
          dates.push_back(static_cast<Sequence*>(node)->date);
        }

        return true;
      }
    );

    return dates;
  }

  VEC<Date> Parser::getMMYYYYDates() {
    VEC<Date> dates;

    seqs.fixed->forEach(
      DS_LinkedList::RIGHT,
      [&](DS_LinkedList *node)->bool {

        if (!static_cast<Sequence*>(node)->completed) {
          dates.push_back(static_cast<Sequence*>(node)->date);
        }

        return true;
      }
    );

    return dates;
  }

  //________|
  // SPREAD |
  //________|

  // only 1 of the 3 parameters will have a value
  VEC<Date> Spread::everyDateDistribute(
    CR_SZ dd_diff,
    CR_SZ mm_diff,
    CR_SZ yyyy_diff
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

  VEC<Date> Spread::everyDaysDistribute(CR_SZ difference) {
    return everyDateDistribute(difference, 0, 0);
  }

  VEC<Date> Spread::everyMonthsDistribute(CR_SZ difference) {
    return everyDateDistribute(0, difference, 0);
  }

  VEC<Date> Spread::everyYearsDistribute(CR_SZ difference) {
    return everyDateDistribute(0, 0, difference);
  }

  VEC<Date> Spread::fixedNumberDistribute(CR_SZ quantity) {
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

#endif // __MINI_TOOLS__UTILS__TIMER_CPP__