#ifndef SORTEDLIST_H_INCLUDED
#define SORTEDLIST_H_INCLUDED

#include "User.h"

const int MAX_FRIENDS = 30;

class SortedList
{
private:
    User info[MAX_FRIENDS];
    int length;

public:
    SortedList();
    void Insert(User item);
    void Print();
};

#endif
