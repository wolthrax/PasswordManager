#ifndef GROUPCONVERTER_H
#define GROUPCONVERTER_H

#include<QTreeWidgetItem>
#include<entities/Group.h>

class GroupConverter
{
public:
    GroupConverter();
    virtual ~GroupConverter();

    static QTreeWidgetItem *convertToItem(Group);
};

#endif // GROUPCONVERTER_H
