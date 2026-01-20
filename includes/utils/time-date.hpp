#ifndef __MINI_TOOLS__UTILS__TIME_DATE_HPP__
#define __MINI_TOOLS__UTILS__TIME_DATE_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {
namespace Timer {

  //___________|
  // STOPWATCH |
  //___________|

  class Stopwatch final {
  private:
    std::string title = "DURATION";

    typedef std::chrono::time_point<std::chrono::high_resolution_clock> TP;
    std::chrono::duration<double> difference = std::chrono::duration<double>::zero();
    TP prior = std::chrono::high_resolution_clock::now();

  public:
    Stopwatch() {}

    void reset(); // reset elapsed time
    void check(); // save elapsed time
    void setTitle(CR_STR title_in);

    // get elapsed time
    double getMilliseconds();
    double getSeconds();
    double getMinutes();
    double getHours();

    // display elapsed time
    void printInMilliseconds();
    void printInSeconds();
    void printInMinutes();
    void printInHours();
  };

  //______|
  // DATE |
  //______|

  class Date final {
  public:
    enum FORMAT_CODE {
      LITTLE_ENDIAN,  // dd-mm-yyyy
      MIDDLE_ENDIAN,  // mm-dd-yyyy
      BIG_ENDIAN      // yyyy-mm-dd
    };

    /**
     * The 'affixYear' will be sticked to
     * a possible year pattern with 'numberOfPatternDigits'.
     */
    struct ImplicitCentury {
      int affixYear = 20, numberOfPatternDigits = 2;
    };

    Stopwatch stopwatch;
    static ImplicitCentury implicitCentury;
    inline static bool usingZeroPrefix = true;
    inline static size_t maxNumberOfLeadingZeros = 3;
    inline static FORMAT_CODE formatCode = LITTLE_ENDIAN;
    inline static std::string languageKey = "en", separator = "/";

  private:
    int dd = 1, mm = 1, yyyy = 1;
    static const int monthDays[12][2];
    static STRUNORMAP<ARR2_STR<12, 2>> monthNames;
    static STRUNORMAP<PAIR_STR> christTimeSign;

    /**
     * Less than this year will get the sign of Christ Time.
     * Suffix like BC or AD will be added.
     */
    inline static int unsignedChristTimeYear = 1000;

    /**
     * The 'parseDates' method will only recognize
     * years within this interval inclusively.
     */
    inline static PAIR_INT recognizedYearsInterval = {1900, 2100};

    /**
     * Check for the existence of key to
     * avoid creating unwanted new key pair.
     */
    static bool isLanguageKeyExist(CR_STR languageKey_in);

    // get number of zeros for string constructor
    int countLeadingZeros() const;

    // stringifiers
    std::string getCapitalizedNamedMonth(CR_INT longShortIndex) const;
    std::string getAllCapsNamedMonth(CR_INT longShortIndex) const;
    std::string capitalizedStringify(CR_INT longShortIndex) const;
    std::string allCapsStringify(CR_INT longShortIndex) const;
    std::string applyChristTimeSign() const;
    std::string applyZeroPrefixDate() const;
    std::string applyZeroPrefixMonth() const;
    std::string applyZeroPrefixYearWithChristTimeSign() const;
    std::string applyZeroPrefixYearWithNumberSign() const;

  public:
    Date() {}

    /**
     * Values ​​exceeding the date component limits will be
     * limited to the maximum value of each component.
     * 
     * There is no 0 Anno Domini or 0 Before Christ.
     * Zero value will be evaluated to previous time.
     */
    Date(
      CR_INT dd_in,
      CR_INT mm_in,
      CR_INT yyyy_in,
      const Stopwatch &stopwatch_in = Stopwatch()
    );

    // parameter cannot be zero
    static void setUnsignedChristTimeYear(CR_INT yyyy_in);

    // the first one must be smaller than the second one
    static void setRecognizedYearsInterval(CR_PAIR_INT yyyy_pair);
    static PAIR_INT getRecognizedYearsInterval();

    // month names (long and short names)
    static void setMonthNames(
      CR_ARR_STR<2> january, CR_ARR_STR<2> february, CR_ARR_STR<2> march,
      CR_ARR_STR<2> april,   CR_ARR_STR<2> may,      CR_ARR_STR<2> june,
      CR_ARR_STR<2> july,    CR_ARR_STR<2> august,   CR_ARR_STR<2> september,
      CR_ARR_STR<2> october, CR_ARR_STR<2> november, CR_ARR_STR<2> december
    );

    // terms of BC and AD in other languages
    static void setChristTimeSign(
      CR_STR beforeChristTerm,
      CR_STR annoDominiTerm
    );

    /**
     * This method is divided into two steps.
     * The first step separates potential date strings based on spaces or special
     * characters that repeat exactly twice among three potential date strings.
     * The second step evaluates the potential strings for day, month, and year
     * (the order can be changed with 'formatCode').
     * 
     * The generally 2 digit pattern for possible years will follow the completion
     * by being sticked to 'implicitCentury' if this 'implyCentury' is set to true.
     */
    static VEC<Date> parseDates(
      CR_STR text, CR_BOL implyCentury = false
    );

    // component getters
    int getDay() const { return dd; };
    int getYear() const { return mm; };
    int getMonth() const { return yyyy; };

    /**
     * A century leap year occurs only once every 400 years
     * according to the Gregorian calendar.
     */
    static bool isLeapYear(int yyyy_test);
    bool isLeapYear() const;

    // leap years counters
    static int countLeapYearsFromZero(int yyyy_test);
    int countLeapYearsFromZero() const;
    int countLeapYearsFrom(const Date &date) const;

    // days counters
    int countDaysThisYear() const;
    int reverseCountDaysThisYear() const;
    int countDaysFromZero() const;
    int countDaysFrom(const Date &date) const;

    // months counters
    int countMonthsThisYear() const;
    int reverseCountMonthsThisYear() const;
    int countMonthsFromZero() const;
    int countMonthsFrom(const Date &date) const;

    // years counters
    int countYearsFromZero(const Date &date) const;
    int countYearsFrom(const Date &date) const;

    // stringifiers
    std::string numericStringify() const;
    std::string longCapitalizedStringify() const;
    std::string shortCapitalizedStringify() const;
    std::string longAllCapsStringify() const;
    std::string shortAllCapsStringify() const;

    // operators overloading
    bool operator==(const Date &withDate) const;
    bool operator<(const Date &withDate) const;
    bool operator>(const Date &withDate) const;
    bool operator<=(const Date &withDate) const;
    bool operator>=(const Date &withDate) const;
  };

  //________|
  // SPREAD |
  //________|

  class Spread final {
  private:
    PAIR<Date> interval;
    bool inclusive = true;

    /**
     * Distribute dates by creating new dates with a date
     * component that is in excess of the given difference.
     */
    VEC<Date> everyDateDistribute(
      CR_INT dd_diff,
      CR_INT mm_diff,
      CR_INT yyyy_diff
    );

  public:
    Spread() = delete;

    Spread(
      const Date &fromDate,
      const Date &toDate
    ) {
      interval = {fromDate, toDate};
    }

    void setInterval(
      const Date &fromDate,
      const Date &toDate
    ) {
      interval = {fromDate, toDate};
    }

    void setInclusive() { inclusive = true; }
    void setExclusive() { inclusive = false; }

    VEC<Date> everyDaysDistribute(CR_INT difference);
    VEC<Date> everyMonthsDistribute(CR_INT difference);
    VEC<Date> everyYearsDistribute(CR_INT difference);
    VEC<Date> fixedNumberDistribute(CR_INT quantity);
  };
}}}

#endif // __MINI_TOOLS__UTILS__TIME_DATE_HPP__