cmake_minimum_required(VERSION 2.8)

project(tedit CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

enable_testing()
include(gmock)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(editor)
add_subdirectory(event)
add_subdirectory(view)
add_subdirectory(screen)
add_subdirectory(main)
