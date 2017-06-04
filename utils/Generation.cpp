#include "Generation.h"

Generation::Generation(){}

Generation::~Generation(){}

QString Generation::generateID()
{
    unsigned long long r30 = RAND_MAX * rand() + rand();
    unsigned long long s30 = RAND_MAX * rand() + rand();
    unsigned long long t4  = rand() & 0xf;

    unsigned long long res = (r30 << 34) + (s30 << 4) + t4;
    return QString::number(res);
}
