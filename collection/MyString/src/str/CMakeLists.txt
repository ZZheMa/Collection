set(SRCS
    csi_string.h
	csi_string.cc
	main.cc
    )

set(TARGET_NAME CsiString)
add_library(str ${SRCS})
add_executable(${TARGET_NAME} ${SRCS})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME CsiString)
