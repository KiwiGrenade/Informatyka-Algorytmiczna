add_executable(test_GF test_GF.cpp)
target_include_directories(test_GF PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(test_GF PRIVATE
        Catch2::Catch2WithMain
        GF
)
add_test(TEST_CPP ./test_GF)
