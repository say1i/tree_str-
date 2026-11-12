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

node* tree::head() const {
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

int tree::lookfor(const string& x) {
    node* temp = root.get();
    while (temp) {
        if (x == temp->value) return temp->index;
        temp = (x < temp->value ? temp->left : temp->right).get();
    }
    return -1;
}

bool tree::eliminate(const string& x) {
    node* temp = root.get();

    while (temp && temp->value != x) {
        if (x < temp->value) temp = temp->left.get();
        else temp = temp->right.get();
    }

    if (temp == nullptr) return false;

    // узел без потомков
    if (temp->left == nullptr && temp->right == nullptr) {
        if (temp == root.get()) root.reset();
        else if (temp->parent->left.get() == temp) temp->parent->left.reset();
        else temp->parent->right.reset();
    }
    // узел с одним потомком
    else if (temp->left == nullptr || temp->right == nullptr) {
        unique_ptr<node> child = temp->left != nullptr ? move(temp->left) : move(temp->right);
        child->parent = temp->parent;

        if (temp == root.get()) {
            root = move(child);
        }
        else {
            auto& link = (temp->parent->left.get() == temp) ? temp->parent->left : temp->parent->right;
            link = move(child);
        }
    }
    // узел с двумя потомками
    else {
        node* pred = temp->left.get();
        while (pred->right != nullptr) pred = pred->right.get();

        // Замена данных
        temp->value = pred->value;

        // Удаление предшественника
        unique_ptr<node> child = move(pred->left);
        node* parent = pred->parent;

        if (child != nullptr) child->parent = parent;

        auto& link = (parent->left.get() == pred) ? parent->left : parent->right;
        link = move(child);
    }

    fixIndexes(root.get(), 1);
    return true;
}

void tree::show() const {
    cout << "{ ";
    if (!root) {
        cout << '}' << endl;
        return;
    }

    queue<node*> q;
    q.push(root.get());

    while (!q.empty()) {
        node* p = q.front();
        q.pop();
        cout << "\n " << p->index << ": " << p->value;

        if (p->left) q.push(p->left.get());
        if (p->right) q.push(p->right.get());
    }

    cout << "\n}" << endl;
}

string tree::findMaxByLetters() {
    if (!root) return "";

    node* temp = root.get();
    while (temp->right != nullptr) temp = temp->right.get();

    return temp->value;
}

vector<node*> tree::getKStage(int k) {
    vector<node*> r;
    if (!root) return r;

    queue<levelPair> q;
    q.push({root.get(), 1});

    while (!q.empty()) {
        levelPair lp = q.front();
        q.pop();

        if (k == lp.level) r.push_back(lp.n);

        if (lp.n->left) q.push({lp.n->left.get(), lp.level + 1});
        if (lp.n->right) q.push({lp.n->right.get(), lp.level + 1});
    }

    return r;
}

string tree::findMaxByLength() {
    if (!root) return "";

    string max = root->value;
    queue<node*> q;
    q.push(root.get());

    while (!q.empty()) {
        node* n = q.front();
        q.pop();

        if (n->value.size() > max.size()) max = n->value;

        if (n->left) q.push(n->left.get());
        if (n->right) q.push(n->right.get());
    }

    return max;
}

string tree::findMaxByLengthOnKLevel(int k) {
    if (!root) return "";

    string max = "";
    queue<levelPair> q;
    q.push({root.get(), 1});

    while (!q.empty()) {
        levelPair lp = q.front();
        q.pop();

        if (k == lp.level && lp.n->value.size() > max.size()) max = lp.n->value;

        if (lp.n->left) q.push({lp.n->left.get(), lp.level + 1});
        if (lp.n->right) q.push({lp.n->right.get(), lp.level + 1});
    }

    return max;
}