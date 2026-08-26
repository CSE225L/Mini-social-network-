#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

class Stack
{
private:
    int items[100];
    int top;

public:
    Stack();
    void push(int value);
    int pop();
    bool isEmpty();
};

#endif
