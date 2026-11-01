#pragma once
#include "Node.h"
#include <string>
#include <vector>

class tree {
private:
    node* root = nullptr;
    void fixIndexes(node* n, int index);

public:
    ~tree();

    node* head() const;
    void push(const std::string& x);
    int lookfor(const std::string& x);
    bool eliminate(const std::string& x);
    void show() const;
    
    std::string findMaxByLetters();
    std::vector<node*> getKStage(int k);
    std::string findMaxByLength();
    std::string findMaxByLengthOnKLevel(int k);
};