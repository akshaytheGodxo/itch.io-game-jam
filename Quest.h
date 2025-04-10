#pragma once
#include <string>

struct Quest {
    std::string title;
    std::string description;
    bool isCompleted = false;
    bool isAccepted = false;
};
