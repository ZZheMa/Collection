set(SRCS
    sqlite3/01simple_operation.cpp
    sqlite3/02performance_test.cpp
    sqlite3/03concurrence_test.cpp
    sqlite3/04dirty_read.cpp
    sqlite3/05primarykey_test.cpp

    odbc/01odbc_access.cpp
    soci/01simple_operation.cpp
    soci/02orm.cpp
    )

GROUP_SOURCES_BY_DIR(SRCS)

set(TARGET_NAME database)
set(TARGET_OUTPUT_NAME database)

LINK_DIRECTORIES(${SOCI_LIB_DIR})

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${SOCI_INCLUDE_DIR}
                    ${SOCI_INCLUDE_DIR}/core)

add_executable(${TARGET_NAME} ${SRCS})

set(EXTRA_LIBS
    sqlite3
    utility
    soci_core_3_2
    soci_sqlite3_3_2
    soci_odbc_3_2
    odbc32
    )

target_link_libraries(${TARGET_NAME} ${EXTRA_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})

INSTALL(DIRECTORY ${SOCI_DLL_DIR}/Debug ${SOCI_DLL_DIR}/Release
        DESTINATION ${PROJECT_BINARY_DIR}/src/${TARGET_OUTPUT_NAME})
#message("${PROJECT_BINARY_DIR}/src/${TARGET_OUTPUT_NAME}")