#ifndef __TEST__HELPER_CPP__
#define __TEST__HELPER_CPP__

#include "helper.hpp"

void Helper::getSamples(
  const std::function<TUP4PTR(mt::VEC_INT&, mt::VEC_DBL&, mt::VEC_STR&, mt::VEC_STR&)> &callback,
  mt::CR_STR timerTitle,
  mt::CR_STR logFilePath
) {
  mt::FS_PATH testPath = mt_uti::Scanner::findDirectory("test", true);

  mt::VEC_INT integers = mt_uti::Scanner::txtToNumbers<int>(
    testPath / "samples/integers.txt"
  );

  mt::VEC_DBL reals = mt_uti::Scanner::txtToNumbers<double>(
    testPath / "samples/reals.txt"
  );

  mt::VEC_STR letters = mt_uti::Scanner::txtToLetters<std::string>(
    testPath / "samples/letters.txt"
  );

  mt::VEC_STR words = mt_uti::Scanner::txtToLetters<std::string>(
    testPath / "samples/words.txt"
  );

  TUP4PTR toPrint = callback(
    integers, reals, letters, words
  );

  const mt::FS_PATH
    completeLogFilePath = testPath / "logs" / logFilePath;

  // integers
  if (std::get<0>(toPrint)) {
    mt_uti::Printer::logf<int>(
      *std::get<0>(toPrint), completeLogFilePath, false
    );
  }

  // reals
  if (std::get<1>(toPrint)) {
    mt_uti::Printer::logf<double>(
      *std::get<1>(toPrint), completeLogFilePath, false
    );
  }

  // letters
  if (std::get<2>(toPrint)) {
    mt_uti::Printer::logf<std::string>(
      *std::get<2>(toPrint), completeLogFilePath, false
    );
  }

  // words
  if (std::get<3>(toPrint)) {
    mt_uti::Printer::logf<std::string>(
      *std::get<3>(toPrint), completeLogFilePath, false
    );
  }

  // display elapsed time
  mt_uti::Timer::Stopwatch::print(false, timerTitle + ":");
}

void Helper::CLIWrapper::displayFinalMessage(bool &callbackCompleted) {
  static int currentRunNumber = 1;

  if (CLIWrapper::displayingFinalMessage) {
    if (callbackCompleted) {
      std::cout << Helper::CLIWrapper::greenFontColor
        << CLIWrapper::finalMessageBorderStyle << CLIWrapper::completedMessage
        << CLIWrapper::finalMessageBorderStyle << "\x1b[0m\n";
    }
    else if (CLIWrapper::entryDetected) {
      std::cout << Helper::CLIWrapper::redFontColor
        << CLIWrapper::finalMessageBorderStyle << CLIWrapper::failedMessage
        << CLIWrapper::finalMessageBorderStyle << "\x1b[0m\n";
    }
    else if (CLIWrapper::numberOfRuns == currentRunNumber) {
      CLIWrapper::maxRunsReached = true;

      std::cout << Helper::CLIWrapper::yellowFontColor
        << CLIWrapper::finalMessageBorderStyle << CLIWrapper::invalidMessage
        << CLIWrapper::finalMessageBorderStyle << "\x1b[0m\n";
    }
  }

  currentRunNumber++;
}

std::string Helper::CLIWrapper::generateDefaultEntry() {
  lastDefaultEntry.second++;

  // limit counter
  if (lastDefaultEntry.second > 26) {
    lastDefaultEntry.second = 1;
    lastDefaultEntry.first.push_back('a');
  }
  else lastDefaultEntry.first.back()++;

  // combine characters
  std::string generatedEntry;

  for (char &ch : lastDefaultEntry.first) {
    generatedEntry += ch;
  }

  // combine letters with number
  return generatedEntry + std::to_string(lastDefaultEntry.second);
}

void Helper::CLIWrapper::printHeader(
  std::string &entry,
  std::string &description
) {
  std::cout << Helper::CLIWrapper::azureFontColor << entry
    << ":\x1b[0m\n" << italicFont << description << "\x1b[0m";
}

void Helper::CLIWrapper::printAbout(
  std::string &entry,
  std::string &description
) {
  std::cout << std::endl;
  CLIWrapper::printHeader(entry, description);
  std::cout << std::endl;
}

void Helper::CLIWrapper::setFinalMessageBorderStyle(mt::CR_STR style) {
  CLIWrapper::finalMessageBorderStyle = style;
}

void Helper::CLIWrapper::setCompletedMessage(mt::CR_STR message) {
  if (!message.empty()) {
    CLIWrapper::completedMessage = message;
  }
}

void Helper::CLIWrapper::setFailedMessage(mt::CR_STR message) {
  if (!message.empty()) {
    CLIWrapper::failedMessage = message;
  }
}

void Helper::CLIWrapper::setInvalidMessage(mt::CR_STR message) {
  if (!message.empty()) {
    CLIWrapper::invalidMessage = message;
  }
}

void Helper::CLIWrapper::setDefaultDescription(mt::CR_STR description) {
  if (!description.empty()) {
    CLIWrapper::defaultDescription = description;
  }
}

void Helper::CLIWrapper::hideFinalMessage() {
  CLIWrapper::displayingFinalMessage = false;
}

void Helper::CLIWrapper::setNumberOfRuns(mt::CR_INT count) {
  CLIWrapper::numberOfRuns = count;
}

#endif // __TEST__HELPER_CPP__