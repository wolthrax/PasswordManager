#ifndef GROUPSYSTEM_H
#define GROUPSYSTEM_H

#include<QList>
#include<QDebug>

#include<windows.h>
#include<lm.h>

class GroupSystem
{
public:
    GroupSystem();
    virtual ~GroupSystem();

    QList<LOCALGROUP_INFO_1*> getWindowsGroupList();
    int addWindowsGroup(wchar_t*, wchar_t*);
    int editWindowsGroup(wchar_t*, wchar_t*, wchar_t*);
    int removeWindowsGroup(wchar_t*);
    int addMembers(wchar_t*, wchar_t*);
};

#endif // GROUPSYSTEM_H
