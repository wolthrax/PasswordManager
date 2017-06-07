#include "Messages.h"

Messages::Messages(){}

Messages::~Messages(){}

QString Messages::getMessage(int status)
{
    if(status == 5)
        return "Access dinaed.";
    else if(status == 1279)
        return "Group already exists.";
    else if(status == 1376)
        return "A group with this name does not exist.";
    else if(status == 87)
        return "Invalid parameter.";
    else if(status == 86)
        return "Invalid old password.";
    else if(status == 2223)
        return "Group already exists.";
    else if(status == -1)
        return "The file can not be written to this directory\nDo you want to change another directory?";
    else if(status == -2)
        return "Can not open file\nDo you want to change another file?";
    else if(status == -3)
        return "Invalid file\nDo you want to change another file?";
    else return "Error code: " + QString::number(status);
}
