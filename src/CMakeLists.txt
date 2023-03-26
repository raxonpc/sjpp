# Find libcurl
include(FindCURL)

if(NOT CURL_FOUND)
    message(FATAL_ERROR "LibCURL is required to build sjpp")
endif()


set(HEADER_LIST ${sjpp_SOURCE_DIR}/include/sjpp/sjpp.hpp ${sjpp_SOURCE_DIR}/include/sjpp/types.hpp)

add_library(sjpp sjpp.cpp Parser.cpp Parser.hpp ${HEADER_LIST})

target_include_directories(sjpp
    PUBLIC
    $<BUILD_INTERFACE:${sjpp_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>

    PRIVATE
    ${CURL_INCLUDE_DIRS}
)

set_target_properties(sjpp PROPERTIES PUBLIC_HEADER "${HEADER_LIST}")

target_link_libraries(sjpp ${CURL_LIBRARIES})
target_compile_features(sjpp PUBLIC cxx_std_20)

add_library(sjpp::sjpp ALIAS sjpp)

# IDEs should put the headers in a nice place
source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})

#----------------------------- INSTALL STEP -----------------------------
if(SJPP_INSTALL)
    install(TARGETS sjpp
            EXPORT sjppTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            PUBLIC_HEADER DESTINATION include/sjpp
    )

    # CONFIGURE PACKAGE
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        sjppConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    install(EXPORT sjppTargets
            NAMESPACE sjpp::
            DESTINATION lib/cmake/sjpp)

    set(targets_export_name sjppTargets CACHE INTERNAL "")
    configure_package_config_file(
            ${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/sjppConfig.cmake INSTALL_DESTINATION lib/cmake/sjpp)

    install(
            FILES ${CMAKE_CURRENT_BINARY_DIR}/sjppConfigVersion.cmake ${CMAKE_CURRENT_BINARY_DIR}/sjppConfig.cmake
            DESTINATION lib/cmake/sjpp
    )
endif()
