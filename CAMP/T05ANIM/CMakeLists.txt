cmake_minimum_required(VERSION 3.16)

if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
  message(
    FATAL_ERROR
      "In-source builds are disabled.
  Please create a subfolder and use `cmake ..` inside it.
  NOTE: cmake will now create CMakeCache.txt and CMakeFiles/*.
  You must delete them, or cmake will refuse to work.")
endif()

include(cmake/CPM.cmake)
include(cmake/list_dirs.cmake)
include(cmake/upd_tar_list.cmake)

project(T05ANIM LANGUAGES CXX)

add_subdirectory(tools)

set(TARGETS)
list(APPEND TARGETS ${LIBLIST} ${TOOLLIST})

foreach(TARGET ${TARGETS})
  target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_compile_features(${TARGET} PRIVATE cxx_std_20)

  target_compile_options(${TARGET} PRIVATE /W4)
endforeach()

enable_testing()
add_subdirectory(test)
