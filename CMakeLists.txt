cmake_minimum_required(VERSION 3.14...3.26)

project(sjpp
        VERSION 0.01
        DESCRIPTION "Cpp API for SJP polish dictionary"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#-----------------------------------------------------------------------------

option(SJPP_BUILD_TESTS "Build unit tests" ON)
option(SJPP_BUILD_APP "Build example app" ON)
option(SJPP_BUILD_EXAMPLES "Build examples" ON)
option(SJPP_INSTALL "Generate install target" ON)
option(SJPP_DOCS "Generate documentation" ON)

#-----------------------------------------------------------------------------

# Disallow in-source builds
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed")
endif()

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

#-----------------------------------------------------------------------------

add_subdirectory(src)

#-----------------------------------------------------------------------------

if (SJPP_BUILD_APP)
    add_subdirectory(app)
endif ()

if (SJPP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (SJPP_BUILD_TESTS)
    # this line must be in the main CMakeLists
    include(CTest)

    add_subdirectory(test)
endif ()

if(SJPP_DOCS)
    add_subdirectory(docs)
endif()