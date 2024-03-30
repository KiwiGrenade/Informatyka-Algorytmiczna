set(ADA_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/ADA/src)
add_custom_target(C_WRAPPER_FOR_ADA ALL
    COMMAND gprbuild -p -P Test_Ada_Wrapper_Prj
    SOURCES
        wrapper.c
        wrapper.h
        Test_Ada_Wrapper_Prj.gpr
        ${ADA_LIB_DIR}/ada_lib.adb
        ${ADA_LIB_DIR}/ada_lib.ads
        ${ADA_LIB_DIR}/../Test_Ada_Lib_Prj.gpr
    BYPRODUCTS
        ${CMAKE_CURRENT_SOURCE_DIR}/test
        ${CMAKE_CURRENT_SOURCE_DIR}/build
        ${ADA_LIB_DIR}/build
        ${ADA_LIB_DIR}/include
        ${ADA_LIB_DIR}/lib
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)
add_test(TEST_C_WRAPPER_FOR_ADA ${CMAKE_CURRENT_SOURCE_DIR}/test)
