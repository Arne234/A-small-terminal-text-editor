#include "TextEditor/TextEditor.h"


int main() {

    Buffer b;
    Cursor c;
    History h;
    TextEditor editor(b, c, h);


    editor.run();


    return 0;
}
