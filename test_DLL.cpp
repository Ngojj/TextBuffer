#include "TextBuffer.h"
#include <iostream>
using namespace std;

int main()
{
    DoublyLinkedList<char> list;
    list.insertAtHead('a');
    list.insertAtTail('b');
    list.insertAt(1, 'c'); // List: a, c, b

    cout << "List: ";
    for (int i = 0; i < list.size(); ++i)
        cout << list.get(i) << " ";
    cout << endl;

    list.deleteAt(1); // Xóa phần tử ở giữa
    cout << "After delete: ";
    for (int i = 0; i < list.size(); ++i)
        cout << list.get(i) << " ";
    cout << endl;

    return 0;
}
