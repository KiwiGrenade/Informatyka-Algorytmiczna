add_custom_command(
	OUTPUT 	${CMAKE_BINARY_DIR}/main
	COMMAND mkdir ${CMAKE_BINARY_DIR}/bin
	COMMAND	mkdir ${CMAKE_BINARY_DIR}/obj
	COMMAND	gprbuild ${CMAKE_CURRENT_SOURCE_DIR}/ada_lib_test.gpr
	SOURCE ada_lib_test.gpr lib.adb lib.ads main.adb test_lib.adb test_lib.ads
)
add_custom_target(Ada ALL 
	DEPENDS ${CMAKE_BINARY_DIR}/main
	DEPENDS ${CMAKE_BINARY_DIR}/bin
	DEPENDS ${CMAKE_BINARY_DIR}/obj
	)
