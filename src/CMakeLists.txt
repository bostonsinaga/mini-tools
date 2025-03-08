set (SOURCES
  utils/calculators.cpp
  utils/reader.cpp
  utils/timer.cpp
  data-structures/str-tools.cpp
  data-structures/linked-list.cpp
  data-structures/tree.cpp
)

add_library(mini-tools STATIC ${SOURCES})
