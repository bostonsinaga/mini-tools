set (SOURCES
  algorithms/number-sequence.cpp
  data-structures/general-tree.cpp
  data-structures/linked-list.cpp
  utils/random-words.cpp
  utils/scanner.cpp
  utils/str-tools.cpp
  utils/time-date.cpp
)

add_library(mini-tools STATIC ${SOURCES})
