#include "TextEditor.h"


void TextEditor::run() {
    
    bool gameRunning = true;

    FileManager file(buffer);

    file.loadFiles();

    do {

        render();

        int c = _getch();

        switch(c) {
            case 27:
                gameRunning = false;
                break;
            case 19:
                file.saveFiles();
                break;
            case 32:
                buffer.insert({cursor.getRow(), cursor.getCol()}, ' ');
                cursor.moveRight();
                break;
            case 9:
                buffer.insert({cursor.getRow(), cursor.getCol()}, '\t');
                cursor.moveRight();
                break;      
            case 8:
                if (cursor.getCol() > 0) {
                    buffer.deleteChar({cursor.getRow(), cursor.getCol() - 1});
                    cursor.moveLeft();
                }
                else if (cursor.getRow() > 0) {  
                    size_t i = buffer.getLineLength(cursor.getRow() - 1); 
                    buffer.deleteEnterLine(cursor.getRow());
                    cursor.moveUp();
                    cursor.setCol(i);  
                }

                break;
            case 0:
            case 224: {
                int arrow = _getch();

                switch (arrow) {
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
                buffer.newLine({cursor.getRow(), cursor.getCol()});
                cursor.setLineBreak();
                break;
            default:
                buffer.insert({cursor.getRow(), cursor.getCol()}, c);
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
                std::cout << "|";
                std::cout << c;
                col++;
            }
            else {
                std::cout << c;
                col++;
            }
        }
        if (cursor.getCol() == line.size() && cursor.getRow() == row) {
            std::cout << "|";
        }
        row++;
        std::cout << "\n";
    }
}