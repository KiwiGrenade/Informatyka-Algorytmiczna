set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_custom_command(
    OUTPUT
        ${SRC_DIR}/lib.h
        ${SRC_DIR}/lib.c
    COMMAND cp ../../libs/C/src/lib.c ../../libs/C/src/lib.h src
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/C/src/lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/C/src/lib.h
    VERBATIM
    USES_TERMINAL
)

add_custom_command(
    OUTPUT
        ${SRC_DIR}/lib_h.ads
        ${SRC_DIR}/stdint_h.ads
        ${SRC_DIR}/x86_64_linux_gnu_bits_stdint_intn_h.ads
        ${SRC_DIR}/x86_64_linux_gnu_bits_stdint_uintn_h.ads
        ${SRC_DIR}/x86_64_linux_gnu_bits_types_h.ads
    COMMAND
        gcc -c -fdump-ada-spec -C lib.h
    WORKING_DIRECTORY
        ${SRC_DIR}
    DEPENDS
        ${SRC_DIR}/lib.h
        ${SRC_DIR}/lib.c
    VERBATIM
    USES_TERMINAL
)

add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/test
    COMMAND
        gprbuild -p -P Test_C_Wrp_Prj.gpr
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/Test_C_Wrp_Prj.gpr
        ${SRC_DIR}/lib_h.ads
    BYPRODUCTS
        ${SRC_DIR}/build
)

add_custom_target(ADA_WRP_FOR_C ALL
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/test
)

add_test(TEST_ADA_WRP_FOR_C ${CMAKE_CURRENT_SOURCE_DIR}/test)