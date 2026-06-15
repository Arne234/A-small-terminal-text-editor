#pragma once

#include <iostream>
#include <vector>
#include <string>


struct Position {
    size_t row;
    size_t col;
};


class Buffer {
    private:
        std::vector<std::string> lines;

    public:
        Buffer();

        void insert(Position pos, char c);
        void deleteChar(Position pos);
        const std::vector<std::string>& getText() const;

        void clearLines();
        void addFileVector(std::vector<std::string> v);

        const size_t getLineLength(const size_t index) const;
        void newLine(Position pos);
        void deleteLine(const size_t index);
};