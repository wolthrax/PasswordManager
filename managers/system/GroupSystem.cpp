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
    if (ret_status == NERR_Success)
    {
        return 0;
    } else if (ret_status == ERROR_ACCESS_DENIED)
    {
        return -1;
    } else if (ret_status == ERROR_ALIAS_EXISTS)
    {
        return -2;
    } else return -3;
}

int GroupSystem::editWindowsGroup(wchar_t * oldNameGroup, wchar_t * nameGroup, wchar_t* commentGroup)
{
    LOCALGROUP_INFO_1 group_info_0;                         // описание новой группы
    LOCALGROUP_INFO_1 group_info_1;                         // описание новой группы
    NET_API_STATUS ret_status;                              // код возврата из функции

    qDebug() << QString::fromWCharArray(oldNameGroup) << QString::fromWCharArray(nameGroup) << QString::fromWCharArray(commentGroup);

    // устанавливаем адрес имени в структуру
    group_info_0.lgrpi1_name = nameGroup;
    group_info_1.lgrpi1_name = nameGroup;
    group_info_1.lgrpi1_comment = commentGroup;

    // изменяем имя группы
    ret_status = NetLocalGroupSetInfo(
                                NULL,                       // имя сервера
                                oldNameGroup,               // имя группы
                                0,                          // новое имя группы
                                (LPBYTE)&group_info_0,      // новая информация о группе
                                NULL);                      // индексирования информации нет

    // изменяем соментарий группы
    ret_status = NetLocalGroupSetInfo(
                                NULL,                       // имя сервера
                                nameGroup,                  // имя группы
                                1,                          // новое имя группы
                                (LPBYTE)&group_info_1,      // новая информация о группе
                                NULL);                      // индексирования информации нет

    NetApiBufferFree(&group_info_0);
    NetApiBufferFree(&group_info_1);
    // проверяем завершение функции
    if (ret_status == NERR_Success)
    {
        return 0;
    } else if (ret_status == ERROR_ACCESS_DENIED)
    {
        return -1;
    } else if (ret_status == ERROR_NO_SUCH_ALIAS)
    {
        return -2;
    } else return -3;
}

int GroupSystem::removeWindowsGroup(wchar_t * name)
{
    NET_API_STATUS ret_status;                              //код возврата из функции
    ret_status = NetLocalGroupDel(NULL, name);              // удаляем локальную группу

    qDebug() << QString::fromWCharArray(name);
    // проверяем код завершения

    if (ret_status == NERR_Success)
    {
        return 0;
    } else if (ret_status == ERROR_ACCESS_DENIED)
    {
        return -1;
    } else if (ret_status == ERROR_NO_SUCH_ALIAS)
    {
        return -2;
    } else return -3;
}
