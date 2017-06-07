#ifndef MWSSAGES_H
#define MWSSAGES_H

#include<QMessageBox>
#include<QString>
#include<QMap>

class Messages
{
public:
    Messages();
    virtual ~Messages();
    static QString getMessage(int);
};

#endif // MWSSAGES_H
