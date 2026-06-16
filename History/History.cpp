#include "History.h"



void History::pushUndo(const Action& a) {
    undoStack.push(a);

    while (!redoStack.empty()) {
        redoStack.pop();
    }
    
    if (undoStack.size() > maxLen) {
        std::stack<Action> temp;

        while (undoStack.size() > 1) {
            temp.push(undoStack.top());
            undoStack.pop();
        }

        undoStack.pop();

        while (!temp.empty()) {
            undoStack.push(temp.top());
            temp.pop();
        }
    }
}


std::optional<Action> History::undo() {
    if (!undoStack.empty()) {
        Action action = undoStack.top();
        undoStack.pop();
        redoStack.push(action);

        return action;
    }
    else {
        return std::nullopt;
    }
}


std::optional<Action> History::redo() {
    if (!redoStack.empty()) {
        Action action = redoStack.top();
        redoStack.pop();
        undoStack.push(action);

        return action;
    }
    else {
        return std::nullopt;
    }
}