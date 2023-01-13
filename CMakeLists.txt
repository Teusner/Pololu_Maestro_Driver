cmake_minimum_required(VERSION 3.1)
project(Sparton_AHRS_M1_Driver VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# rtac_asio
include(FetchContent) # once in the project to include the module

FetchContent_Declare(rtac_asio GIT_REPOSITORY https://github.com/pnarvor/rtac_asio.git GIT_TAG master)
FetchContent_MakeAvailable(rtac_asio)

# Driver Include dir
set(POLOLU_MAESTRO_DRIVER_HEADERS include)

# Driver
add_library(pololu_maestro_driver src/pololu_maestro_driver.cpp)
target_include_directories(pololu_maestro_driver PUBLIC ${POLOLU_MAESTRO_DRIVER_HEADERS})
target_link_libraries(pololu_maestro_driver PUBLIC rtac_asio)

# Detecting if project is included into another
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(MY_PROJECT_BUILD_EXAMPLES   "whether or not examples should be built" ON)

    if(MY_PROJECT_BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()
endif()