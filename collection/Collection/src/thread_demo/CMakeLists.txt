set(SRCS
    01cpp_thread.cpp
    )

set(TARGET_NAME thread_demo)
set(TARGET_OUTPUT_NAME thread_demo)

add_executable(${TARGET_NAME} ${SRCS})

set(EXTRA_LIBS
    )

include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} ${EXTRA_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
