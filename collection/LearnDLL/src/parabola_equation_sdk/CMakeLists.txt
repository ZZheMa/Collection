set(SRCS
    three_order_determinant.h
    three_order_determinant.cpp
    parabola_equation.h
    parabola_equation.cpp
    point.h
    )

# Project name
set(TARGET_NAME parabola_equation_sdk)
# Executable Name
set(TARGET_OUTPUT_NAME parabola_equation_sdk)

add_library(parabola_equation_sdk ${SRCS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
