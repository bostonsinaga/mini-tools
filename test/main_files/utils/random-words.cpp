#include "helper.hpp"

int main(int argc, char *argv[]) {
  mt::ARR_INT<4> params;

  // expected to be paired with integers
  const mt::ARR_STR<4> keywords = {
    "-amount",
    "-max-number",
    "-word-length-start",
    "-word-length-end"
  };

  //_____________________________|
  // TESTS INPUTS INITIALIZATION |
  //_____________________________|
  if (helper::parsePairCLI<int, 4>(
    argc, argv, "--init-inputs", keywords, params
  )) {
    /** Generate Random Data */

    enum {
      amount_e, max_number_e,
      word_length_start_e, word_length_end_e
    };

    const mt::VEC<int> integers = mt_uti::RandomWords::generateIntegrals<int>(
      params[amount_e], params[max_number_e], 0
    );

    const mt::VEC<float> reals = mt_uti::RandomWords::generateFloatingPoints<float>(
      params[amount_e], params[max_number_e], 0
    );

    const mt::VEC_STR letters = mt_uti::RandomWords::generateStrings(
      params[amount_e],
      {params[word_length_start_e], params[word_length_end_e]},
      true, false
    );

    const mt::VEC_STR words = mt_uti::RandomWords::generateStrings(
      params[amount_e],
      {params[word_length_start_e], params[word_length_end_e]},
      false, true
    );

    /** Write To Files */

    const mt::FS_PATH samplesPath = mt_uti::Scanner::findDirectory(
      "test/samples", true
    );

    mt_uti::Printer::write<int>(
      integers, samplesPath / "integers.txt", false
    );

    mt_uti::Printer::write<float>(
      reals, samplesPath / "reals.txt", false
    );

    mt_uti::Printer::write<std::string>(
      letters, samplesPath / "letters.txt", false
    );

    mt_uti::Printer::write<std::string>(
      words, samplesPath / "words.txt", false
    );
  }
  //______________|
  // REGULAR TEST |
  //______________|
  else {

  }

  return 0;
}

