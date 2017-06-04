#ifndef CURRENTOBJECTS_H
#define CURRENTOBJECTS_H

#include<QList>

#include"Group.h"
#include"Entry.h"

class CurrentObjects
{
public:
    CurrentObjects();
    virtual ~CurrentObjects();

    static QList<Entry> entryList;
    static QList<Group> groupList;

    static QList<Group> windowsGroupList;
    static QList<Entry> windowsEntryList;

    static QString password;

};

#endif // CURRENTOBJECTS_H
