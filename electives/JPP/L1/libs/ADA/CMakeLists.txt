add_custom_target(ADA_TEST_LIB ALL
    COMMAND gprbuild -p -P Test_Ada_Lib_Prj
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Test_Ada_Lib_Prj.gpr
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ada_lib.adb
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ada_lib.ads
    BYPRODUCTS
        ${CMAKE_CURRENT_SOURCE_DIR}/test/build
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
    
)

add_test(TEST_ADA_LIB ${CMAKE_CURRENT_SOURCE_DIR}/test/build/test)