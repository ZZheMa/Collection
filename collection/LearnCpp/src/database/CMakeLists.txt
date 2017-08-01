set(SRCS
    sqlite3_demo/01simple_operation.cpp
    sqlite3_demo/02performance_test.cpp
    sqlite3_demo/03concurrence_test.cpp
    sqlite3_demo/04dirty_read.cpp
    sqlite3_demo/05primarykey_test.cpp

    sqlserver/01odbc_access.cpp
    )

GROUP_SOURCES_BY_DIR(SRCS)

set(TARGET_NAME database)
set(TARGET_OUTPUT_NAME database)

add_executable(${TARGET_NAME} ${SRCS})

set(EXTRA_LIBS
    sqlite3
    utility
    odbc32
    )

include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} ${EXTRA_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
