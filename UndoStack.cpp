#include "UndoStack.h"
#include <iostream>
using namespace std;

UndoStack::UndoStack()
{
    top = -1;
}

bool UndoStack::isEmpty() const
{
    return top == -1;
}

bool UndoStack::isFull() const
{
    return top == MAX_UNDO - 1;
}

void UndoStack::push(Action a)
{
    if (isFull())
    {
        cout << "Undo history is full." << endl;
        return;
    }
    top++;
    items[top] = a;
}

Action UndoStack::pop()
{
    Action empty;
    empty.type = 0;
    empty.userA = 0;
    empty.userB = 0;

    if (isEmpty())
    {
        cout << "Nothing to undo." << endl;
        return empty;
    }

    Action a = items[top];
    top--;
    return a;
}
