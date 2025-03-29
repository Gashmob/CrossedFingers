cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION LIB_VERSION)

project(
        crossed_fingers
        VERSION ${LIB_VERSION}
        LANGUAGES CXX
)

include(FetchContent)
cmake_policy(SET CMP0135 NEW)

# _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-.
# Library

## Coverage config
add_library(additional_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # No optimization + debug info + coverage flags
    target_compile_options(additional_config INTERFACE -O0 -g --coverage)
    target_link_options(additional_config INTERFACE --coverage)
else ()
    # Full optimization
    target_compile_options(additional_config INTERFACE -O3)
endif ()

## YesChief!
find_package(yeschief 1.1.0 REQUIRED)
message(STATUS "Found YesChief!")
message(STATUS "Included from: ${YESCHIEF_INCLUDE_DIR}")

## CrossedFingers lib
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS crossed_fingers
        "${PROJECT_SOURCE_DIR}/src/crossedfingers/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/crossedfingers/**/*.cpp"
)
message(DEBUG SRC_FILES=${SRC_FILES})

add_library(crossed_fingers ${SRC_FILES})
target_link_libraries(crossed_fingers PUBLIC yeschief)

target_include_directories(crossed_fingers PUBLIC "${PROJECT_SOURCE_DIR}/include" "${YESCHIEF_INCLUDE_DIR}")

target_compile_definitions(crossed_fingers
        PUBLIC LIB_VERSION="${LIB_VERSION}"
)

target_compile_options(crossed_fingers PUBLIC -Wall)

## CrossedFingers main lib
add_library(crossed_fingers_main "${PROJECT_SOURCE_DIR}/src/main.cpp")
target_link_libraries(crossed_fingers_main PUBLIC crossed_fingers)
target_compile_options(crossed_fingers_main PUBLIC -Wall)

# _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-.
# Tests

option(BUILD_TESTING "Build the testing tree." OFF)
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    message(DEBUG "Build test tree")
    enable_testing()
    add_subdirectory(tests)
endif ()

# _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-.
# Packaging

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(DEBUG "Build install tree")
    install(TARGETS crossed_fingers)
    include(packaging)
    lib_package()
endif ()
