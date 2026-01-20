add_library(test-helper STATIC ${CMAKE_CURRENT_SOURCE_DIR}/helper.cpp)
target_link_libraries(test-helper PRIVATE mini-tools)

function(register_test target_filename_list)
  foreach(array IN LISTS ${target_filename_list})

    string(REGEX MATCH "^[^@]+" target ${array})
    string(REGEX MATCH "@(.+)" filename ${array})
    string(REGEX REPLACE "^@" "" filename ${filename})

    project(${target})
    add_executable(${target} ${filename})

    target_link_libraries(${target} mini-tools test-helper)
    target_include_directories(${target} PUBLIC ${main_files_dir})
  endforeach()
endfunction()

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/algorithms)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/data-structures)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)

set(status-printer status-printer@status-printer.cpp)
register_test(status-printer)
