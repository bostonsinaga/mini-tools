#ifndef __TEST__HELPER_TPP__
#define __TEST__HELPER_TPP__

template <typename T, typename U, typename V>
requires mt_uti::CLIUniqueType<T, U, V>
void Helper::CLIWrapper::printKeywords(
  std::string &entry,
  std::string &description,
  mt_uti::CLIParser<T, U, V> &parser
) {
  std::cout << std::endl;
  CLIWrapper::printHeader(entry, description);

  for (mt::CR_STR keyword : parser.template extractStringsFromMainUnormap<T>()) {
    std::cout << "\n  " << keyword << " <"
      << mt_uti::CLIParser<T, U, V>::template getStringifiedType<T>() << '>';
  }

  for (mt::CR_STR keyword : parser.template extractStringsFromMainUnormap<U>()) {
    std::cout << "\n  " << keyword << " <"
      << mt_uti::CLIParser<T, U, V>::template getStringifiedType<U>() << '>';
  }

  for (mt::CR_STR keyword : parser.template extractStringsFromMainUnormap<V>()) {
    std::cout << "\n  " << keyword << " <"
      << mt_uti::CLIParser<T, U, V>::template getStringifiedType<V>() << '>';
  }

  std::cout << std::endl;
}

template <typename T, typename U, typename V>
requires mt_uti::CLIUniqueType<T, U, V>
void Helper::CLIWrapper::run(
  std::string entry,
  std::string description,
  mt_uti::CLIParser<T, U, V> &parser,
  bool (*callback)(mt_uti::CLIParser<T, U, V>&)
) {
  /**
    * Skip this run.
    * An entry was detected in the previous runs
    * or the number of runs has exceeded the limit.
    */
  if (CLIWrapper::entryDetected || CLIWrapper::maxRunsReached) return;

  /** Assign default strings */

  if (entry.empty()) {
    entry = CLIWrapper::generateDefaultEntry();
  }

  if (description.empty()) {
    description = CLIWrapper::defaultDescription;
  }

  /**
    * Displaying main menu.
    * Main menu was already detected in previous runs.
    */
  if (CLIWrapper::mainMenuDetected) {
    CLIWrapper::printAbout(entry, description);
    return;
  }

  /** Entry Detection */

  bool callbackCompleted = false;

  // main menu
  if (parser.query({"-h"}) ||
    parser.query({"--help"})
  ) {
    CLIWrapper::mainMenuDetected = true;
    CLIWrapper::printAbout(entry, description);
    return;
  }
  // individual description
  else if (
    parser.enter({entry, "-h"}) ||
    parser.enter({entry, "--help"})
  ) {
    CLIWrapper::entryDetected = true;
    CLIWrapper::printKeywords<T, U, V>(entry, description, parser);
    return;
  }
  // invoke callback
  else if (parser.query({entry})) {
    CLIWrapper::entryDetected = true;

    if (callback && callback(parser)) {
      callbackCompleted = true;
    }
  }

  // display final message
  CLIWrapper::displayFinalMessage(callbackCompleted);
}

#endif // __TEST__HELPER_TPP__