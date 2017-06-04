#ifndef GENERATION_H
#define GENERATION_H

#include<QString>

class Generation
{
public:
    Generation();
    virtual ~Generation();

    static QString generateID();
};

#endif // GENERATION_H
