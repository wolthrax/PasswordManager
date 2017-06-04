#ifndef GROUP_H
#define GROUP_H

#include<QString>

class Group
{
public:
    Group();
    virtual ~Group();

    QString getId();
    void setId(QString);

    QString getName();
    void setName(QString);

    QString getNotes();
    void setNotes(QString);

private:
    QString id;
    QString name;
    QString notes;
};

#endif // GROUP_H
