#include "BST.h"
#include <iostream>
using namespace std;

DBNode::DBNode(User u)
{
    info = u;
    leftChild = NULL;
    rightChild = NULL;
}

BST::BST()
{
    root = NULL;
}

BST::~BST()
{
    destroy(root);
}

void BST::destroy(DBNode* node)
{
    if (node == NULL)
    {
        return;
    }
    destroy(node->leftChild);
    destroy(node->rightChild);
    delete node;
}

DBNode* BST::insertNode(DBNode* node, User user)
{
    if (node == NULL)
    {
        return new DBNode(user);
    }

    if (user < node->info)
    {
        node->leftChild = insertNode(node->leftChild, user);
    }
    else if (user > node->info)
    {
        node->rightChild = insertNode(node->rightChild, user);
    }

    return node;
}

void BST::insert(User user)
{
    root = insertNode(root, user);
}

DBNode* BST::searchNode(DBNode* node, User user)
{
    if (node == NULL || user == node->info)
    {
        return node;
    }

    if (user < node->info)
    {
        return searchNode(node->leftChild, user);
    }

    return searchNode(node->rightChild, user);
}

DBNode* BST::search(User user)
{
    return searchNode(root, user);
}

DBNode* BST::searchByID(int id)
{
    User temp(id, "");
    return search(temp);
}

void BST::inOrder(DBNode* node)
{
    if (node == NULL)
    {
        return;
    }
    inOrder(node->leftChild);
    node->info.Print();
    inOrder(node->rightChild);
}

void BST::displayAll()
{
    if (root == NULL)
    {
        cout << "No users registered." << endl;
        return;
    }
    inOrder(root);
}
