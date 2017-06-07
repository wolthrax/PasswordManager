#include "CheckPassword.h"

CheckPassword::CheckPassword(){}

CheckPassword::~CheckPassword(){}

bool CheckPassword::check(QString password, QString repeat)
{
    if(password == repeat)
        return true;
    else return false;
}
