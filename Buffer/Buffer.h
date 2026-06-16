#pragma once

#include "../Position/Position.h"

#include <iostream>
#include <vector>
#include <string>
#include <optional>





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

        const char getChar(const Position pos) const;

        const size_t getLineLength(const size_t index) const;
        void newLine(Position pos);
        void deleteLine(const size_t index);
        std::optional<Position> findLine(const std::string& word, const Position start) const;
};