set (SOURCES
  algorithms/number-sequence.cpp
  data-structures/linked-list.cpp
  data-structures/tree.cpp
  utils/random-words.cpp
  utils/scanner.cpp
  utils/str-tools.cpp
  utils/time-date.cpp
)

add_library(mini-tools STATIC ${SOURCES})
