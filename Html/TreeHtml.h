#pragma once
#include "../Tree/Tree.h"
#include <string>
#include <sstream>
#include <queue>

class treeHtml {
private:
    std::string file;
    std::string title;
    std::ostringstream out;

    void add_node(std::queue<node*>& nodes, node*& temp, node* child, bool is_left);

public:
    treeHtml(std::string file = "", std::string title = "Бинарное Дерево");
    
    void push(const tree& instance, const std::string& description = "");
    bool save() const;
};