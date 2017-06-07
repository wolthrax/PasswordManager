#include "EntryConverter.h"

EntryConverter::EntryConverter(){}

EntryConverter::~EntryConverter(){}

QTreeWidgetItem* EntryConverter::convertToItem(Entry entry)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, entry.getTitle());
    item->setIcon(0, QIcon("://icons/entry.png"));
    item->setText(1, entry.getUserName());
    item->setText(2, "*********");
    item->setText(3, entry.getURL());
    item->setText(4, entry.getNotes());

    item->setText(101, entry.getGroupid());
    item->setText(100, entry.getId());
    item->setText(104, entry.getPassword());
    item->setText(105, "c");


    return item;
}

QTreeWidgetItem *EntryConverter::convertToItem(USER_INFO_1 *userInfo)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "User");
    item->setIcon(0, QIcon("://icons/user.ico"));
    item->setText(1, StringConverter::toQString(userInfo->usri1_name));
    item->setText(2, "********");
    item->setText(3, StringConverter::toQString(userInfo->usri1_home_dir));
    item->setText(4, StringConverter::toQString(userInfo->usri1_comment));
    item->setText(105, "w");
    return item;
}
