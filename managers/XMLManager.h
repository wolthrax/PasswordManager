#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include<QString>
#include<QtXml/QDomDocument>
#include<QtXml/QDomElement>
#include<QtXml/QDomAttr>
#include<QTextStream>
#include<QIODevice>
#include<QFile>
#include<QDebug>

#include<entities/CurrentObjects.h>

class XMLManager
{
public:
    XMLManager();
    virtual ~XMLManager();

    int save(QString, QString);
    int open(QString, QString);

};

#endif // XMLMANAGER_H
