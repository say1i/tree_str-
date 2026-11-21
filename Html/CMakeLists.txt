add_library(Html STATIC
        TreeHtml.cpp
        TreeHtml.h
)

target_include_directories(Html PUBLIC .)
target_link_libraries(Html PUBLIC Tree)