add_library(L3 SHARED DHSetup.hpp)
set_target_properties(L3 PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(L3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libs)
target_link_libraries(L3 PUBLIC L2)
