#pragma once
#include "Node.h"
#include <string>
#include <vector>
#include <memory>
#include <optional>

class tree {
private:
    std::unique_ptr<node> root = nullptr;
    void fixIndexes(node* n, int index);

public:
    ~tree() = default;

    const node* head() const noexcept;
    void push(const std::string &x);
    std::optional<std::size_t> lookfor(std::string_view x) const noexcept;
    bool eliminate(std::string_view x);
    void show() const;

    std::string findMaxByLetters() const;

    std::vector<node *> getKStage(std::size_t k) const;
    std::string findMaxByLength() const;
    std::string findMaxByLengthOnKLevel(std::size_t k) const;
};
