#include "UnsortedList.h"

UnsortedList::UnsortedList()
{
    length = 0;
}

void UnsortedList::Insert(User item)
{
    info[length] = item;
    length++;
}

void UnsortedList::Print()
{
    for(int i = 0; i < length; i++)
    {
        info[i].Print();
    }
}
