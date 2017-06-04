#include "UserSystem.h"

UserSystem::UserSystem(){}

UserSystem::~UserSystem(){}

QList<USER_INFO_1*> UserSystem::getWindowsUserInfoByGroupName(wchar_t * groupName)
{
    QList<USER_INFO_1*> windowsUserList;

    // информация о членах группы
    LOCALGROUP_MEMBERS_INFO_1 *member_info = NULL;
    DWORD entries_read;                                         // прочитанное количество членов группы
    DWORD total_entries;                                        // общее количество членов группы
    NET_API_STATUS ret_status;                                  // код возврата из функции
    NetLocalGroupGetMembers(
                    NULL,                                       // имя сервера
                    groupName,                                  // имя группы
                    1,                                          // уровень информации
                    (LPBYTE*)&member_info,                      // информация о пользователях
                    MAX_PREFERRED_LENGTH,                       // читаем информацию о всех членах группы
                    &entries_read,                              // прочитанное количество членов группы
                    &total_entries,                             // полное количество членов группы
                    NULL);                                      // читаем в один прием

    for (DWORD i = 0; i < entries_read; ++i)
    {
        USER_INFO_1 *userInfo;

        ret_status = NetUserGetInfo(
                    NULL,                                       // имя сервера
                    member_info[i].lgrmi1_name,                 // имя пользователя
                    1,                                          // уровень информации 1
                    (LPBYTE*)&userInfo);                        // адрес информации о пользователе

        if(ret_status == NERR_Success)
        {
            windowsUserList.append(userInfo);
        }
//        else if(ret_status == NERR_UserNotFound)
//        {
//            windowsUserList.append(userInfo);
//        }
    }
    NetApiBufferFree(member_info); // освобождаем буфер
    return windowsUserList;
}
