#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include "User.h"

const int MAX_FRIENDS = 30;

class SortedList
{
private:
    User info[MAX_FRIENDS];
    int length;

public:
    SortedList();

    void Insert(User);
    void Print();
};

#endif
