#include "SortedList.h"
#include <iostream>
using namespace std;

SortedList::SortedList()
{
    length = 0;
}

void SortedList::Insert(User item)
{
    if (length >= MAX_FRIENDS)
    {
        return;
    }

    int location = 0;
    while (location < length && info[location].getName() < item.getName())
    {
        location++;
    }

    for (int index = length; index > location; index--)
    {
        info[index] = info[index - 1];
    }

    info[location] = item;
    length++;
}

void SortedList::Print()
{
    if (length == 0)
    {
        cout << "(none)" << endl;
        return;
    }
    for (int i = 0; i < length; i++)
    {
        info[i].Print();
    }
}
