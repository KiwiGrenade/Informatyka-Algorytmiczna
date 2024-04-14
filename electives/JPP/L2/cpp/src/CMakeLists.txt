add_library(GF SHARED
        GF.cpp)

target_include_directories(GF PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../libs)
target_link_libraries(GF PUBLIC
        L1_LIB)
