#ifndef CHRONOLOGICAL_FEED_H_INCLUDED
#define CHRONOLOGICAL_FEED_H_INCLUDED

#include <iostream>
#include "Post.h"
#include <cstddef>
using namespace std;

template <class T>
class StackNode
{
public:
    T data;
    StackNode<T>* next;

    StackNode(T value)
    {
        data = value;
        next = NULL;
    }
};

template <class T>
class LinkedStack
{
private:
    StackNode<T>* top;
    int size;

public:
    LinkedStack()
    {
        top = NULL;
        size = 0;
    }

    ~LinkedStack()
    {
        while (!isEmpty())
        {
            pop();
        }
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
        if (isEmpty())
        {
            return false;
        }
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
        return top == NULL;
    }

    int getSize() const
    {
        return size;
    }

    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void displayAll() const
    {
        StackNode<T>* current = top;
        if (current == NULL)
        {
            cout << "  (No posts yet)" << endl;
            return;
        }
        while (current != NULL)
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

    void clear()
    {
        feedStack.clear();
    }

    void showFeed() const
    {
        cout << endl << "CHRONOLOGICAL FEED (Newest First)" << endl;
        feedStack.displayAll();
    }

    int postCount() const
    {
        return feedStack.getSize();
    }
};

#endif
