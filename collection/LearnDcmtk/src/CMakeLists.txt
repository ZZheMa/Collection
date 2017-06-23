set(SRCS
    01print_tag_infos.cpp
    )

GROUP_SOURCES_BY_DIR(SRCS)

set(DCMTK_LIB_DIR        $ENV{DCMTK_DIR}/lib)
set(DCMTK_INCLUDE_DIR    $ENV{DCMTK_DIR}/include)

include_directories(${DCMTK_INCLUDE_DIR})

LINK_DIRECTORIES(${DCMTK_LIB_DIR})

set(TARGET_NAME src)
set(TARGET_OUTPUT_NAME test)

set(LINK_LIBS
    ws2_32
    netapi32
    ofstd
    dcmdata 
    oflog 
    dcmnet 
    )

add_executable(${TARGET_NAME} ${SRCS})

TARGET_LINK_LIBRARIES(${TARGET_NAME} ${LINK_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
