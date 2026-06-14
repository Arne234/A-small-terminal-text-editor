#pragma once

#include <iostream>
#include <conio.h>


class Cursor {
    private: 
        size_t col = 0;
        size_t row = 0;

    public:
        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();

        size_t getCol();
        size_t getRow();

        void setLineBreak();
        void setCol(const size_t c);

};