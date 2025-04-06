cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(mini-tools)
add_subdirectory(src)
add_subdirectory(test)

target_include_directories(mini-tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_include_directories(mini-tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
