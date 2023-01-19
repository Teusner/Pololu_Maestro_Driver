# List of exaples
list(APPEND test_files
    position.cpp
    multiple_positions.cpp
    velocity.cpp
)

# Compile each example
foreach(filename ${test_files})
    get_filename_component(target_name ${filename} NAME_WE)
    add_executable(${target_name} ${filename})
    target_link_libraries(${target_name} PRIVATE pololu_maestro_driver)
    target_include_directories(${target_name} PUBLIC ${POLOLU_MAESTRO_DRIVER_HEADERS})
endforeach()
