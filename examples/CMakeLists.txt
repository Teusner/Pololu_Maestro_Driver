# Example
add_executable(main main.cpp)
target_link_libraries(main PRIVATE pololu_maestro_driver)
target_include_directories(main PUBLIC ${POLOLU_MAESTRO_DRIVER_HEADERS})