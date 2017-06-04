#ifndef USERSYSTEM_H
#define USERSYSTEM_H

#include<QList>
#include<QDebug>

#include<windows.h>
#include<lm.h>

class UserSystem
{
public:
    UserSystem();
    virtual ~UserSystem();

    QList<USER_INFO_1*> getWindowsUserInfoByGroupName(wchar_t*);
};

#endif // USERSYSTEM_H
