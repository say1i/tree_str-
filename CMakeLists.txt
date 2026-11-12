cmake_minimum_required(VERSION 4.3)
project(tree_str_)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Tree STATIC
        Tree/Tree.cpp
        Tree/Tree.h
        Tree/Node.h
)
target_include_directories(Tree PUBLIC Tree)

add_library(Html STATIC
        Html/TreeHtml.cpp
        Html/TreeHtml.h
)
target_include_directories(Html PUBLIC Html)
target_link_libraries(Html PUBLIC Tree)

add_executable(tree_str_ main.cpp)
target_link_libraries(tree_str_ PRIVATE Tree Html)