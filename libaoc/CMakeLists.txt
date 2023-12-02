cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME current_day)

add_library(${current_day})  # WIN32)
# for VS, set the startup target (the one that starts in debugger by default)
# set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${current_day})

# add_custom_command(TARGET ${current_day} POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/input.txt $<TARGET_FILE_DIR:${current_day}>
# )

add_subdirectory(include)
add_subdirectory(src)
