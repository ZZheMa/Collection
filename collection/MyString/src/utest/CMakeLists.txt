# Unit test.
if(JIL_ENABLE_TEST)
    set(UT_SRCS
	csi_string_test.cc
        )
    set(UT_TARGET_NAME csi_string_unittest)
    add_executable(${UT_TARGET_NAME} ${UT_SRCS})
    target_link_libraries(${UT_TARGET_NAME} gtest str)
endif()
