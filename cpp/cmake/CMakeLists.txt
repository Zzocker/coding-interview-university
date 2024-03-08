# mimumum version of c_make to use
cmake_minimum_required(VERSION 3.15)

# name of the project
project(simpleCMakeExample)

# to support clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# this is root CMakeList
# should only contains sub-directory which child cmakelist
add_subdirectory(include)
add_subdirectory(src)

# give a option to this library user to build example
# define a variable BUILD_EXAMPLE=ON(default)
option(BUILD_EXAMPLE "Whether or not to build example" ON)

if (BUILD_EXAMPLE)
    message(STATUS "Building example....")
    add_subdirectory(example)
endif()
