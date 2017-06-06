#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include<QTreeWidgetItem>
#include<QDebug>

#include<windows.h>
#include<lm.h>

#include"entities/Group.h"
#include"entities/CurrentObjects.h"
#include"utils/Generation.h"
#include"managers/converters/GroupConverter.h"
#include"managers/system/GroupSystem.h"
#include"utils/StringConverter.h"

class GroupManager
{
public:
    GroupManager();
    virtual ~GroupManager();

    void addGroup(Group);
    void removeGroup(QString);
    void editGroup(Group);
    QList<QTreeWidgetItem*> getGroupItemList();
    QList<QTreeWidgetItem*> getWindowsGroupItemList();
    int addWindowsGroup(QString, QString);
    int editWindowsGroup(QString, QString, QString);
    int removeWindowsGroup(QString);
    int addMemberInWindowsGroup(QString, QString);

private:
    GroupSystem groupSystem;

};

#endif // GROUPMANAGER_H
