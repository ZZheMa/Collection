cmake_minimum_required(VERSION 2.8)

project(LearnDLL)

include_directories(${PROJECT_SOURCE_DIR}/src)

IF(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(MSVC)

# Group sources by dir.
# Usage: GROUP_SOURCES_BY_DIR(SRCS)
macro(GROUP_SOURCES_BY_DIR source_files)
    set(sgbd_cur_dir ${CMAKE_CURRENT_BINARY_DIR})
    foreach(sgbd_file ${${source_files}})
        #message("sgbd_fpath=${sgbd_fpath}")
        string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
        string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
        string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
        string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
        if(sgbd_nogroup)
            set(sgbd_group_name "\\")
        endif()
        #message("group name=${sgbd_group_name}")
        source_group(${sgbd_group_name} FILES ${sgbd_file})
    endforeach()
endmacro()

add_subdirectory(src)
