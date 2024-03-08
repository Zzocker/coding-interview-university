# Simple CMake Example

1. Create `CMakeLists.txt`
2. Generate Makefile:
    - `mkdir build`
    - `cmake ..` .. is pointing to where CMakeLists.txt exists
3. Generate `binary`: `make`
4. Execute `./main`

# Multi CMakeList Project

- Any cpp library is divide into three folders
    - `include` : stores all the include files of dependencies + own library include
        - `include/<library_name>` : directory stores all the include files defined by the library
    - `src` : Contains implementation of declared things in include files
    - `example` : generally contains executable file which uses the developed library.

- Root `CMakeList.txt`
```
# minimum version of c_make to use
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
```

- include `CMakeLists.txt`

```
project(simpleCMakeExample)
```

- src `CMakeLists.txt`
```
project(simpleCMakeExample)


# static library .a
add_library(simplecmake printhello.cpp)
# share library .so
# add_library(simplecmake SHARED printhello.cpp)

# define include path
target_include_directories(simplecmake PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
```

- example `CMakeLists.txt`

```
project(simpleCMakeExample)


add_executable(example main.cpp)

target_link_libraries(example PRIVATE simplecmake)
```