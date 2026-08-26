#include "Stack.h"

Stack::Stack()
{
    top = -1;
}

void Stack::push(int value)
{
    if (top < 99)
    {
        top++;
        items[top] = value;
    }
}

int Stack::pop()
{
    if (isEmpty())
    {
        return -1;
    }

    int value = items[top];
    top--;
    return value;
}

bool Stack::isEmpty()
{
    return top == -1;
}
