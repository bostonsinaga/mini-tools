set (SOURCES
  utils/scanner.cpp
  utils/timer.cpp
  data-structures/str-tools.cpp
  data-structures/linked-list.cpp
  data-structures/tree.cpp
  algorithms/calculators.cpp
)

add_library(mini-tools STATIC ${SOURCES})
