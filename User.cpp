#include "User.h"

User::User(int id, string name, bool vip)
{
    userID = id;
    userName = name;
    vipUser = vip;
}

bool User::operator<(const User& other) const
{
    return userID < other.userID;
}

bool User::operator>(const User& other) const
{
    return userID > other.userID;
}

bool User::operator==(const User& other) const
{
    return userID == other.userID;
}

int User::getID() const
{
    return userID;
}

string User::getName() const
{
    return userName;
}

bool User::isVIP() const
{
    return vipUser;
}

int User::retrieveID() const
{
    return userID;
}

string User::retrieveName() const
{
    return userName;
}

bool User::checkvip() const
{
    return vipUser;
}

void User::Print() const
{
    cout << "ID: " << userID << " Name: " << userName;
    if (vipUser)
    {
        cout << " [VIP]";
    }
    cout << endl;
}
