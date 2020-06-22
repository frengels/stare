cmake_minimum_required(VERSION 3.11)
project(stare VERSION 0.0.1 LANGUAGES CXX)

set(STARE_IS_MASTER_PROJECT OFF)

if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(STARE_IS_MASTER_PROJECT ON)
endif ()

option(STARE_TESTS "Build stare's unit tests" ${STARE_IS_MASTER_PROJECT})

if (STARE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

include(CMakePackageConfigHelpers)

add_library(stare INTERFACE)
add_library(stare::stare ALIAS stare)
target_include_directories(
    stare
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(stare INTERFACE cxx_std_20)
if (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "10.0.0")
        target_compile_options(stare INTERFACE -fconcepts)
        target_compile_definitions(stare INTERFACE STARE_GCC9)
    endif()
endif()

write_basic_package_version_file(
    stareConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(
    TARGETS stare
    EXPORT stareConfig)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/stareConfigVersion.cmake
    DESTINATION lib/cmake/stare)

install(
    EXPORT stareConfig
    NAMESPACE stare::
    DESTINATION lib/cmake/stare)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
    DESTINATION .)