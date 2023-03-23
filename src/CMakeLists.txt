
add_library(sjpp sjpp.cpp)


target_include_directories(sjpp PUBLIC 
  $<BUILD_INTERFACE:${sjpp_SOURCE_DIR}/include>
 	$<INSTALL_INTERFACE:include>
)
