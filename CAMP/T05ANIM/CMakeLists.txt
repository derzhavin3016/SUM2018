cmake_minimum_required(VERSION 3.16)
project(T05ANIM)

add_executable(anim main.cpp)
set_target_properties(anim PROPERTIES WIN32_EXECUTABLE TRUE)

target_compile_options(anim PRIVATE /W4)
target_compile_features(anim PRIVATE cxx_std_20)
