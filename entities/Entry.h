#ifndef USER_H
#define USER_H

#include<QString>

class Entry
{
public:
    Entry();
    virtual ~Entry();

    QString getId();
    void setId(QString);

    QString getPassword();
    void setPassword(QString);

    QString getTitle();
    void setTitle(QString);

    QString getUserName();
    void setUserName(QString);

    QString getURL();
    void setURL(QString);

    QString getNotes();
    void setNotes(QString);

    QString getGroupid();
    void setGroupid(QString);

private:
    QString id;
    QString title;
    QString userName;
    QString password;
    QString URL;
    QString notes;
    QString groupid;
};

#endif // USER_H
