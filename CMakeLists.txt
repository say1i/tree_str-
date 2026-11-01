cmake_minimum_required(VERSION 4.3)
project(tree_str_)

set(CMAKE_CXX_STANDARD 20)

add_executable(tree_str_ main.cpp
        Tree/Node.h
        Tree/Tree.cpp
        Tree/Tree.h
        Html/TreeHtml.cpp
        Html/TreeHtml.h
)
