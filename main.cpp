#include "TextEditor/TextEditor.h"


int main() {

    Buffer b;
    Cursor c;
    TextEditor editor(b, c);


    editor.run();


    return 0;
}