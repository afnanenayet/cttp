# CMAKE file for cttp
# Afnan Enayet

cmake_minimum_required(VERSION 3.9)
project(cttp C)
include_directories(include)
file(GLOB sources "src/*.c")
add_executable(cttp ${sources})

