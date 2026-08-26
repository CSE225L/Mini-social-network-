#ifndef UNSORTEDLIST_H_INCLUDED
#define UNSORTEDLIST_H_INCLUDED

#include "User.h"

const int MAX_BLOCKED = 30;

class UnsortedList
{
private:
    User info[MAX_BLOCKED];
    int length;

public:
    UnsortedList();
    void Insert(User item);
    bool ContainsID(int id);
    void RemoveID(int id);
    void Print();
};

#endif
