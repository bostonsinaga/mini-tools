project(mini-tools)

set (SOURCES
  # HEADERS
  mini-tools.h

  # SOURCES
  algorithms/geometrics/point.cpp
  algorithms/geometrics/polygon.cpp
  algorithms/geometrics/ray-casting.cpp
  algorithms/geometrics/rect.cpp
)

add_library(mini-tools STATIC ${SOURCES})
