#include "GroupManager.h"

GroupManager::GroupManager(){}

GroupManager::~GroupManager(){}

void GroupManager::addGroup(Group group)
{
    group.setId(Generation::generateID());
    CurrentObjects::groupList.append(group);
}

void GroupManager::removeGroup(QString groupId)
{
    for(int i = 0; i < CurrentObjects::groupList.size(); i++)
    {
        if(QString::compare(groupId,  CurrentObjects::groupList.value(i).getId()) == 0)
        {
            for(int j = 0; j < CurrentObjects::entryList.size(); j++)
            {
                if(QString::compare(CurrentObjects::groupList.value(i).getId(),
                                    CurrentObjects::entryList.value(j).getGroupid()) == 0)
                {
                    CurrentObjects::entryList.removeAt(j);
                }
            }
            CurrentObjects::groupList.removeAt(i);
            break;
        }
    }
}

void GroupManager::editGroup(Group group)
{
    for(int i = 0; i < CurrentObjects::groupList.size(); i++)
    {
        if(QString::compare(group.getId(), CurrentObjects::groupList.value(i).getId()) == 0)
        {
            CurrentObjects::groupList.replace(i, group);
            break;
        }
    }
}

QList<QTreeWidgetItem*> GroupManager::getGroupItemList()
{
    QList<QTreeWidgetItem*> groupItemList;
    for(Group group : CurrentObjects::groupList)
    {
        QTreeWidgetItem* item = GroupConverter::convertToItem(group);
        groupItemList.append(item);
    }
    return groupItemList;
}

QList<QTreeWidgetItem*> GroupManager::getWindowsGroupItemList()
{
    QList<QTreeWidgetItem*> windowsGroupItemList;

    for(LOCALGROUP_INFO_1 *groupInfo : groupSystem.getWindowsGroupList())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, QString::fromWCharArray(groupInfo->lgrpi1_name));
        item->setIcon(0, QIcon("://icons/winGroup.png"));
        item->setToolTip(0, QString::fromWCharArray(groupInfo->lgrpi1_comment));
        windowsGroupItemList.append(item);
    }
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, "All users");
    item->setIcon(0, QIcon("://icons/winGroup.png"));
    item->setToolTip(0, "All users");
    windowsGroupItemList.insert(0, item);
    return windowsGroupItemList;
}

int GroupManager::addWindowsGroup(QString name, QString comment)
{
    return groupSystem.addWindowsGroup(StringConverter::toWCHAR(name), StringConverter::toWCHAR(comment));
}

int GroupManager::editWindowsGroup(QString oldName, QString name, QString comment)
{
    return groupSystem.editWindowsGroup(StringConverter::toWCHAR(oldName),
                                        StringConverter::toWCHAR(name),
                                        StringConverter::toWCHAR(comment));
}

int GroupManager::removeWindowsGroup(QString name)
{
    return groupSystem.removeWindowsGroup(StringConverter::toWCHAR(name));
}

int GroupManager::addMemberInWindowsGroup(QString groupName, QString userName)
{
    return groupSystem.addMembers(StringConverter::toWCHAR(groupName), StringConverter::toWCHAR(userName));
}
