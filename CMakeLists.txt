cmake_minimum_required(VERSION 3.11)
project(stare LANGUAGES CXX)

set(IS_MASTER_PROJECT OFF)

if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(IS_MASTER_PROJECT ON)
endif ()

option(STARE_TESTS "Build stare's unit tests" ${IS_MASTER_PROJECT})

add_library(stare INTERFACE)
target_include_directories(stare INTERFACE include)
target_compile_features(stare INTERFACE cxx_std_20)

if (STARE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()