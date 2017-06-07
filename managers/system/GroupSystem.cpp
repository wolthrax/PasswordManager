#include "GroupSystem.h"

GroupSystem::GroupSystem(){}

GroupSystem::~GroupSystem(){}

QList<LOCALGROUP_INFO_1*> GroupSystem::getWindowsGroupList()
{

    QList<LOCALGROUP_INFO_1*> groupList;

    DWORD entries_read;
    DWORD total_entries;
    LOCALGROUP_INFO_1 *buf_ptr = NULL;
    NET_API_STATUS ret_status;


    ret_status = NetLocalGroupEnum(
                                NULL,                       // локальный компьютер
                                1,                          // получаем имя группы и комментарий
                                (LPBYTE*)&buf_ptr,          // указатель на адрес буфера для данных
                                MAX_PREFERRED_LENGTH,       // длина буфера по требованию
                                &entries_read,              // указатель на количество элементов
                                &total_entries,             // указатель на нумерацию элементов
                                NULL);
    // проверяем завершение функции
    if (ret_status != NERR_Success)
    {
        NetApiBufferFree(buf_ptr);                          // освобождаем буфер для данных
        return groupList;
    }

    // записываем в коллекцию имена локальных групп и комментарии
    for (DWORD i = 0; i < entries_read; ++i)
    {
        if(&buf_ptr[i] != NULL)
            groupList.append(&buf_ptr[i]);
    }
    NetApiBufferFree(&buf_ptr);                             // освобождаем буфер для данных

    return groupList;
}

int GroupSystem::addWindowsGroup(wchar_t * nameGroup, wchar_t* commentGroup)
{
    LOCALGROUP_INFO_1 group_info;                           // информация о группе
    NET_API_STATUS ret_status;                              // код возврата из функции

    group_info.lgrpi1_name = nameGroup;                     // устанавливаем адрес имени
    group_info.lgrpi1_comment = commentGroup;               // устанавливаем комментарий

    // создаем локальную группу
    ret_status = NetLocalGroupAdd(
                                NULL,                       // имя сервера
                                1,                          // уровень входных данных
                                (LPBYTE)&group_info,        // имя группы и комментарии
                                NULL);                      // индексацию данных не используем
    // проверка выполнения функции
    NetApiBufferFree(&group_info);
    return ret_status;
}

int GroupSystem::editWindowsGroup(wchar_t * oldNameGroup, wchar_t * nameGroup, wchar_t* commentGroup)
{
    LOCALGROUP_INFO_0 group_info_0;                         // описание новой группы
    LOCALGROUP_INFO_1 group_info_1;                         // описание новой группы
    NET_API_STATUS ret_status;                              // код возврата из функции

    // устанавливаем адрес имени в структуру
    group_info_0.lgrpi0_name = nameGroup;
    group_info_1.lgrpi1_comment = commentGroup;

    // изменяем имя группы
    ret_status = NetLocalGroupSetInfo(
                                NULL,                       // имя сервера
                                oldNameGroup,               // имя группы
                                0,                          // новое имя группы
                                (LPBYTE)&group_info_0,      // новая информация о группе
                                NULL);                      // индексирования информации нет

    // изменяем коментарий группы
    group_info_1.lgrpi1_comment = commentGroup;
    ret_status = NetLocalGroupSetInfo(
                                NULL,                       // имя сервера
                                nameGroup,                  // имя группы
                                1,                          // новое имя группы
                                (LPBYTE)&group_info_1,      // новая информация о группе
                                NULL);                      // индексирования информации нет

    NetApiBufferFree(&group_info_0);
    NetApiBufferFree(&group_info_1);
    // проверяем завершение функции
    return ret_status;
}

int GroupSystem::removeWindowsGroup(wchar_t * name)
{
    NET_API_STATUS ret_status;                              //код возврата из функции
    ret_status = NetLocalGroupDel(NULL, name);              // удаляем локальную группу

    // проверяем код завершения
    return ret_status;
}

int GroupSystem::addMembers(wchar_t * groupName, wchar_t * userName)
{
    NET_API_STATUS ret_status;
    LOCALGROUP_MEMBERS_INFO_3 member;
    member.lgrmi3_domainandname = userName;
    ret_status = NetLocalGroupAddMembers(
               NULL,                                        // имя сервера
               groupName,                                   // имя группы
               3,                                           // уровень информации
               (LPBYTE)&member,                             // имя учетной записи
               1);                                          // добавляем одного члена группы
    NetApiBufferFree(&member);
    return ret_status;
}
