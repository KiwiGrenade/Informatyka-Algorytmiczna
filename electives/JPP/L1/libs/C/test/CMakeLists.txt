
add_executable(C_LIB_TEST test_1.cpp)

target_link_libraries(C_LIB_TEST 
    Catch2::Catch2WithMain
    C_Lib
)
    
target_include_directories(C_LIB_TEST
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(TEST_C_LIB ./C_LIB_TEST)