#include "Tree.h"
#include <iostream>
#include <memory>
#include <queue>
#include <utility>

using namespace std;

void tree::fixIndexes(node* n, int index) {
    if (!n) return;
    n->index = index;
    fixIndexes(n->left.get(), index * 2);
    fixIndexes(n->right.get(), index * 2 + 1);
}

const node *tree::head() const  noexcept{
    return root.get();
}

void tree::push(const string& x) {
    if (root == nullptr) {
        root = make_unique<node>();
        root->value = x;
        root->index = 1;
        return;
    }

    node* temp = root.get();
    while (true) {
        if (x <= temp->value) {
            if (temp->left == nullptr) {
                temp->left = make_unique<node>();
                temp->left->value = x;
                temp->left->index = temp->index * 2;
                temp->left->parent = temp;
                break;
            }
            temp = temp->left.get();
        }
        else {
            if (temp->right == nullptr) {
                temp->right = make_unique<node>();
                temp->right->value = x;
                temp->right->index = temp->index * 2 + 1;
                temp->right->parent = temp;
                break;
            }
            temp = temp->right.get();
        }
    }
}

std::optional<std::size_t> tree::lookfor(std::string_view x) const noexcept {
    const node* temp = root.get();
    while (temp) {
        if (x == temp->value) return temp->index;
        temp = (x < temp->value) ? temp->left.get() : temp->right.get();
    }
    return std::nullopt;
}

bool tree::eliminate(std::string_view x) {
    node* temp = root.get();

    while (temp && temp->value != x) {
        temp = (x < temp->value) ? temp->left.get() : temp->right.get();
    }

    if (!temp) return false;

    // Узел без потомков
    if (!temp->left && !temp->right) {
        if (temp == root.get()) {
            root.reset();
        } else if (temp->parent->left.get() == temp) {
            temp->parent->left.reset();
        } else {
            temp->parent->right.reset();
        }
    }
    // Узел с одним потомком
    else if (!temp->left || !temp->right) {
        std::unique_ptr<node> child = temp->left ? std::move(temp->left) : std::move(temp->right);
        child->parent = temp->parent;

        if (temp == root.get()) {
            root = std::move(child);
        } else {
            auto& link = (temp->parent->left.get() == temp) ? temp->parent->left : temp->parent->right;
            link = std::move(child);
        }
    }
    // Узел с двумя потомками
    else {
        node* pred = temp->left.get();
        while (pred->right) {
            pred = pred->right.get();
        }

        temp->value = std::move(pred->value);

        std::unique_ptr<node> child = std::move(pred->left);
        node* parent = pred->parent;

        if (child) {
            child->parent = parent;
        }

        auto& link = (parent->left.get() == pred) ? parent->left : parent->right;
        link = std::move(child);
    }

    fixIndexes(root.get(), 1);
    return true;
}

void tree::show() const {
    std::cout << "{ ";
    if (!root) {
        std::cout << "}\n";
        return;
    }

    std::queue<const node*> q;
    q.push(root.get());

    while (!q.empty()) {
        const node* p = q.front();
        q.pop();
        std::cout << "\n " << p->index << ": " << p->value;

        if (p->left) q.push(p->left.get());
        if (p->right) q.push(p->right.get());
    }

    std::cout << "\n}\n";
}

std::string tree::findMaxByLetters() const {
    if (!root) return {};

    const node* temp = root.get();
    while (temp->right) {
        temp = temp->right.get();
    }

    return temp->value;
}

vector<node*> tree::getKStage(std::size_t k) const {
    std::vector<node*> r;
    if (!root || k == 0) return r;

    std::queue<levelPair> q;
    q.push({root.get(), 1});

    while (!q.empty()) {
        auto [n, level] = q.front();
        q.pop();

        if (level > k) break;
        if (level == k) r.push_back(vector<node *>::value_type(n));

        if (n->left) q.push({n->left.get(), level + 1});
        if (n->right) q.push({n->right.get(), level + 1});
    }

    return r;
}

std::string tree::findMaxByLength() const {
    if (!root) return {};

    std::string maxStr = root->value;
    std::queue<const node*> q;
    q.push(root.get());

    while (!q.empty()) {
        const node* n = q.front();
        q.pop();

        if (n->value.size() > maxStr.size()) {
            maxStr = n->value;
        }

        if (n->left) q.push(n->left.get());
        if (n->right) q.push(n->right.get());
    }

    return maxStr;
}

std::string tree::findMaxByLengthOnKLevel(std::size_t k) const {
    if (!root || k == 0) return {};

    std::string maxStr;
    std::queue<levelPair> q;
    q.push({root.get(), 1});

    while (!q.empty()) {
        auto [n, level] = q.front();
        q.pop();

        if (level > k) break;
        if (level == k && n->value.size() > maxStr.size()) {
            maxStr = n->value;
        }

        if (n->left) q.push({n->left.get(), level + 1});
        if (n->right) q.push({n->right.get(), level + 1});
    }

    return maxStr;
}