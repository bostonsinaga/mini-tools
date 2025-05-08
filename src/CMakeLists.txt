set (SOURCES
  algorithms/number_sequence.cpp
  data_structures/linked_list.cpp
  data_structures/general_tree.cpp
  utils/cli-parser.cpp
  utils/random_words.cpp
  utils/scanner.cpp
  utils/str_tools.cpp
  utils/time_date.cpp
)

add_library(mini_tools STATIC ${SOURCES})
