#include "binarysearchtree.h"

DBNode::DBNode(User u)
{
    info = u;
    leftchild = NULL;
    rightchild = NULL;
}

binaryseachtree::binaryseachtree()
{
    parentnode = NULL;
}

DBNode* binarysearchtree::insert(Node* parentnode, User user)
{
    if (parentnode == NULL)
        return new DBNode(user);

    if (user < parentnode->info)
        parentnode->left = insert(parentnode->left, user);

    else if (user > parentnode->info)
        parentnode->right = insert(parentnode->right, user);

    return parentnode;
}

void binarysearchtree::insert(User user)
{
    parentnode = insert(parentnode, user);
}

DBNode* binarysearchtree::search(Node* parentnode, User user)
{
    if (parentnode == NULL || user == parentnode->info)
        return parentnode;

    if (user < parentnode->info)
        return search(parentnode->left, user);

    return search(parentnode->right, user);
}

Node* binarysearchtree::search(User user)
{
    return search(parentnode, user);
}
