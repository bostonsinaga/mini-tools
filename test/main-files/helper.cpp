#ifndef __TEST__HELPER_CPP__
#define __TEST__HELPER_CPP__

#include "helper.hpp"

const std::string Helper::EscapeStyle::availables[Helper::EscapeStyle::numberOfAvailables] = {
  "\x1b[0m", // normal
  "\x1b[3m", // italic
  "\x1b[4m", // underline
  "\x1b[38;2;255;0;0m", // red
  "\x1b[38;2;0;255;0m", // green
  "\x1b[38;2;0;0;255m", // blue
  "\x1b[38;2;255;255;0m", // yellow
  "\x1b[38;2;255;0;255m", // magenta
  "\x1b[38;2;0;127;255m", // azure
  "\x1b[38;2;255;127;0m" // orange
};

Helper::EscapeStyle::EscapeStyle() {
  used = availables[NORMAL_ESCAPE_STYLE];
}

Helper::EscapeStyle::EscapeStyle(const ESCAPE_STYLE_CODE& code) {
  if (code >= NORMAL_ESCAPE_STYLE &&
    code <= ORANGE_COLOR_ESCAPE_STYLE
  ) {
    used = availables[code];
  }
  else used = availables[NORMAL_ESCAPE_STYLE];
}

Helper::EscapeStyle Helper::titleEscapeStyle = Helper::EscapeStyle(
  Helper::MAGENTA_COLOR_ESCAPE_STYLE
);

std::string Helper::EscapeStyle::generate(mt::CR_STR text, mt::CR_BOL needTrim) const {
  if (needTrim && !text.empty()) {

    // find whitespace boundary indexes
    mt::PAIR<int> spaceBoundaryIndexes = mt_uti::StrTool::findSpaceBoundaryIndexes(text);

    // trimmed string from whitespaces with ANSI escape code
    return text.substr(0, spaceBoundaryIndexes.first)
      + used + text.substr(
        spaceBoundaryIndexes.first,
        spaceBoundaryIndexes.second + 1
      ) + availables[NORMAL_ESCAPE_STYLE]
      + text.substr(spaceBoundaryIndexes.second + 1);
  }

  // no need to trim
  return used + text + availables[NORMAL_ESCAPE_STYLE];
}

void Helper::getSamples(
  const std::function<TUP4PTR(mt::VEC_INT&, mt::VEC_DBL&, mt::VEC_STR&, mt::VEC_STR&)> &callback,
  mt::CR_STR timerTitle,
  mt::CR_STR logFilePath
) {
  mt_uti::Timer::Stopwatch stopwatch;
  mt::FS_PATH testPath = mt_uti::FileTool::findDirectory("test", true);

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
  stopwatch.check();
  std::cout << timerTitle << ": " << stopwatch.getMillisecondsString() << std::endl;
}

void Helper::CLIWrapper::displayFinalMessage(bool &callbackCompleted) {
  static int currentRunNumber = 1;

  if (CLIWrapper::displayingFinalMessage) {
    // completed message
    if (callbackCompleted) {
      std::cout << EscapeStyle(GREEN_COLOR_ESCAPE_STYLE).generate(
        '\n' + CLIWrapper::finalMessageBorderStyle
        + CLIWrapper::completedMessage
        + CLIWrapper::finalMessageBorderStyle + '\n'
      );
    }
    // failed message
    else if (CLIWrapper::entryDetected) {
      std::cout << EscapeStyle(RED_COLOR_ESCAPE_STYLE).generate(
        '\n' + CLIWrapper::finalMessageBorderStyle
        + CLIWrapper::failedMessage
        + CLIWrapper::finalMessageBorderStyle + '\n'
      );
    }
    // invalid message
    else if (CLIWrapper::numberOfRuns == currentRunNumber) {
      CLIWrapper::maxRunsReached = true;

      std::cout << EscapeStyle(YELLOW_COLOR_ESCAPE_STYLE).generate(
        '\n' + CLIWrapper::finalMessageBorderStyle
        + CLIWrapper::invalidMessage
        + CLIWrapper::finalMessageBorderStyle + '\n'
      );
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
  std::cout << EscapeStyle(AZURE_COLOR_ESCAPE_STYLE).generate(entry + ":\n")
    << EscapeStyle(ITALIC_ESCAPE_STYLE).generate(description);
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