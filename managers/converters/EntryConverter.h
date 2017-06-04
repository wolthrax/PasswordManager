#ifndef ENTRYCONVERTER_H
#define ENTRYCONVERTER_H

#include<QTreeWidgetItem>
#include"entities/Entry.h"

class EntryConverter
{
public:
    EntryConverter();
    virtual ~EntryConverter();

    static QTreeWidgetItem* convertToItem(Entry);
};

#endif // ENTRYCONVERTER_H
