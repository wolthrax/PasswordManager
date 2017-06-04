#include "StringConverter.h"

StringConverter::StringConverter(){}

StringConverter::~StringConverter(){}

QString StringConverter::toQString(wchar_t *value)
{
    return QString::fromWCharArray(value);
}

wchar_t* StringConverter::toWCHAR(QString value)
{
    char *p = value.toLocal8Bit().data(); //just for proper syntax highlighting ..."
    wchar_t *wcharValue;
    // required size
    int nChars = MultiByteToWideChar(CTRY_DEFAULT, 0, p, -1, NULL, 0);
    // allocate it
    wcharValue = new wchar_t[nChars];
    MultiByteToWideChar(CTRY_DEFAULT, 0, p, -1, (LPWSTR)wcharValue, nChars);

    wchar_t *newWcharValue = wcharValue;
    delete [] wcharValue;
    return newWcharValue;
}
