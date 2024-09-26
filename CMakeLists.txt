cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE tools/toolchains/gcc/toolchain.cmake CACHE PATH "toolchain file")
project(hello-unit-testing)

# GoogleTest (https://google.github.io/googletest/)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

if(WIN32)
    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

set(CMAKE_DISABLE_FIND_PACKAGE_Python TRUE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

find_package(Threads REQUIRED)

enable_testing()

# Item under test
add_executable(
    test_calc
    components/calc/src/calc.c
    components/calc/test/test_calc.cc
)

target_include_directories(
    test_calc
    PRIVATE
    components/calc/src
)

target_link_libraries(
    test_calc
    GTest::gtest_main
    GTest::gmock_main
    Threads::Threads
)

gtest_discover_tests(test_calc)

add_custom_target(
    run_test
    ALL
    DEPENDS test_calc
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
)
