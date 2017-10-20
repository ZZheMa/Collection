set(SRCS
    parabola_equation_wrapper.h
    parabola_equation_wrapper.cpp
    main.cpp
    )

set(TARGET_NAME parabola_dll_wrapper)
set(TARGET_OUTPUT_NAME parabola_dll_wrapper)

add_executable(${TARGET_NAME} ${SRCS})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})
