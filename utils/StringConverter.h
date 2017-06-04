#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include<QString>
#include<windows.h>

class StringConverter
{
public:
    StringConverter();
    virtual ~ StringConverter();

    static QString toQString(wchar_t*);
    static wchar_t* toWCHAR(QString);


};

#endif // STRINGCONVERTER_H
