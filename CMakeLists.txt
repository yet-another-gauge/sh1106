cmake_minimum_required(VERSION 3.0.2)

add_library(SH1106 OBJECT
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/sh1106)

target_include_directories(SH1106 PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/)
