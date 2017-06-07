#include "EntryManager.h"

#include"entities/Entry.h"

EntryManager::EntryManager(){}

EntryManager::~EntryManager(){}

void EntryManager::addEntry(Entry entry)
{
    entry.setId(Generation::generateID());
    CurrentObjects::entryList.append(entry);
}

void EntryManager::removeEntry(QString entryId)
{
    for(int i = 0; i < CurrentObjects::entryList.size(); i++)
    {
        if(QString::compare(entryId, CurrentObjects::entryList.value(i).getId()) == 0)
        {
            CurrentObjects::entryList.removeAt(i);
            break;
        }
    }
}

void EntryManager::editEntry(Entry entry)
{
    for(int i = 0; i < CurrentObjects::entryList.size(); i++)
    {
        if(QString::compare(entry.getId(), CurrentObjects::entryList.value(i).getId()) == 0)
        {
            CurrentObjects::entryList.replace(i, entry);
            break;
        }
    }
}

QList<QTreeWidgetItem*> EntryManager::getEntryItemList()
{
    QList<QTreeWidgetItem*> entryItemList;
    for(Entry entry : CurrentObjects::entryList)
    {
        QTreeWidgetItem* item = EntryConverter::convertToItem(entry);
        entryItemList.append(item);
    }

    return entryItemList;
}

QList<QTreeWidgetItem*> EntryManager::getEntryItemListByGroupId(QString groupId)
{
    QList<QTreeWidgetItem*> entryItemList;
    for(Entry entry : CurrentObjects::entryList)
    {
        if(QString::compare(groupId, entry.getGroupid()) == 0)
        {
            QTreeWidgetItem* item = EntryConverter::convertToItem(entry);
            entryItemList.append(item);
        }
    }
    return entryItemList;
}

QList<QTreeWidgetItem *> EntryManager::getWindowsEntryItemListNyGroupName(QString groupName)
{
    QList<QTreeWidgetItem*> windowsEntryItemList;
    QList<USER_INFO_1*> userInfoList;
    if(groupName == "All users")
        userInfoList = userSystem.getAllWindowsUser();
    else userInfoList = userSystem.getWindowsUserInfoByGroupName(StringConverter::toWCHAR(groupName));
    for(USER_INFO_1* userInfo : userInfoList)
    {
        QTreeWidgetItem *item = EntryConverter::convertToItem(userInfo);
        windowsEntryItemList.append(item);
    }
    return windowsEntryItemList;
}

int EntryManager::addWindowsUser(USER_INFO_1 userInfo)
{
    return userSystem.addWindowsUser(userInfo);
}

int EntryManager::editWindowsUser(USER_INFO_1 userInfo, QString oldUserName, QString newPassword)
{
    return userSystem.editWindowsUser(userInfo, StringConverter::toWCHAR(oldUserName), StringConverter::toWCHAR(newPassword));
}

int EntryManager::removeWindowsUser(QString userName)
{
    return userSystem.removeWindowsUser(StringConverter::toWCHAR(userName));
}
