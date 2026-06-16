#include "TextEditor.h"


enum class Mode {
    normal,
    searching
};

std::string search;
std::optional<Position> lastMatch;
Mode mode = Mode::normal;


void TextEditor::run() {
    
    bool gameRunning = true;

    FileManager file(buffer);

    file.loadFiles();

    do {

        render();

        int c = _getch();

        switch(c) {
            case 27:
                if (mode == Mode::searching) {
                    mode = Mode::normal;
                    search.clear();
                    lastMatch.reset();
                }

                gameRunning = false;
                break;
            case 19:
                file.saveFiles();
                break;
            case 32:
                if (mode == Mode::searching) {
                    search += ' ';
                    break;
                }
                
                buffer.insert({cursor.getRow(), cursor.getCol()}, ' ');
                history.pushUndo({ActionType::insert, Position{cursor.getRow(), cursor.getCol()}, ' '});
                cursor.moveRight();
                break;
            case 9:
                buffer.insert({cursor.getRow(), cursor.getCol()}, '\t');
                cursor.moveRight();
                break;      
            case 8:
                if (mode == Mode::searching) {
                    if (!search.empty()) {
                        search.pop_back();
                    }
                    break;
                }

                if (cursor.getCol() > 0) {
                    Position pos{cursor.getRow(), cursor.getCol() - 1};
                    char c = buffer.getChar(pos);
                    buffer.deleteChar(pos);
                    history.pushUndo({ActionType::delete_char, pos, c});
                    cursor.moveLeft();
                }

                else if (cursor.getRow() > 0) {  
                    size_t i = buffer.getLineLength(cursor.getRow() - 1); 
                    buffer.deleteLine(cursor.getRow());
                    cursor.moveUp();
                    cursor.setCol(i);  
                }

                break;

            case 6: {
                search.clear();
                mode = Mode::searching;
                lastMatch.reset();

                break;
            }

            case 14:
                if (mode == Mode::normal && !search.empty()) {
                    Position start = lastMatch.value_or(Position{0, 0});
                    
                    auto pos = buffer.findLine(search, start);

                    lastMatch = pos;

                    if (pos.has_value()) {
                        cursor.setRow(pos->row);
                        cursor.setCol(pos->col);
                    }
                }
                
                break;

            case 0:
            case 224: {
                if (mode == Mode::searching) break;

                int key = _getch();

                switch (key) {
                    case 83:
                        if (cursor.getCol() < buffer.getLineLength(cursor.getRow())) {
                            buffer.deleteChar({cursor.getRow(), cursor.getCol()});
                        }
                        else if (cursor.getCol() >= buffer.getLineLength(cursor.getRow()) && cursor.getRow() < buffer.getText().size() - 1) {
                            buffer.deleteLine(cursor.getRow() + 1);
                        }
                        break;
                    case 72:
                        cursor.moveUp();
                        if (cursor.getCol() > buffer.getLineLength(cursor.getRow())) {
                            cursor.setCol(buffer.getLineLength(cursor.getRow()));
                        }
                        break;
                    case 80:
                        if (cursor.getRow() < buffer.getText().size() - 1) {
                            cursor.moveDown();
                            if (cursor.getCol() > buffer.getLineLength(cursor.getRow())) {
                                cursor.setCol(buffer.getLineLength(cursor.getRow()));
                            }
                        }
                        break;
                    case 75:
                        cursor.moveLeft();
                        break;
                    case 77:
                        if (cursor.getCol() < buffer.getLineLength(cursor.getRow())) {
                            cursor.moveRight();
                        }
                        break;

                }
                break;
            }
            case 13:
                if (mode == Mode::searching) {
                    Position start = lastMatch.value_or(Position{0, 0});
                    
                    auto pos = buffer.findLine(search, start);

                    lastMatch = pos;

                    if (pos.has_value()) {
                        cursor.setRow(pos->row);
                        cursor.setCol(pos->col);
                    }

                    mode = Mode::normal;
                    break;
                }

                buffer.newLine({cursor.getRow(), cursor.getCol()});
                cursor.setLineBreak();
                break;

            case 26: {
                auto action = history.undo();
        
                if (action) {
                    bool changed = applyReverse(*action);

                    if (changed) {
                        cursor.setRow(action->pos.row);

                        if (action->a == ActionType::insert) {
                            cursor.setCol(action->pos.col);
                        }

                        else {
                            cursor.setCol(action->pos.col + 1);
                        }
                    }
                }

                break;
            }

            case 25: {
                auto action = history.redo();

                if (action) {
                    bool changed = apply(*action);

                    if (changed) {
                        if (action->a == ActionType::insert) {
                            cursor.setCol(action->pos.col + 1);
                        }
                        
                        else {
                            cursor.setCol(action->pos.col);
                        }
                    }
                }

                break;
            }
            
            default:
                if (mode == Mode::searching) {
                    search += c;
                    break;
                }

                buffer.insert({cursor.getRow(), cursor.getCol()}, c);
                history.pushUndo({ActionType::insert, Position{cursor.getRow(), cursor.getCol()}, static_cast<char>(c)});
                cursor.moveRight();
                break;
        }

        

    } while (gameRunning);

}


void TextEditor::render() {
    system("cls");

    int row = 0;
    

    for (std::string line : buffer.getText()) {
        int col = 0;
        

        for (char c : line) {
            if (cursor.getCol() == col && cursor.getRow() == row) {
                if (mode == Mode::normal) {
                    std::cout << "|";
                }
                
                std::cout << c;
                col++;
            }
            else {
                std::cout << c;
                col++;
            }
        }
        if (cursor.getCol() == line.size() && cursor.getRow() == row && mode == Mode::normal) {
            std::cout << "|";
        }
        row++;
        std::cout << "\n";
    }

    if (mode == Mode::searching) {
        std::cout << "\n" << "Search: " << search << "|";
        
    }
}


bool TextEditor::apply(const Action& action) {
    if (action.a == ActionType::delete_char) {
        buffer.deleteChar(action.pos);
        return true;
    }

    else if (action.a == ActionType::insert) {
        buffer.insert(action.pos, action.c);
        return true;
    }

    return false;
}



bool TextEditor::applyReverse(const Action& action) {
    if (action.a == ActionType::insert) {
        buffer.deleteChar(action.pos);
        return true;
    }

    else if (action.a == ActionType::delete_char) {
        buffer.insert(action.pos, action.c);
        return true;
    }

    return false;
}