#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include "User.h"
#include <cstddef>

struct DBNode
{
    User info;
    DBNode* leftChild;
    DBNode* rightChild;

    DBNode(User u);
};

class BST
{
private:
    DBNode* root;

    DBNode* insertNode(DBNode* node, User user);
    DBNode* searchNode(DBNode* node, User user);
    void inOrder(DBNode* node);
    void destroy(DBNode* node);

public:
    BST();
    ~BST();

    void insert(User user);
    DBNode* search(User user);
    DBNode* searchByID(int id);
    void displayAll();
};

#endif
