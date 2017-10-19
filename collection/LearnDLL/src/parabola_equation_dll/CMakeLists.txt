set(SRCS
    parabola_equation_dll.h
    parabola_equation_dll.cpp
    )

add_definitions(-DPARABOLA_EQUATION_EXPORT)

# Project name
set(TARGET_NAME parabola_equation_dll)
# Executable Name
set(TARGET_OUTPUT_NAME parabola_equation_dll)

add_library(parabola_equation_dll SHARED ${SRCS})

set(EXTRA_LIBS
    parabola_equation_sdk
    )

target_link_libraries(${TARGET_NAME} ${EXTRA_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
