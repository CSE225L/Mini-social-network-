#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class User
{
private:
    int userID;
    string userName;
    bool vipUser;

public:
    User(int id = 0, string name = "", bool vip = false);

    bool operator<(const User& other) const;
    bool operator>(const User& other) const;
    bool operator==(const User& other) const;

    int getID() const;
    string getName() const;
    bool isVIP() const;
    int retrieveID() const;
    string retrieveName() const;
    bool checkvip() const;
    void Print() const;
};

#endif
