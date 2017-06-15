set(SRCS
    thread/01create.cpp
    thread/02lock.cpp
    thread/03condition_variable.cpp
    thread/04producer_consumer.cpp
    thread/05atomic.cpp
    
    smart_pointer/01smart_pointer.cpp
    )

GROUP_SOURCES_BY_DIR(SRCS)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(TARGET_NAME c11_demo)
set(TARGET_OUTPUT_NAME c11_demo)

add_executable(${TARGET_NAME} ${SRCS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
