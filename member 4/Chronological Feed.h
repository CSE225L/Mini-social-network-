#ifndef CHRONOLOGICAL_FEED_H_INCLUDED
#define CHRONOLOGICAL_FEED_H_INCLUDED
#include <iostream>
#include "post.h"
using namespace std;

template <class T>
class StackNode
{
public:
    T data;
    StackNode<T>* next;
    StackNode(T value) : data(value), next(nullptr) {}
};

template <class T>
class LinkedStack
{
private:
    StackNode<T>* top;
    int size;

public:
    LinkedStack() : top(nullptr),size(0) {}

    ~LinkedStack()
    {
        while (!isEmpty()) pop();
    }

    void push(T value)
    {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = top;
        top = newNode;
        size++;
    }

    bool pop()
    {
        if (isEmpty()) return false;
        StackNode<T>* temp = top;
        top = top->next;
        delete temp;
        size--;
        return true;
    }

    T peek() const
    {
        return top->data;
    }
    bool isEmpty() const
    {
        return top == nullptr;
    }
    int getSize() const
    {
        return size;
    }

    void displayAll() const
    {
        StackNode<T>* current = top;
        if (!current)
        {
            cout << "  (No posts yet)\n";
            return;
        }
        while (current)
        {
            current->data.display();
            current = current->next;
        }
    }
};

class ChronologicalFeed
{
private:
    LinkedStack<Post> feedStack;

public:
    void newPost(Post p)
    {
        feedStack.push(p);
    }

    void showFeed() const
    {
        cout << "\n CHRONOLOGICAL FEED (Newest First) \n";
        feedStack.displayAll();
    }

    int postCount() const
    {
        return feedStack.getSize();
    }
};


#endif // CHRONOLOGICAL_FEED_H_INCLUDED
