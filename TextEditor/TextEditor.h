#pragma once

#include "../Buffer/Buffer.h"
#include "../Cursor/Cursor.h"
#include "../FileManager/FileManager.h"

#include <windows.h>


class TextEditor {
    private:
        Buffer& buffer;
        Cursor& cursor;

    public:
        TextEditor(Buffer& b, Cursor& c) : buffer(b), cursor(c) {}

        void run();
        void render();
};