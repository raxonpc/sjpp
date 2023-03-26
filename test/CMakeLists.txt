include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(parser_test parser_test.cpp)
target_link_libraries(parser_test GTest::gtest_main sjpp)

# copy test file
add_custom_command(
        TARGET parser_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/kruk.html
        ${CMAKE_CURRENT_BINARY_DIR}/kruk.html)

include(GoogleTest)
gtest_discover_tests(parser_test)