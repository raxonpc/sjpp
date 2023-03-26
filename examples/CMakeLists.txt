cmake_minimum_required(VERSION 3.14)

find_package(sjpp REQUIRED)

add_executable(cli cli.cpp)
target_link_libraries(cli sjpp::sjpp)
