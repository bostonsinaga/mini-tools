set (SOURCES
  algorithms/calculators.cpp
  data-structures/linked-list.cpp
  data-structures/tree.cpp
  utils/reader.cpp
  utils/str-tools.cpp
  utils/timer.cpp
)

add_library(mini-tools STATIC ${SOURCES})
