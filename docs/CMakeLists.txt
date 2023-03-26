find_package(Doxygen REQUIRED)
if(NOT DOXYGEN_FOUND)
    message(FATAL ERROR "Could not find the doxygen executable")
endif()

set(DOXYGEN_GENERATE_MAN NO)
set(DOXYGEN_GENERATE_HTML YES)

set(DOXYGEN_PROJECT_NAME "sjpp")
set(DOXYGEN_PROJECT_NUMBER ${PROJECT_VERSION})
set(DOXYGEN_PROJECT_BRIEF "sjpp is a C++ API for sjp.pl Polish dictionary.")
set(DOXYGEN_STRIP_FROM_PATH ../include/)
set(DOXYGEN_EXAMPLE_PATH ../examples)
set(DOXYGEN_AUTOLINK_SUPPORT YES)
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_REFERENCES_LINK_SOURCE YES)
set(DOXYGEN_IMAGE_PATH images)
set(DOXYGEN_GENERATE_TREEVIEW YES)

doxygen_add_docs(
        doxygen
        mainpage.dox ../include/sjpp/sjpp.hpp ../include/sjpp/types.hpp  ../examples/cli.cpp
        COMMENT "Generate html documentation of sjpp"
)

configure_file(index.html ${CMAKE_BINARY_DIR}/docs/index.html COPYONLY)
