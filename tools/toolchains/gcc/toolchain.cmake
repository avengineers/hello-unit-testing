set(CMAKE_C_COMPILER gcc CACHE STRING "C Compiler")
set(CMAKE_CXX_COMPILER g++ CACHE STRING "CXX Compiler")
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER} CACHE STRING "ASM Compiler")

find_program(CMAKE_C_COMPILER_FOUND_PATH ${CMAKE_C_COMPILER})
get_filename_component(CMAKE_C_COMPILER_FOUND_PATH ${CMAKE_C_COMPILER_FOUND_PATH} DIRECTORY)
get_filename_component(CMAKE_C_COMPILER_FOUND_PATH ${CMAKE_C_COMPILER_FOUND_PATH} DIRECTORY)
include_directories(BEFORE ${CMAKE_C_COMPILER_FOUND_PATH}/x86_64-w64-mingw32/include)

