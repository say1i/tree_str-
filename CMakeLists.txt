cmake_minimum_required(VERSION 4.3)
project(tree_str_)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS program_options)

add_subdirectory(Tree)
add_subdirectory(Html)

configure_file(config.cfg config.cfg COPYONLY)

add_executable(tree_str_ main.cpp)
target_link_libraries(tree_str_ PRIVATE Tree Html Boost::program_options)

add_executable(tree_tests tree_test.cpp)
target_include_directories(tree_tests PRIVATE tests)
target_link_libraries(tree_tests PRIVATE Tree Html)

enable_testing()
add_test(NAME tree_unit_tests COMMAND tree_tests)