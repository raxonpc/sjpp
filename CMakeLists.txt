cmake_minimum_required(VERSION 3.14...3.26)

project(
        sjpp
        VERSION 0.01
        DESCRIPTION "Cpp API for SJP polish dictionary"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(SJPP_BUILD_TESTS "Build unit tests" ON)
option(SJPP_BUILD_EXAMPLE "Build example app" ON)


add_subdirectory(src)

if (SJPP_BUILD_EXAMPLE)
    add_subdirectory(app)
endif ()

if (SJPP_BUILD_TESTS)
    add_subdirectory(test)
endif ()