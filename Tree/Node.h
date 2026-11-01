#pragma once
#include <string>

struct node {
    std::string value;
    int index;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
};

struct levelPair {
    node* n;
    unsigned level;
};