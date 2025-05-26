set (SOURCES
  utils/random-words.cpp
  utils/scanner.cpp
  utils/str-tools.cpp
  utils/time-date.cpp
  utils/cli-parser.cpp
  algorithms/number-sequence.cpp
  data-structures/linked-list.cpp
  data-structures/general-tree.cpp
)

add_library(mini-tools STATIC ${SOURCES})
