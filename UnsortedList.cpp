#include "UnsortedList.h"
#include <iostream>
using namespace std;

UnsortedList::UnsortedList()
{
    length = 0;
}

void UnsortedList::Insert(User item)
{
    if (length >= MAX_BLOCKED)
    {
        return;
    }
    if (ContainsID(item.getID()))
    {
        return;
    }
    info[length] = item;
    length++;
}

bool UnsortedList::ContainsID(int id)
{
    for (int i = 0; i < length; i++)
    {
        if (info[i].getID() == id)
        {
            return true;
        }
    }
    return false;
}

void UnsortedList::RemoveID(int id)
{
    int index = -1;
    for (int i = 0; i < length; i++)
    {
        if (info[i].getID() == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        return;
    }
    for (int i = index; i < length - 1; i++)
    {
        info[i] = info[i + 1];
    }
    length--;
}

void UnsortedList::Print()
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
