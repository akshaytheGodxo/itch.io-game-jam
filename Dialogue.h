#pragma once
#include <string>
#include <vector>

struct Dialogue {
    std::vector<std::string> lines;
    int currentLine = 0;

    std::string getCurrentLine() const {
        if (currentLine < lines.size()) return lines[currentLine];
        return "";
    }

    void nextLine() {
        if (currentLine < lines.size()) currentLine++;
    }

    bool isFinished() const {
        return currentLine >= lines.size();
    }

    void reset() {
        currentLine = 0;
    }
};
