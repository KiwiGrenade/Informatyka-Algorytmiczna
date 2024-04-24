add_executable(DHSetup_TEST test_DHSetup.cpp)
add_executable(User_TEST test_User.cpp)

target_link_libraries(DHSetup_TEST PUBLIC
    Catch2::Catch2WithMain
    L3_DHSetup
)
target_link_libraries(User_TEST PUBLIC
    Catch2::Catch2WithMain
    L3_DHSetup
)

target_include_directories(DHSetup_TEST PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)
target_include_directories(User_TEST PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(TEST_DHSetup ./DHSetup_TEST)
add_test(TEST_User ./User_TEST)
