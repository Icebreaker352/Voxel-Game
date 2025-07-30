cmake_minimum_required(VERSION 3.13)
project(stb_image)


add_library(stb_image)
target_include_directories(stb_image PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")
target_sources(stb_image PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/stb.cpp")