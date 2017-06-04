#include "EntryConverter.h"

EntryConverter::EntryConverter(){}

EntryConverter::~EntryConverter(){}

QTreeWidgetItem* EntryConverter::convertToItem(Entry entry)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, entry.getTitle());
    item->setIcon(0, QIcon("://icons/entry.png"));
    item->setText(1, entry.getUserName());
    item->setText(2, entry.getPassword());
    item->setText(3, entry.getURL());
    item->setText(4, entry.getNotes());

    item->setText(101, entry.getGroupid());
    item->setText(100, entry.getId());

    return item;
}
