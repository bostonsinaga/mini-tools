set (SOURCES
  algorithms/number-sequence.cpp
  data-structures/general-tree.cpp
  data-structures/linked-list.cpp
  utils/printer.cpp
  utils/random-words.cpp
  utils/scanner.cpp
  utils/str-tools.cpp
  utils/time-date.cpp
  utils/booleanizer.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
