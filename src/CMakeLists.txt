set (SOURCES
  algorithms/calculators.cpp
  data-structures/linked-list.cpp
  data-structures/tree.cpp
  utils/scanner.cpp
  utils/str-tools.cpp
  utils/time-date.cpp
)

add_library(mini-tools STATIC ${SOURCES})
