#include "helper.hpp"

typedef std::tuple<mt::VEC_INT, mt::VEC_FLT, mt::VEC_STR, mt::VEC_STR> FourVectorTypes;

FourVectorTypes generateRandomValues(mt_uti::CLIParser<mt::LD> *cli) {

  /** Initialization */

  size_t amount = 0,
    maxNumber = 0,
    wordLengthStart = 0,
    wordLengthEnd = 0;

  if (cli->getSizeAt<mt::LD>("-amount")) {
    amount = cli->getVectorAt<mt::LD>("-amount").back();
  }

  if (cli->getSizeAt<mt::LD>("-max-number")) {
    maxNumber = cli->getVectorAt<mt::LD>("-max-number").back();
  }

  if (cli->getSizeAt<mt::LD>("-word-length-start")) {
    wordLengthStart = cli->getVectorAt<mt::LD>("-word-length-start").back();
  }

  if (cli->getSizeAt<mt::LD>("-word-length-end")) {
    wordLengthEnd = cli->getVectorAt<mt::LD>("-word-length-end").back();
  }

  /** Limiting sizes */

  bool needAdditionalNewline = false;

  if (amount > 100) {
    amount = 100;
    needAdditionalNewline = true;
    std::cout << "\nExcessive '-amount'. Limited to 100.";
  }

  if (wordLengthStart > 10) {
    wordLengthStart = 10;
    needAdditionalNewline = true;
    std::cout << "\nExcessive '-word-length-start'. Limited to 10.";
  }

  if (wordLengthEnd > 10) {
    wordLengthEnd = 10;
    needAdditionalNewline = true;
    std::cout << "\nExcessive '-word-length-end'. Limited to 10.";
  }

  if (needAdditionalNewline) std::cout << std::endl;

  /** Random value generators */

  return std::make_tuple(
    mt_uti::RandomWords::generateIntegrals<int>(
      amount, maxNumber, 0
    ),
    mt_uti::RandomWords::generateFloatingPoints<float>(
      amount, maxNumber, 0
    ),
    mt_uti::RandomWords::generateStrings(
      amount,
      {wordLengthStart, wordLengthEnd},
      true, false
    ),
    mt_uti::RandomWords::generateStrings(
      amount,
      {wordLengthStart, wordLengthEnd},
      false, false
    )
  );
}

// on 'cli->enter("--test")'
bool testFun(mt_uti::CLIParser<mt::LD> *cli) {

  FourVectorTypes randomValues = generateRandomValues(cli);

  /** Display random values */

  std::cout << "\nIntegers:\n";
  for (mt::CR_INT val : std::get<0>(randomValues)) {
    std::cout << val << ", ";
  }
  std::cout << std::endl;

  std::cout << "\nReals:\n";
  for (mt::CR_FLT val : std::get<1>(randomValues)) {
    std::cout << val << ", ";
  }
  std::cout << std::endl;

  std::cout << "\nLetters:\n";
  for (mt::CR_STR val : std::get<2>(randomValues)) {
    std::cout << val << ", ";
  }
  std::cout << std::endl;

  std::cout << "\nWords:\n";
  for (mt::CR_STR val : std::get<3>(randomValues)) {
    std::cout << val << ", ";
  }
  std::cout << std::endl;

  return true;
}

// on 'cli->enter("--init-inputs")'
bool initInputsFun(mt_uti::CLIParser<mt::LD> *cli) {

  FourVectorTypes randomValues = generateRandomValues(cli);

  /** Write random values to files */

  const mt::FS_PATH samplesPath = mt_uti::Scanner::findDirectory(
    "test/samples", true
  );

  mt_uti::Printer::write<int>(
    std::get<0>(randomValues), samplesPath / "integers.txt", false
  );

  mt_uti::Printer::write<float>(
    std::get<1>(randomValues), samplesPath / "reals.txt", false
  );

  mt_uti::Printer::write<std::string>(
    std::get<2>(randomValues), samplesPath / "letters.txt", false
  );

  mt_uti::Printer::write<std::string>(
    std::get<3>(randomValues), samplesPath / "words.txt", false
  );

  return true;
}

int main(int argc, char *argv[]) {

  /** Help and Error Messages */

  helper::CLIMessage helperTest(
    "--test",
    "Generate random values and display them on command line.",
    "-amount<NUMBER> -max-number<NUMBER> -word-length-start<NUMBER> -word-length-end<NUMBER>"
  );

  helper::CLIMessage helperInitInputs(
    "--init-inputs",
    "Generate random values and write them to files at 'test/samples' directory.",
    "-amount<NUMBER> -max-number<NUMBER> -word-length-start<NUMBER> -word-length-end<NUMBER>"
  );

  /** CLI Registrations */

  mt_uti::CLIParser<mt::LD> cliTest(
    mt_uti::CLIParser<mt::LD>::argvToStringVector(argc, argv),
    {
      std::make_pair("-amount", 0),
      std::make_pair("-max-number", 0),
      std::make_pair("-word-length-start", 0),
      std::make_pair("-word-length-end", 0)
    }
  );

  mt_uti::CLIParser<mt::LD> cliInitInputs(
    mt_uti::CLIParser<mt::LD>::argvToStringVector(argc, argv),
    {
      std::make_pair("-amount", 0),
      std::make_pair("-max-number", 0),
      std::make_pair("-word-length-start", 0),
      std::make_pair("-word-length-end", 0)
    }
  );

  // process CLI input
  helper::CLIWrapper<mt::LD>(
    {&helperTest, &helperInitInputs},
    {&cliTest, &cliInitInputs},
    {testFun, initInputsFun}
  );

  return 0;
}

