#include "CurrentObjects.h"

CurrentObjects::CurrentObjects(){}

CurrentObjects::~CurrentObjects(){}

QList<Entry> CurrentObjects::entryList;
QList<Group> CurrentObjects::groupList;
QString CurrentObjects::password;
bool CurrentObjects::access = false;
