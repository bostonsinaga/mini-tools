cmake_minimum_required(VERSION 3.10)
project(sorters)

set (SOURCES
  #headers
  bubble-sort.h
  comb-sort.h
  insertion-sort.h
  merge-sort.h
  quick-sort.h
  selection-sort.h
  sorters.h

  #sources
  bubble-sort.cpp
  comb-sort.cpp
  insertion-sort.cpp
  merge-sort.cpp
  quick-sort.cpp
  selection-sort.cpp
)

add_library(sorters STATIC ${SOURCES})
target_include_directories(sorters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
