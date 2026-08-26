#ifndef UNSORTEDLIST_H
#define UNSORTEDLIST_H
#include "User.h"

const int MAX_BLOCKED = 30;

class UnsortedList
{
private:
    User info[MAX_BLOCKED];
    int length;

public:
    UnsortedList();

    void Insert(User);
    void Print();
};

#endif
