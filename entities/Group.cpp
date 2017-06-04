#include "Group.h"

Group::Group(){}

Group::~Group(){}


QString Group::getId()
{
    return id;
}

void Group::setId(QString id)
{
    this->id = id;
}

QString Group::getName()
{
    return name;
}

void Group::setName(QString name)
{
   this->name = name;
}

QString Group::getNotes()
{
    return notes;
}

void Group::setNotes(QString notes)
{
    this->notes = notes;
}
