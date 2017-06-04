#include "Entry.h"

Entry::Entry(){}

Entry::~Entry(){}

QString Entry::getId()
{
    return id;
}

void Entry::setId(QString id)
{
    this->id = id;
}

QString Entry::getTitle()
{
    return title;
}

void Entry::setTitle(QString title)
{
    this->title = title;
}

QString Entry::getUserName()
{
    return userName;
}

void Entry::setUserName(QString userName)
{
    this->userName = userName;
}

QString Entry::getPassword()
{
    return password;
}

void Entry::setPassword(QString password)
{
    this->password = password;
}

QString Entry::getURL()
{
    return URL;
}

void Entry::setURL(QString URL)
{
   this->URL = URL;
}

QString Entry::getNotes()
{
    return notes;
}

void Entry::setNotes(QString notes)
{
    this->notes = notes;
}

QString Entry::getGroupid()
{
    return groupid;
}

void Entry::setGroupid(QString groupid)
{
    this->groupid = groupid;
}
