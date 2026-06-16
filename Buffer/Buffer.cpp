#include "Buffer.h"



Buffer::Buffer() {
    lines.push_back("");
}


void Buffer::insert(Position pos, char c) {
    if (pos.row >= lines.size()) {
        return;
    }
    
    std::string& line = lines[pos.row];

    if (pos.col > line.size()) {
        return;
    }

    line.insert(line.begin() + pos.col, c);
}



void Buffer::deleteChar(Position pos) {
    if (pos.row > lines.size()) {
        return;
    }

    
    std::string& line = lines[pos.row];

    if (pos.col >= line.size()) {
        return;
    }

    line.erase(line.begin() + pos.col);
}


const std::vector<std::string>& Buffer::getText() const {
    return lines;
}


void Buffer::clearLines() {
    lines.clear();
}


void Buffer::addFileVector(std::vector<std::string> v) {

    lines = std::move(v);

    if (lines.empty()) {
        lines.push_back("");
    }
}


const char Buffer::getChar(const Position pos) const {
    return lines[pos.row][pos.col];
}


const size_t Buffer::getLineLength(const size_t index) const {
    return lines[index].length();
}


void Buffer::newLine(Position pos) {
    std::string& line = lines[pos.row];

    const std::string& left = line.substr(0, pos.col);
    const std::string& right = line.substr(pos.col);

    line = left;
    lines.insert(lines.begin() + pos.row + 1, right);
}


void Buffer::deleteLine(const size_t index) {
    const std::string deleteLine = lines[index];
    
    lines.erase(lines.begin() + index);

    lines[index - 1] += deleteLine;
}

std::optional<Position> Buffer::findLine(const std::string& word, const Position start) const {
    
    if (start.col == 0 && start.row == 0) {
        for (size_t row = 0; row < lines.size(); ++row) {
            size_t col = lines[row].find(word);

            if (col != std::string::npos) {
                return Position{row, col};
            }
        }

        return std::nullopt;
    }
    
    
    for (size_t row = start.row; row < lines.size(); ++row) {
        size_t startCol = (row == start.row) ? start.col + 1 : 0;

        size_t col = lines[row].find(word, startCol);

        if (col != std::string::npos) {
            return Position{row, col};
        }
    }
    
    
    for (size_t row = 0; row < lines.size(); ++row) {
        size_t col = lines[row].find(word);

        if (col != std::string::npos) {
            return Position{row, col};
        }
    }

    return std::nullopt;
}