#include "Cursor.h"




void Cursor::moveRight() {
    col += 1;
}


void Cursor::moveLeft() {
    if (col == 0) {
        return;
    }
    col -= 1;
}


void Cursor::moveUp() {
    if (row == 0) {
        return;
    }
    row -= 1;
}


void Cursor::moveDown() {
    row += 1;
}


size_t Cursor::getCol() {
    return col;
}


size_t Cursor::getRow() {
   return row;
}


void Cursor::setRow(const size_t r) {
    row = r;
}


void Cursor::setCol(const size_t c) {
    col = c;
}


void Cursor::setLineBreak() {
    col = 0;
    row++;
}