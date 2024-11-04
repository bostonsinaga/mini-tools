set (SOURCES
  algorithms/calculators.cpp
  algorithms/geometrics/point.cpp
  algorithms/geometrics/polygon.cpp
  algorithms/geometrics/ray-casting.cpp
  algorithms/geometrics/rect.cpp
  utils/reader.cpp
  utils/str-tools.cpp
  utils/timer.cpp
  data-structures/tree.cpp
)

add_library(mini-tools STATIC ${SOURCES})
