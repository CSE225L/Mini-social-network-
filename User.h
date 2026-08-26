#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include<string>
using namespace std;

class USER_H_INCLUDED
{
private:
    int User_ID;
    string User_name;
    bool vipuser;

public:
    User(int = 0,string = "",bool = false);

    bool operator<(const User& other)const;
    bool operator>(const User& other)const;
    bool operator==(const User& other)const;

    string retrieveName() const;
    bool checkvip() const;
    int retrieveID() const;

};
#endif // USER_H_INCLUDED
