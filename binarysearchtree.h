#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include "User.h"

struct DBNode
{
    User info;
    DBNode* leftchild;
    DBNode* rightchild;

    Node(User);
};

class BST
{
private:
    DBNode* parentnode;

    DBNode* insert(DBNode*, User);
    DBNode* search(DBNode*, User);

public:
    BST();

    void insert(User);
    DBNode* search(User);
};

#endif




#endif // BINARYSEARCHTREE_H_INCLUDED
