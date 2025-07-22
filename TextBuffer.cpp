#include "TextBuffer.h"

// ----------------- DoublyLinkedList -----------------
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    // TODO
    head = NULL;
    tail = NULL;
    count = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    // TODO
    Node *temp = head;
    while (temp != NULL)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
    head = tail = NULL;
    count = 0;
}

// TODO: implement other methods of DoublyLinkedList

template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data)
{
    Node *newNode = new Node(data, 0, 0);
    newNode->prev = NULL;

    if (tail == NULL)
    {
        head = tail = newNode;
        count++;
        return;
    }

    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    count++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data)
{
    Node *newNode = new Node(data, 0, 0);
    if (tail == NULL)
    {
        head = tail = newNode;
        count++;
        return;
    }
    newNode->prev = tail;
    newNode->next = NULL;
    tail->next = newNode;
    tail = newNode;
    count++;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data)
{
    if (index < 0 || index > count)
    {
        throw ::out_of_range("Index is invalid!");
    }
    Node *newNode = new Node(data, 0, 0);

    if (index == 0)
    {
        insertAtHead(data);
        return;
    }
    else if (index == count)
    {
        insertAtTail(data);
        return;
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        count++;
    }
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index)
{
    if (index < 0 || index >= count)
    {
        throw ::out_of_range("Index is invalid!");
    }

    if (index == 0)
    {
        Node *del = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete del;
    }
    else if (index == count - 1)
    {
        Node *del = tail;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        delete del;
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index; ++i)
            temp = temp->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }
    count--;
}

template <typename T>
T &DoublyLinkedList<T>::get(int index) const
{
    if (index < 0 || index >= count)
    {
        throw ::out_of_range("Index is invalid!");
    }
    Node *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp->data;
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const
{
    Node *temp = head;
    for (int i = 0; i < count; i++)
    {
        if (temp->data == item)
            return i;
        temp = temp->next;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const
{
    return indexOf(item) != -1;
}

template <typename T>
void DoublyLinkedList<T>::reverse()
{
    Node *current = head;
    Node *previous = nullptr;

    tail = head;

    while (current != nullptr)
    {
        Node *next = current->next;
        current->next = previous;
        current->prev = next;
        previous = current;
        current = next;
    }
    head = previous;
}

template <typename T>
int DoublyLinkedList<T>::size() const
{
    return count;
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T &)) const
{
    string result = "[";
    for (Node *curr = head; curr != nullptr; curr = curr->next)
    {
        if (convert2str)
        {
            result += convert2str(curr->data);
        }
        else
        {
            stringstream ss;
            ss << curr->data;
            result += ss.str();
        }
        if (curr->next != nullptr)
            result += ", ";
    }
    result += "]";
    return result;
}

template <typename T>
void DoublyLinkedList<T>::split(Node *head, Node **leftHead, Node **rightHead)
{
    Node *slow = head;
    Node *fast = head->next;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    *leftHead = head;
    *rightHead = slow->next;
    slow->next = nullptr;

    if (*rightHead)
        (*rightHead)->prev = nullptr;
}

// Ở ngoài class
bool compareChar(char a, char b)
{
    if (tolower(a) == tolower(b))
        return a < b;
    return tolower(a) < tolower(b);
}

// Tổng quát cho các kiểu khác ngoài char
// merge cho các kiểu khác dùng toán tử <

// template <typename T>
// typename DoublyLinkedList<T>::Node *DoublyLinkedList<T>::merge(Node *leftHead, Node *rightHead)
// {
//     if (!leftHead)
//         return rightHead;
//     if (!rightHead)
//         return leftHead;

//     Node *head = nullptr;
//     if (leftHead->data < rightHead->data)
//     {
//         head = leftHead;
//         head->next = merge(leftHead->next, rightHead);
//         if (head->next != nullptr)
//             head->next->prev = head;
//     }
//     else
//     {
//         head = rightHead;
//         head->next = merge(leftHead, rightHead->next);
//         if (head->next != nullptr)
//         {
//             head->next->prev = head;
//         }
//     }
//     head->prev = nullptr;
//     return head;
// }
// Đặc biệt hóa cho char

template <>
DoublyLinkedList<char>::Node *DoublyLinkedList<char>::merge(Node *leftHead, Node *rightHead)
{
    if (!leftHead)
        return rightHead;
    if (!rightHead)
        return leftHead;

    Node *head = nullptr;
    if (compareChar(leftHead->data, rightHead->data))
    {
        head = leftHead;
        head->next = merge(leftHead->next, rightHead);
        if (head->next != nullptr)
            head->next->prev = head;
    }
    else
    {
        head = rightHead;
        head->next = merge(leftHead, rightHead->next);
        if (head->next != nullptr)
        {
            head->next->prev = head;
        }
    }
    head->prev = nullptr;
    return head;
}

template <>
void DoublyLinkedList<char>::mergeSort(Node *&head)
{
    if (head == nullptr || head->next == nullptr)
        return;

    Node *leftHead = nullptr;
    Node *rightHead = nullptr;

    split(head, &leftHead, &rightHead);

    mergeSort(leftHead);
    mergeSort(rightHead);

    head = merge(leftHead, rightHead);
}

template <>
void DoublyLinkedList<char>::sort()
{
    mergeSort(this->head);

    Node *current = head;
    count = 0;
    tail = nullptr;
    while (current != nullptr)
    {
        tail = current;
        current = current->next;
        count++;
    }
}
// ----------------- TextBuffer -----------------
TextBuffer::TextBuffer()
{
    // TODO
    this->cursorPos = 0;
    this->size = 1000;
    this->isModified = false;
    this->history = new HistoryManager();
    this->version = 0;
}

TextBuffer::~TextBuffer()
{
    // TODO
    delete history;
}

void TextBuffer::insert(char c)
{
    if (buffer.size() >= size)
        return;
    buffer.insertAt(cursorPos, c);
    history->addAction("insert", cursorPos, c);
    cursorPos++;
    isModified = true;
    version++;
}
void TextBuffer::deleteChar()
{
    if (cursorPos == 0 || buffer.size() == 0)
        return;
    char deleted = buffer.get(cursorPos - 1);
    buffer.deleteAt(cursorPos - 1);
    history->addAction("delete", cursorPos, deleted);
    cursorPos--;
    isModified = true;
    version++;
}
void TextBuffer::moveCursorLeft()
{
    if (cursorPos == 0)
        throw ::cursor_error();
    history->addAction("move", cursorPos, 'L');
    cursorPos--;
}
void TextBuffer::moveCursorRight()
{
    if (cursorPos == buffer.size())
        throw ::cursor_error();
    history->addAction("move", cursorPos, 'R');
    cursorPos++;
}
void TextBuffer::moveCursorTo(int index)
{
    if (index < 0 || index > buffer.size())
        throw ::out_of_range("Index is invalid!");
    // while (cursorPos > index)
    // {
    //     moveCursorLeft();
    //     cursorPos--;
    // }

    // while (cursorPos < index)
    // {
    //     moveCursorRight();
    //     cursorPos++;
    // }
    history->pushOldCursorPos(cursorPos);
    history->addAction("move", cursorPos, 'J');
    cursorPos = index;
}
string TextBuffer::getContent() const
{
    string result;
    for (int i = 0; i < buffer.size(); i++)
    {
        result += buffer.get(i);
    }
    return result;
}
int TextBuffer::getCursorPos() const
{
    return cursorPos;
}
int TextBuffer::findFirstOccurrence(char c) const
{
    return buffer.indexOf(c);
}
int *TextBuffer::findAllOccurrences(char c, int &count) const
{
    int cnt = 0;
    for (int i = 0; i < buffer.size(); i++)
    {
        if (buffer.get(i) == c)
            cnt++;
    }
    if (cnt == 0)
    {
        count = 0;
        return nullptr;
    }
    int *array = new int[cnt];
    int index = 0;
    for (int i = 0; i < buffer.size(); i++)
    {
        if (buffer.get(i) == c)
        {
            array[index] = i;
            index++;
        }
    }
    count = cnt;
    return array;
}
/*
- Ta có giá trị ascii cả các chữ hoa từ A->Z = 65->90
- giá trị ascii của các chữ thường từ a->z = 97->122
- sử dụng merge sort để độ phức tạp trong mọi trường hợp luôn là nlogn
*/
void TextBuffer::sortAscending()
{
    string oldContent = getContent();
    buffer.sort();
    history->addAction("sort", cursorPos, '\0');
    cursorPos = 0;
    isModified = true;
    version++;

    history->setPrevContentForLastAction(oldContent);
    string afterSort = getContent();
    history->setPostContentForLastAction(afterSort);
}
void TextBuffer::deleteAllOccurrences(char c)
{
    for (int i = 0; i < buffer.size();)
    {
        if (buffer.get(i) == c)
        {
            buffer.deleteAt(i);
            if (i <= cursorPos)
                cursorPos--;
        }
        else
            i++;
    }
    if (cursorPos < 0)
        cursorPos = 0;
    isModified = true;
    version++;
}
void TextBuffer::undo()
{
    if (!history->hasUndo())
        return;
    auto act = history->popUndo();
    history->pushRedo(act);

    if (act.nameAction == "insert")
    {
        buffer.deleteAt(act.cursor);
        cursorPos = act.cursor;
    }
    else if (act.nameAction == "delete")
    {
        buffer.insertAt(act.cursor - 1, act.c);
        cursorPos = act.cursor;
    }
    else if (act.nameAction == "move")
    {
        if (act.c == 'L')
            cursorPos++;
        else if (act.c == 'R')
            cursorPos--;
        else if (act.c == 'J')
        {
            cursorPos = history->popOldCursorPos();
        } // giữ nguyên
    }
    else if (act.nameAction == "sort")
    {
        while (buffer.size() > 0)
            buffer.deleteAt(buffer.size() - 1);

        for (char ch : act.prevContent)
            buffer.insertAtTail(ch);

        cursorPos = 0; // con trỏ quay về đầu
    }
}
void TextBuffer::redo()
{
    if (!history->hasRedo())
        return;
    auto act = history->popRedo();
    history->pushUndo(act);

    if (act.nameAction == "insert")
    {
        buffer.insertAt(act.cursor, act.c);
        cursorPos = act.cursor + 1;
        history->clearRedo(); // Xóa redoStack sau khi insert
    }
    else if (act.nameAction == "delete")
    {
        buffer.deleteAt(act.cursor - 1);
        cursorPos = act.cursor - 1;
        history->clearRedo(); // Xóa redoStack sau khi delete
    }
    else if (act.nameAction == "move")
    {
        if (act.c == 'L')
            cursorPos--;
        else if (act.c == 'R')
            cursorPos++;
        else if (act.c == 'J')
        {
            cursorPos = act.cursor;
        }
    }
    else if (act.nameAction == "sort")
    {
        while (buffer.size() > 0)
            buffer.deleteAt(buffer.size() - 1);

        for (char ch : act.postContent)
            buffer.insertAtTail(ch);

        cursorPos = 0;
    }
}

// TODO: implement other methods of TextBuffer

// ----------------- HistoryManager -----------------
TextBuffer::HistoryManager::HistoryManager()
{
    // TODO
}

TextBuffer::HistoryManager::~HistoryManager()
{
    // TODO
    undoStack.clear();
    redoStack.clear();
}

// TODO: implement other methods of HistoryManager

void TextBuffer::HistoryManager::setPrevContentForLastAction(const string &content)
{
    if (undoStack.empty())
        return;

    Action a = undoStack.top();
    undoStack.pop();

    a.prevContent = content;

    undoStack.push(a);
}
void TextBuffer::HistoryManager::setPostContentForLastAction(const string &content)
{
    if (undoStack.empty())
        return;

    Action a = undoStack.top();
    undoStack.pop();
    a.postContent = content;
    undoStack.push(a);
}
void TextBuffer::HistoryManager::addAction(const string &actionName, int cursorPos, char c)
{
    undoStack.push(Action(actionName, cursorPos, c));
    redoStack.clear(); // sau thao tác mới thì redo phải xoá
}

void TextBuffer::HistoryManager::printHistory() const
{
    cout << "[";
    for (int i = 0; i < undoStack.size(); ++i)
    {
        const Action &a = undoStack.get(i);
        cout << "(" << a.nameAction << ", " << a.cursor << ", ";
        if (a.c == '\0')
            cout << "\\0";
        else
            cout << a.c;
        cout << ")";
        if (i != undoStack.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

int TextBuffer::HistoryManager::size() const
{
    return undoStack.size();
}

bool TextBuffer::HistoryManager::hasUndo() const
{
    return !undoStack.empty();
}

bool TextBuffer::HistoryManager::hasRedo() const
{
    return !redoStack.empty();
}

TextBuffer::HistoryManager::Action TextBuffer::HistoryManager::popUndo()
{
    Action a = undoStack.top();
    undoStack.pop();
    return a;
}

void TextBuffer::HistoryManager::pushRedo(const Action &act)
{
    redoStack.push(act);
}

TextBuffer::HistoryManager::Action TextBuffer::HistoryManager::popRedo()
{
    Action a = redoStack.top();
    redoStack.pop();
    return a;
}

void TextBuffer::HistoryManager::pushUndo(const Action &act)
{
    undoStack.push(act);
}

void TextBuffer::HistoryManager::clearRedo()
{
    redoStack.clear();
}

// Explicit template instantiation for char, string, int, double, float, and Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;
