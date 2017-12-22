# build file for cttp
# Afnan Enayet

cmake_minimum_required(VERSION 3.2)
project(cttp C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(program_name cttp)
include(CTest)

# Output to certain folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(TARGET_GROUP production CACHE_STRING "build target")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -fsanitize=address -std=c11 -Wold-style-definition -O3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -o2 -std=c11")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    # set(CMAKE_VERBOSE_MAKEFILE ON)
    enable_testing()
    add_subdirectory(test)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

include_directories(include)
file(GLOB sources "src/*.c")
add_executable(${program_name} ${sources})
target_link_libraries(${program_name} m)
set_property(TARGET ${program_name} PROPERTY C_STANDARD 11)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    list(REMOVE_ITEM sources ${PROJECT_SOURCE_DIR}/src/cttp.c)
    add_library(cttpfn ${sources})
    set_property(TARGET cttpfn PROPERTY C_STANDARD 11)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)
