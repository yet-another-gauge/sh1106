cmake_minimum_required(VERSION 3.0.2)

add_library(sh1106 OBJECT
        ${CMAKE_CURRENT_SOURCE_DIR}/src/syscfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sh1106.c)

target_include_directories(sh1106 PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/)
