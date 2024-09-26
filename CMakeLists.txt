cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE tools/toolchains/gcc/toolchain.cmake CACHE PATH "toolchain file")
project(hello-unit-testing)

add_executable(
    test_calc
    components/calc/src/calc.c
    components/calc/test/test_calc.c
)

target_include_directories(
    test_calc
    PRIVATE
    components/calc/src
)

# Phony target to run the tests
add_custom_target(
    run_test
    ALL
    DEPENDS test_calc
    COMMAND test_calc
)
