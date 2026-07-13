#ifndef __MINI_TOOLS__UTILS__TIMER_HPP__
#define __MINI_TOOLS__UTILS__TIMER_HPP__

#include "types.hpp"
#include "data-structures/linked-list.hpp"

namespace mini_tools {
namespace utils {
namespace Timer {

  //___________|
  // STOPWATCH |
  //___________|

  class Stopwatch {
  private:
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> TP;
    std::chrono::duration<double> difference = std::chrono::duration<double>::zero();
    TP prior = std::chrono::high_resolution_clock::now();

  public:
    Stopwatch() {}

    void reset(); // reset elapsed time
    void check(); // save elapsed time

    // get elapsed time
    double getMilliseconds();
    double getSeconds();
    double getMinutes();
    double getHours();

    // get elapsed time in string
    std::string getMillisecondsString(CR_STR timeUnit = "ms");
    std::string getSecondsString(CR_STR timeUnit = "s");
    std::string getMinutesString(CR_STR timeUnit = "m");
    std::string getHoursString(CR_STR timeUnit = "h");
  };

  //______|
  // DATE |
  //______|

  class Date {
  public:
    static const int monthDays[12][2];

    enum FORMAT_CODE {
      LITTLE_ENDIAN,  // dd-mm-yyyy
      MIDDLE_ENDIAN,  // mm-dd-yyyy
      BIG_ENDIAN      // yyyy-mm-dd
    };

    Stopwatch stopwatch;
    inline static bool usingZeroPrefix = true;
    inline static size_t maxNumberOfLeadingZeros = 3;
    inline static FORMAT_CODE formatCode = LITTLE_ENDIAN;
    inline static std::string languageKey = "en";

  private:
    int dd = 1, mm = 1, yyyy = 1;
    static UNORMAP_STR<ARR2_STR<12, 2>> monthNames;
    static UNORMAP_STR<PAIR_STR> christTimeSign;

    /**
     * Less than this year will get the sign of Christ Time.
     * Suffix like BC or AD will be added.
     */
    inline static int unsignedChristTimeYear = 1000;

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

    /** Month Names (Long and Short Names) */

    static void setMonthNames(
      CR_ARR_STR<2> january, CR_ARR_STR<2> february, CR_ARR_STR<2> march,
      CR_ARR_STR<2> april,   CR_ARR_STR<2> may,      CR_ARR_STR<2> june,
      CR_ARR_STR<2> july,    CR_ARR_STR<2> august,   CR_ARR_STR<2> september,
      CR_ARR_STR<2> october, CR_ARR_STR<2> november, CR_ARR_STR<2> december
    );

    static std::string getMonthName(
      CR_INT index, CR_BOL isShortened
    );

    struct NamedMonthLengths {
      int longArray[12], shortArray[12];
    };

    static NamedMonthLengths createNamedMonthLengths();

    // terms of BC and AD in other languages
    static void setChristTimeSign(
      CR_STR beforeChristTerm,
      CR_STR annoDominiTerm
    );

    // component getters
    int getDay() const { return dd; };
    int getMonth() const { return mm; };
    int getYear() const { return yyyy; };

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
    std::string numericStringify(CR_STR separator = "/") const;
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
  // PARSER |
  //________|

  class Parser {
  private:
    // indexes that following the 'Date::formatCode'
    enum {DD_I, MM_J, YYYY_K};
    int idx[3];

    // 3 test strings
    std::string com_str_arr[3];

    /**
     * The 'affixYear' will be sticked to
     * a possible year pattern with 'numberOfPatternDigits'.
     */
    class ImplicitYear final {
    public: 
      int affixYear = 20;
      int numberOfPatternDigits = 2;
      bool active = true;
    };

    /**
     * The 'checkDate' will only recognize
     * years within this interval inclusively.
     */
    class RecognizedYearsInterval final {
    private:
      PAIR_INT pair = {1900, 2100};

    public:
      void set(CR_PAIR_INT yyyy_pair);
      PAIR_INT get() { return pair; }
      int min() { return pair.first; }
      int max() { return pair.second; }

      // get the number of digits of the interval
      algorithms::NumberSequence::Digits minDigits();
      algorithms::NumberSequence::Digits maxDigits();
    };

    class WordNode final : public data_structures::LinkedList {
    public:
      std::string value;
      WordNode(CR_STR value_in = "") : value(value_in) {}
    };

    class Sequence final : public data_structures::LinkedList {
    public:
      Date date;
      bool completed = false;
      Sequence(const Date &date_in, CR_BOL completed_in)
      : date(date_in), completed(completed_in) {}
    };

    struct Seqs {
      Sequence *fixed = nullptr, *temporary = nullptr;
    } seqs;

    // codes for 'checkDate' status
    enum DATE_COMPLETENESS_CODE {
      DATE_INVALID,
      DATE_MM_YYYY,
      DATE_COMPLETED
    };

    // test the possible 3 string components
    DATE_COMPLETENESS_CODE checkDate();

    // split text into words with separate character types
    WordNode* spaceSplit(CR_STR text);
    WordNode* distinctSplit(WordNode *wordNode);

  public:
    ImplicitYear implicitYear;
    RecognizedYearsInterval recognizedYearsInterval;
    bool randomizeUnknownDD = false;

    // constructor & destructor
    Parser() {}
    ~Parser() {
      if (seqs.fixed) seqs.fixed->annihilate();
    }

    /**
     * Find the dates in the text by checking every 3 words.
     * The generally 2 digit pattern for a possible year will follow
     * the completion by being sticked to 'implicitYear.affixYear' if it active.
     */
    void scan(CR_STR text);

    // extract dates from 'Sequence'
    VEC<Date> getAllDates();
    VEC<Date> getCompletedDates();
    VEC<Date> getMMYYYYDates();
    bool hasDate() { return seqs.fixed; }
  };

  //________|
  // SPREAD |
  //________|

  class Spread {
  private:
    PAIR<Date> interval;
    bool inclusive = true;

    /**
     * Distribute dates by creating new dates with a date
     * component that is in excess of the given difference.
     */
    VEC<Date> everyDateDistribute(
      CR_SZ dd_diff,
      CR_SZ mm_diff,
      CR_SZ yyyy_diff
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

    VEC<Date> everyDaysDistribute(CR_SZ difference);
    VEC<Date> everyMonthsDistribute(CR_SZ difference);
    VEC<Date> everyYearsDistribute(CR_SZ difference);
    VEC<Date> fixedNumberDistribute(CR_SZ quantity);
  };
}}}

#endif // __MINI_TOOLS__UTILS__TIMER_HPP__