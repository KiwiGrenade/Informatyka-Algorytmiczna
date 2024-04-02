# set(GO_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/GO)

add_executable(C_WRP_FOR_GO_UT test.cpp)

add_library(go_shared_lib SHARED IMPORTED)

set_property(TARGET go_shared_lib PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/GO/lib.so)

add_library(c_wrp_for_GO_lib SHARED wrapper.c)
target_include_directories(c_wrp_for_GO_lib
    PUBLIC ../../libs/GO
)

target_link_libraries(C_WRP_FOR_GO_UT PUBLIC 
    c_wrp_for_GO_lib
    go_shared_lib
    Catch2::Catch2WithMain
)

target_include_directories(C_WRP_FOR_GO_UT
    PUBLIC ../../libs/GO
)

add_test(
    NAME 
        TEST_C_WRP_FOR_GO
    COMMAND 
        ./C_WRP_FOR_GO_UT
)