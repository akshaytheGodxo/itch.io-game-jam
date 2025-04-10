#pragma once
#include <string>

struct Item {
    std::string name;
    std::string description;
    int quantity;

    Item(const std::string& n, const std::string& d, int q = 1)
        : name(n), description(d), quantity(q) {}
};
