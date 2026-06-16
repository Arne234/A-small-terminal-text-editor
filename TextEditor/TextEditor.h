#pragma once

#include "../Buffer/Buffer.h"
#include "../Cursor/Cursor.h"
#include "../FileManager/FileManager.h"
#include "../History/History.h"

#include <windows.h>


class TextEditor {
    private:
        Buffer& buffer;
        Cursor& cursor;
        History& history;

    public:
        TextEditor(Buffer& b, Cursor& c, History& h) : buffer(b), cursor(c), history(h) {}

        void run();
        void render();

        bool apply(const Action& action);
        bool applyReverse(const Action& action);
};