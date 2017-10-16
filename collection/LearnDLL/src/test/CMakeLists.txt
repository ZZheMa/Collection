set(SRCS
    main.cpp
    )

set(TARGET_NAME test)
set(TARGET_OUTPUT_NAME test)

add_executable(${TARGET_NAME} ${SRCS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
