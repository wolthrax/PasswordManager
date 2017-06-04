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
    qDebug() << CurrentObjects::entryList.size();
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
    QList<USER_INFO_1*> userInfoList = userSystem.getWindowsUserInfoByGroupName(StringConverter::toWCHAR(groupName));
    for(USER_INFO_1* userInfo : userInfoList)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, "User");
        item->setIcon(0, QIcon("://icons/user.ico"));
        item->setText(1, StringConverter::toQString(userInfo->usri1_name));
        item->setText(2, "********");
        item->setText(3, StringConverter::toQString(userInfo->usri1_home_dir));
        item->setText(4, StringConverter::toQString(userInfo->usri1_comment));
        windowsEntryItemList.append(item);
        NetApiBufferFree(userInfo);
    }
    return windowsEntryItemList;
}
