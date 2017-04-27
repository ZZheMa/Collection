set(SRCS
    app.cpp
    app.h
	main_frame.h
	main_frame.cpp
	listview.h
	listview.cpp
    )

set(TARGET_NAME listview)
set(TARGET_OUTPUT_NAME ListView)

INCLUDE_DIRECTORIES(
 ${PROJET_SOURCE_DIR}/src/listview
)

add_executable(${TARGET_NAME} WIN32 ${SRCS})

if(WIN32)
    target_link_libraries(${TARGET_NAME} gdiplus)
endif()

target_link_libraries(${TARGET_NAME} ${wxWidgets_LIBRARIES})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${TARGET_OUTPUT_NAME})

