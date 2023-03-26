cmake_minimum_required(VERSION 3.14)

find_package(sjpp REQUIRED)

add_executable(cli basic_word_lookup.cpp)
target_link_libraries(cli sjpp::sjpp)
