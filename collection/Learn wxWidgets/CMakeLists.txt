cmake_minimum_required(VERSION 2.8)
project(Learn_wxWidgets)

# Enable unicode.
add_definitions(-DUNICODE -D_UNICODE)
include_directories(${PROJECT_SOURCE_DIR})

# Find wxWidgets.
find_package(wxWidgets REQUIRED core base adv)
include(${wxWidgets_USE_FILE})


# Include the source directory.
include_directories(${PROJECT_SOURCE_DIR}/src)

# Disable CRT secure warnings.
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(src)
