add_subdirectory(src)
add_subdirectory(libs)

add_executable(C_TEST test.cpp)
target_link_libraries(C_TEST PUBLIC
    Catch2::Catch2WithMain
    L3
)
target_include_directories(C_TEST PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_test(TEST_C ./C_TEST)
