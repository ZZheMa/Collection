cmake_minimum_required(VERSION 2.8)
project(CsiString) # TODO: Change the project name to yours.

option(JIL_ENABLE_TEST "enable unit test?" ON)

# Enable unicode.
add_definitions(-DUNICODE -D_UNICODE)
 
# Find gtest.
if (JIL_ENABLE_TEST)
    enable_testing()
endif()

# Include the source directory.
include_directories(${PROJECT_SOURCE_DIR}/src/gtest/include)
include_directories(${PROJECT_SOURCE_DIR}/src/gtest)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Disable CRT secure warnings.
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(src)
