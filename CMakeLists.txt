cmake_minimum_required(VERSION 3.14...3.26)

project(
        sjpp
        VERSION 0.01
        DESCRIPTION "Cpp API for SJP polish dictionary"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(app)