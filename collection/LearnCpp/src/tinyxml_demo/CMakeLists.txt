set(SRCS
    write_and_write.cpp
    )

set(TARGET_NAME tinyxml_demo)
set(TARGET_OUTPUT_NAME tinyxml_demo)

INCLUDE_DIRECTORIES(
 ${PROJET_SOURCE_DIR}/src/tinyxml
 )

add_executable(${TARGET_NAME} ${SRCS})

set(EXTRA_LIBS
    tinyxml
    )

target_link_libraries(${TARGET_NAME} ${EXTRA_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
