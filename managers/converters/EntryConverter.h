#ifndef ENTRYCONVERTER_H
#define ENTRYCONVERTER_H

#include<QTreeWidgetItem>
#include<windows.h>
#include<lm.h>

#include"utils/StringConverter.h"
#include"entities/Entry.h"

class EntryConverter
{
public:
    EntryConverter();
    virtual ~EntryConverter();

    static QTreeWidgetItem* convertToItem(Entry);
    static QTreeWidgetItem* convertToItem(USER_INFO_1*);
};

#endif // ENTRYCONVERTER_H
