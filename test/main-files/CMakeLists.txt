function(register_test target_filename_list)
  foreach(array IN LISTS ${target_filename_list})

    string(REGEX MATCH "^[^@]+" target ${array})
    string(REGEX MATCH "@(.+)" filename ${array})
    string(REGEX REPLACE "^@" "" filename ${filename})

    project(${target})
    add_executable(${target} ${filename})

    target_link_libraries(${target} mini-tools)
    target_include_directories(${target} PUBLIC ${main_files_dir})
  endforeach()
endfunction()

# add_subdirectory(algorithms)
add_subdirectory(data-structures)
# add_subdirectory(utils)
