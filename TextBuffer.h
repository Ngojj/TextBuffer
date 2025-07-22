#ifndef __TEXT_BUFFER_H__
#define __TEXT_BUFFER_H__

#include "main.h"

template <typename T>
class DoublyLinkedList
{
    // TODO: may provide some attributes
    /* ========begin my implementation==========*/
public:
    class Node;

protected:
    Node *head;
    Node *tail;
    int count;
    /* ========end my implementation==========*/
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertAtHead(T data);
    void insertAtTail(T data);
    void insertAt(int index, T data);
    void deleteAt(int index);
    T &get(int index) const;
    int indexOf(T item) const;
    bool contains(T item) const;
    int size() const;
    void reverse();
    string toString(string (*convert2str)(T &) = 0) const;
    /* cac phuong thuc them ho tro*/
    void split(Node *head, Node **leftHead, Node **rightHead);
    // bool compareChar(char a, char b);
    Node *merge(Node *left, Node *right);
    void mergeSort(Node *&head);
    void sort();
    /* ========begin my implementation==========*/
public:
    class Node
    {
    public:
        T data;
        Node *prev;
        Node *next;
        friend class DoublyLinkedList<T>;

    public:
        Node(T data, Node *prev, Node *next)
        {
            this->data = data;
            this->prev = prev;
            this->next = next;
        }
        Node(Node *prev = 0, Node *next = 0)
        {
            this->prev = prev;
            this->next = next;
        }
    };
    /* ========end my implementation==========*/
};

template <typename T>
class stack
{
protected:
    DoublyLinkedList<T> List;

public:
    stack() {}
    void push(T data)
    {
        List.insertAtTail(data);
    }
    void pop()
    {
        if (List.size() == 0)
            return;
        List.deleteAt(List.size() - 1);
    }
    T top() const
    {
        return List.get(List.size() - 1);
    }
    int size() const
    {
        return List.size();
    }
    T get(int index) const
    {
        return List.get(index);
    }

    bool empty() const
    {
        return List.size() == 0;
    }
    void clear()
    {
        while (!empty())
        {
            pop();
        }
    }
};

class TextBuffer
{
public:
    DoublyLinkedList<char> buffer; // buffer la mot dlinkedlist
    int cursorPos;

    // TODO: may provide some attributes
    int size;
    bool isModified;
    int version;
    class HistoryManager;
    HistoryManager *history;

public:
    TextBuffer();
    ~TextBuffer();

    void insert(char c);
    void deleteChar();
    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorTo(int index);
    string getContent() const;
    int getCursorPos() const;
    int findFirstOccurrence(char c) const;
    int *findAllOccurrences(char c, int &count) const;
    void sortAscending();
    void deleteAllOccurrences(char c);
    void undo();
    void redo();

public:
    class HistoryManager
    {
        // TODO: may provide some attributes
    private:
        // int count; // so luong thao tac
        struct Action
        {
            int cursor;
            string nameAction;
            char c;
            string prevContent;
            string postContent;
            int prevCursor; // vị trí con trỏ trước khi move
            int postCursor; // vị trí con trỏ sau khi move
            // Action() : cursor(0), nameAction(""), c('\0'), prevContent("") {}
            Action(string nameAction = "", int cursor = 0, char c = '\0') : nameAction(nameAction), cursor(cursor), c(c) {}
            Action(string nameAction, int cursor, char c, const string &prev, const string &post, int prevCursor, int postCursor)
                : nameAction(nameAction), cursor(cursor), c(c), prevContent(prev), postContent(post), prevCursor(prevCursor), postCursor(postCursor) {}
        };
        stack<Action> undoStack;
        stack<Action> redoStack;
        stack<int> jumpCursorStack;

    public:
        HistoryManager();
        ~HistoryManager();

        void addAction(const string &actionName, int cursorPos, char c);
        void printHistory() const;
        int size() const;
        /* them cac phuong thuc ho tro*/
        bool hasUndo() const;
        bool hasRedo() const;

        Action popUndo();
        void pushRedo(const Action &act);
        Action popRedo();
        void pushUndo(const Action &act);
        void clearRedo();
        /*ham bo tro undo sort*/
        void setPrevContentForLastAction(const string &content);
        void setPostContentForLastAction(const string &content);
        /*ham bo tro cho undo/redo 'J'*/
        void pushOldCursorPos(int pos)
        {
            jumpCursorStack.push(pos);
        }

        int popOldCursorPos()
        {
            int old = jumpCursorStack.top();
            jumpCursorStack.pop();
            return old;
        }
    };
};

#endif // __TEXT_BUFFER_H__
