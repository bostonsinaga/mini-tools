cmake_minimum_required(VERSION 3.10)
project(test)

add_subdirectory(includes)
add_subdirectory(test)

target_include_directories(mini-tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_include_directories(mini-tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
