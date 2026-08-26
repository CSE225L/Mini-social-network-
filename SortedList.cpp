#include "SortedList.h"

SortedList::SortedList()
{
    length = 0;
}

void SortedList::Insert(User item)
{
    int location = 0;

    while(location < length && info[location] < item)
    {
        location++;
    }

    for(int index = length; index > location; index--)
    {
        info[index] = info[index - 1];
    }

    info[location] = item;
    length++;
}

void SortedList::Print()
{
    for(int i = 0; i < length; i++)
    {
        info[i].Print();
    }
}
