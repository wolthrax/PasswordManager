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

    static QString password;
    static bool access;

};

#endif // CURRENTOBJECTS_H
