
add_library(sjpp sjpp.cpp Parser.cpp Parser.hpp)

target_include_directories(sjpp PUBLIC
        $<BUILD_INTERFACE:${sjpp_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(sjpp curl)
