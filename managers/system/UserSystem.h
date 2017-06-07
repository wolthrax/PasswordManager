#ifndef USERSYSTEM_H
#define USERSYSTEM_H

#include<QList>
#include<QDebug>

#include<windows.h>
#include<lm.h>

#include"managers/system/GroupSystem.h"

class UserSystem
{
public:
    UserSystem();
    virtual ~UserSystem();

    QList<USER_INFO_1*> getAllWindowsUser();
    QList<USER_INFO_1*> getWindowsUserInfoByGroupName(wchar_t*);
    int addWindowsUser(USER_INFO_1);
    int editWindowsUser(USER_INFO_1, wchar_t*, wchar_t*);
    int removeWindowsUser(wchar_t*);
};

#endif // USERSYSTEM_H
