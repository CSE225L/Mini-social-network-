#ifndef STACK_H
#define STACK_H

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
