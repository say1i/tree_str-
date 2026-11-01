#include "Tree.h"
#include <iostream>
#include <queue>

using namespace std;

void tree::fixIndexes(node* n, int index) {
    if (!n) return;
    n->index = index;
    fixIndexes(n->left, index * 2);
    fixIndexes(n->right, index * 2 + 1);
}

tree::~tree() {}

node* tree::head() const { 
    return root; 
}

void tree::push(const string& x) {
    if (root == nullptr) {
        root = new node;
        root->value = x;
        root->index = 1;
        return;
    }

    node* temp = root;
    while (true) {
        if (x <= temp->value) {
            if (temp->left == nullptr) {
                temp->left = new node;
                temp->left->value = x;
                temp->left->index = temp->index * 2;
                temp->left->parent = temp;
                break;
            }
            temp = temp->left;
        }
        else {
            if (temp->right == nullptr) {
                temp->right = new node;
                temp->right->value = x;
                temp->right->index = temp->index * 2 + 1;
                temp->right->parent = temp;
                break;
            }
            temp = temp->right;
        }
    }
}

int tree::lookfor(const string& x) {
    node* temp = root;
    while (temp) {
        if (x == temp->value) return temp->index;
        temp = (x < temp->value) ? temp->left : temp->right;
    }
    return -1;
}

bool tree::eliminate(const string& x) {
    node* temp = root;

    while (temp && temp->value != x) {
        if (x < temp->value) temp = temp->left;
        else temp = temp->right;
    }

    if (temp == nullptr) return false;

    // узел без потомков
    if (temp->left == nullptr && temp->right == nullptr) {
        if (temp == root) root = nullptr;
        else if (temp->parent->left == temp) temp->parent->left = nullptr;
        else temp->parent->right = nullptr;
        delete temp;
    }
    // узел с одним потомком
    else if (temp->left == nullptr || temp->right == nullptr) {
        node* child = temp->left != nullptr ? temp->left : temp->right;

        if (temp == root) {
            root = child;
            child->parent = nullptr;
        }
        else {
            if (temp->parent->left == temp) temp->parent->left = child;
            else temp->parent->right = child;
            child->parent = temp->parent;
        }
        delete temp;
    }
    // узел с двумя потомками
    else {
        node* pred = temp->left;
        while (pred->right != nullptr) pred = pred->right;

        // Замена данных
        temp->value = pred->value;

        // Удаление предшественника
        node* child = pred->left;
        node* parent = pred->parent;

        if (parent->left == pred) parent->left = child;
        else parent->right = child;

        if (child != nullptr) child->parent = parent;

        delete pred;
    }

    fixIndexes(root, 1);
    return true;
}

void tree::show() const {
    cout << "{ ";
    if (!root) {
        cout << '}' << endl;
        return;
    }

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* p = q.front();
        q.pop();
        cout << "\n " << p->index << ": " << p->value;

        if (p->left) q.push(p->left);
        if (p->right) q.push(p->right);
    }

    cout << "\n}" << endl;
}

string tree::findMaxByLetters() {
    if (!root) return "";

    node* temp = root;
    while(temp->right != nullptr) temp = temp->right;

    return temp->value;
}

vector<node*> tree::getKStage(int k) {
    vector<node*> r;
    if (!root) return r;

    queue<levelPair> q;
    q.push({root, 1});

    while (!q.empty()) {
        levelPair lp = q.front();
        q.pop();

        if (k == lp.level) r.push_back(lp.n);

        if (lp.n->left) q.push({lp.n->left, lp.level + 1});
        if (lp.n->right) q.push({lp.n->right, lp.level + 1});
    }

    return r;
}

string tree::findMaxByLength() {
    if (!root) return "";

    string max = root->value;
    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* n = q.front();
        q.pop();

        if (n->value.size() > max.size()) max = n->value;

        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }

    return max;
}

string tree::findMaxByLengthOnKLevel(int k) {
    if (!root) return "";

    string max = "";
    queue<levelPair> q;
    q.push({root, 1});

    while (!q.empty()) {
        levelPair lp = q.front();
        q.pop();

        if (k == lp.level && lp.n->value.size() > max.size()) max = lp.n->value;

        if (lp.n->left) q.push({lp.n->left, lp.level + 1});
        if (lp.n->right) q.push({lp.n->right, lp.level + 1});
    }

    return max;
}