set(SRCS
    01print_tag_infos.cpp
    02add_same_items.cpp
    03create_dcm_file.cpp
    )

GROUP_SOURCES_BY_DIR(SRCS)

set(LINK_LIBS
    ${DCMTK_LIBRARIES}
)

set(TARGET_NAME src)
set(TARGET_OUTPUT_NAME test)

add_executable(${TARGET_NAME} ${SRCS})

TARGET_LINK_LIBRARIES(${TARGET_NAME} ${LINK_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
