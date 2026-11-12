#pragma once
#include <string>
#include <memory>

struct node {
    std::string value;
    int index;
    std::unique_ptr<node> left = nullptr;//отвечает за удаление
    std::unique_ptr<node> right = nullptr;
    node* parent = nullptr;//не отвечает за удаление
};

struct levelPair {
    node* n;
    unsigned level;
};