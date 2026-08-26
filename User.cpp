#include "User.h"

User:User(int i,string n, bool v)
{
    User_ID = i;
    User_name = n;
    vipuser = v;
}
bool User::checkvip()const;
{
    return vipuser;
}
int User::retrieveID() const
{
    return User_ID;
}
string User::retrieveName() const
{
    return User_ID;
}
bool User::operator==(const User& other)const
{
    return User_ID == other.User_ID;
}
bool User::operator<(const User& other)const
{
    return User_ID < other.User_ID;
}
bool User::operator>(const User& other)const
{
    return User_ID > other.User_ID;
}

