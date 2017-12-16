# CMakeLists.txt for testing subdirectory for cttp
cmake_minimum_required(VERSION 3.0)

set(TEST_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
)

file(GLOB sources "src/*_test.c")

# create a test for each test file in sources
foreach(test_file ${sources})
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})
    add_dependencies(${test_name} ${test_name})
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${TEST_OUTPUT_DIR})
    target_link_libraries(${test_name} cttpfn cmocka)
    set_target_properties(
        ${test_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR}
        )
endforeach(test_file)
