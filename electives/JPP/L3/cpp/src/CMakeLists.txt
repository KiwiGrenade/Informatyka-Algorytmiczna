add_library(L3_DHSetup SHARED DHSetup.hpp)
add_library(L3_User SHARED User.hpp)
set_target_properties(L3_DHSetup PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(L3_User PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(L3_DHSetup PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)
target_include_directories(L3_User PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)
target_link_libraries(L3_DHSetup PUBLIC L2)
target_link_libraries(L3_User PUBLIC L3_DHSetup)
