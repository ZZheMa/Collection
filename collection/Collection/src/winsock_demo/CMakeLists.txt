set(SRCS
    01tcp_server.cpp
    01tcp_client.cpp
    02udp_server.cpp
    02udp_client.cpp
    )

set(TARGET_NAME winsock_demo)
set(TARGET_OUTPUT_NAME winsock_demo)

add_executable(${TARGET_NAME} ${SRCS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
