set(UT_SRCS
    main.cpp
    )
set(UT_TARGET_NAME ut)

add_executable(${UT_TARGET_NAME} ${UT_SRCS})
target_link_libraries(${UT_TARGET_NAME} gtest)

#add_test(${UT_TARGET_NAME} ${UT_TARGET_NAME})

