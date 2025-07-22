#include "TextBuffer.h"
#include <iostream>
using namespace std;

int main()
{
    TextBuffer buffer;
    buffer.insert('A');
    cout << "buffer after insert A: " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.insert('B');
    cout << "buffer after insert B: " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.insert('C');
    cout << "buffer after insert C:  " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.moveCursorLeft();

    cout << "cursor after remove left: " << buffer.getCursorPos() << endl;

    buffer.insert('X');
    cout << "buffer after insert X: " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.moveCursorRight();
    cout << "cursor after remove right: " << buffer.getCursorPos() << endl;

    buffer.deleteChar();
    cout << "buffer after deleteChar: " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.undo();
    cout << "undo (khoi phuc ki tu C) : " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.undo();
    cout << "undo (move cursor left) : " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.undo();
    cout << "undo (delete X) : " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.redo();
    cout << "redo (insert X) : " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.redo();
    cout << "redo (move cursor right) : " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    buffer.redo();
    cout << "redo (delete C) : " << buffer.getContent() << " | cursor: " << buffer.getCursorPos() << endl;

    return 0;
}
