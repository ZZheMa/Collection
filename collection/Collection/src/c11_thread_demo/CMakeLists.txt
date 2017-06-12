set(SRCS
    01create.cpp
    02lock.cpp
    03condition_variable.cpp
    )

set(TARGET_NAME c11_thread_demo)
set(TARGET_OUTPUT_NAME c11_thread_demo)

add_executable(${TARGET_NAME} ${SRCS})

set(EXTRA_LIBS
    )

include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} ${EXTRA_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
