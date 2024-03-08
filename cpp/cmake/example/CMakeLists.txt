project(simpleCMakeExample)


add_executable(example main.cpp)

target_link_libraries(example PRIVATE simplecmake)