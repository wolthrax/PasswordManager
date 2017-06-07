#ifndef USERMANAGER_H
#define USERMANAGER_H

#include<QTreeWidgetItem>
#include<QDebug>
#include<utils/Generation.h>

#include<windows.h>
#include<lm.h>

#include"entities/CurrentObjects.h"
#include"managers/converters/EntryConverter.h"
#include"utils/StringConverter.h"
#include<managers/system/UserSystem.h>

class EntryManager
{
public:
    EntryManager();
    virtual ~EntryManager();

    void addEntry(Entry);
    void removeEntry(QString);
    void editEntry(Entry);
    QList<QTreeWidgetItem*> getEntryItemList();
    QList<QTreeWidgetItem*> getEntryItemListByGroupId(QString);
    QList<QTreeWidgetItem*> getWindowsEntryItemListNyGroupName(QString);
    int addWindowsUser(USER_INFO_1);
    int editWindowsUser(USER_INFO_1, QString, QString);
    int removeWindowsUser(QString);

private:
    UserSystem userSystem;
};

#endif // USERMANAGER_H
