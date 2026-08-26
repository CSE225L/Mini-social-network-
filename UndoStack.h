#ifndef UNDOSTACK_H_INCLUDED
#define UNDOSTACK_H_INCLUDED

#include <string>
#include "Post.h"
using namespace std;

const int MAX_UNDO = 100;

const int ACTION_SEND_REQUEST = 1;
const int ACTION_ACCEPT_FRIEND = 2;
const int ACTION_CREATE_POST = 3;
const int ACTION_DELETE_POST = 4;
const int ACTION_BLOCK_USER = 5;

struct Action
{
    int type;
    int userA;
    int userB;
    Post savedPost;
};

class UndoStack
{
private:
    Action items[MAX_UNDO];
    int top;

public:
    UndoStack();
    bool isEmpty() const;
    bool isFull() const;
    void push(Action a);
    Action pop();
};

#endif
