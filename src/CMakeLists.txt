set (SOURCES
  algorithms/number-sequence.cpp
  data-structures/general-tree.cpp
  data-structures/linked-list.cpp
  utils/file-tool.cpp
  utils/printer.cpp
  utils/random-words.cpp
  utils/scanner.cpp
  utils/str-tool.cpp
  utils/timer.cpp
  utils/booleanizer.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
