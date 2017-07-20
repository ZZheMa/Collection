set(SRCS
    01simple_operation.cpp
    02performance_test.cpp
    03concurrence_test.cpp
    04dirty_read.cpp
    05primarykey_test.cpp
    )

set(TARGET_NAME sqlite3_demo)
set(TARGET_OUTPUT_NAME sqlite3_demo)

add_executable(${TARGET_NAME} ${SRCS})

set(EXTRA_LIBS
    sqlite3
    utility
    )

include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} ${EXTRA_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
