#include "GroupConverter.h"

GroupConverter::GroupConverter(){}

GroupConverter::~GroupConverter(){}

QTreeWidgetItem* GroupConverter::convertToItem(Group group)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, group.getName());
    item->setToolTip(0, "Notes: \n" + group.getNotes());
    item->setIcon(0, QIcon("://icons/group.png"));
    item->setText(100, group.getId());
    return item;
}
