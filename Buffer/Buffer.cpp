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


void Buffer::deleteEnterLine(const size_t index) {
    const std::string deleteLine = lines[index];
    
    lines.erase(lines.begin() + index);

    lines[index - 1] += deleteLine;
}