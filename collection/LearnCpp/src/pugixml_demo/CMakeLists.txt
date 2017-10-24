set(SRCS
    write_and_write.cpp
    )

set(TARGET_NAME pugixml_demo)
set(TARGET_OUTPUT_NAME pugixml_demo)

INCLUDE_DIRECTORIES(
 ${PROJET_SOURCE_DIR}/src/pugixml
 )

add_executable(${TARGET_NAME} ${SRCS})

set(EXTRA_LIBS
    pugixml
    )

target_link_libraries(${TARGET_NAME} ${EXTRA_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
