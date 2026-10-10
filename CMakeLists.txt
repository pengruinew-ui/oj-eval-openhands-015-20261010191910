cmake_minimum_required(VERSION 3.10)
project(problem_015)
set(CMAKE_CXX_STANDARD 17)
# No special optimization flags
# No custom flags
add_executable(code main.cpp)
set_target_properties(code PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
