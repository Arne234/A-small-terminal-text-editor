#pragma once

#include "../Position/Position.h"

#include <stack>
#include <iostream>
#include <optional>


enum class ActionType {
    insert,
    delete_char
};


struct Action {
    ActionType a;
    Position pos;
    char c;
};


class History {
    private:
        std::stack<Action> undoStack;
        std::stack<Action> redoStack;
        size_t maxLen = 500;

    public:
        void pushUndo(const Action& a);
        std::optional<Action> undo();
        std::optional<Action> redo();
};