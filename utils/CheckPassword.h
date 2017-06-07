#ifndef CHECKPASSWORD_H
#define CHECKPASSWORD_H

#include<QString>

class CheckPassword
{
public:
    CheckPassword();
    virtual ~CheckPassword();

    static bool check(QString, QString);
};

#endif // CHECKPASSWORD_H
