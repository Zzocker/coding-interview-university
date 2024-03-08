project(simpleCMakeExample)


# static libraray .a
add_library(simplecmake printhello.cpp)
# share library .so
# add_library(simplecmake SHARED printhello.cpp)

# define include path
target_include_directories(simplecmake PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)