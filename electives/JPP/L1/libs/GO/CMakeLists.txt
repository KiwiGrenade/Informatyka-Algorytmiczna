add_test(
    NAME 
        TEST_GO_LIB
    COMMAND 
        go test lib.go lib_test.go
    WORKING_DIRECTORY 
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
add_custom_command(
    OUTPUT
        lib.h
        lib.so
    COMMAND
        go build -o lib.so -buildmode=c-shared lib_c.go
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/lib_c.go
        ${CMAKE_CURRENT_SOURCE_DIR}/go.mod
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)

