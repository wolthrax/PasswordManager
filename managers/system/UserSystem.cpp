#include "UserSystem.h"

UserSystem::UserSystem(){}

UserSystem::~UserSystem(){}

QList<USER_INFO_1 *> UserSystem::getAllWindowsUser()
{
    QList<USER_INFO_1*> userList;
    USER_INFO_1 *userInfo;                                      // информация о пользователе
    DWORD entries_read;                                         // количество прочитанных пользователей
    DWORD total_entries;                                        // общее количество пользователей
    NET_API_STATUS ret_status;                                  // код возврата из функции

    ret_status = NetUserEnum(
                    NULL,                                        // имя сервера
                    1,                                           // узнаем только имена пользователей
                    FILTER_NORMAL_ACCOUNT,                       // перечисляем пользователей, зарегистрированных на компьютере
                    (LPBYTE*)&userInfo,                          // адрес информации о пользователях
                    MAX_PREFERRED_LENGTH,                        // перечисляем всех пользователей
                    &entries_read,                               // количество прочитанных пользователей
                    &total_entries,                              // общее количество пользователей
                    NULL);                                       // индексации нет

    if(ret_status == NERR_Success)
    {
        for (DWORD i = 0; i < entries_read; ++i)
        {
           userList.append(&userInfo[i]);
           // qDebug() << QString::fromWCharArray(userInfo[i]);
        }
        NetApiBufferFree(&userList); // освобождаем буфер
    }
    return userList;
}

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

int UserSystem::addWindowsUser(USER_INFO_1 userInfo)
{
    NET_API_STATUS ret_status;
    ret_status = NetUserAdd(
                        NULL,                                   // имя сервера
                        1,                                      // уровень информации 1
                        (LPBYTE)&userInfo,                      // адрес информации о пользователе
                        NULL);                                  // индексирования в структуре данных нет
    NetApiBufferFree(&userInfo);
    return ret_status;
}

int UserSystem::editWindowsUser(USER_INFO_1 userUnfo, wchar_t *oldUserName, wchar_t *newPassword)
{
    wchar_t *newUserName = userUnfo.usri1_name;
    wchar_t *oldPassword = userUnfo.usri1_password;
    NET_API_STATUS ret_status;
    ret_status = NetUserSetInfo(
                        NULL,                                   // имя сервера
                        oldUserName,                            // имя пользователя
                        0,                                      // изменяем имя пользователя
                        (LPBYTE)&userUnfo,                      // адрес информации о пользователе
                        NULL);                                  // нет индексации

    ret_status = NetUserChangePassword(
                        NULL,                                   // имя домена
                        newUserName,                            // имя пользователя
                        oldPassword,                            // старый пароль
                        newPassword);                           // новый пароль
        NetApiBufferFree(&userUnfo);
    return ret_status;
}

int UserSystem::removeWindowsUser(wchar_t *userName)
{
    NET_API_STATUS ret_status;
    ret_status = NetUserDel(
        NULL,                                                   // имя домена
        (LPWSTR)userName);                                      // имя пользователя
    return ret_status;
}
