set(SRCS
    01override_class.cpp
    02var_list.cpp
    )

set(TARGET_NAME other)
set(TARGET_OUTPUT_NAME other)

add_executable(${TARGET_NAME} ${SRCS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
