cmake_minimum_required(VERSION 2.8)

project(Collection)

add_definitions(-DUNICODE -D_UNICODE)

add_subdirectory(src/sqlite3)
add_subdirectory(src/sqlite3_demo)

include_directories(${PROJECT_SOURCE_DIR}/src)
