add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.c
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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib_h.ads
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stdint_h.ads
        ${CMAKE_CURRENT_SOURCE_DIR}/src/x86_64_linux_gnu_bits_stdint_intn_h.ads
        ${CMAKE_CURRENT_SOURCE_DIR}/src/x86_64_linux_gnu_bits_stdint_uintn_h.ads
        ${CMAKE_CURRENT_SOURCE_DIR}/src/x86_64_linux_gnu_bits_types_h.ads
    COMMAND
        gcc -c -fdump-ada-spec -C lib.h
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.c
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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib_h.ads
    BYPRODUCTS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/build
)

add_custom_target(ADA_WRAPPER_FOR_C ALL
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/test
)

add_test(TEST_ADA_WRAPPER_FOR_C ${CMAKE_CURRENT_SOURCE_DIR}/test)