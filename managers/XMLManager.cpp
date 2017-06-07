#include "XMLManager.h"

XMLManager::XMLManager()
{

}

XMLManager::~XMLManager()
{

}

int XMLManager::save(QString filePath, QString password)
{
    QDomDocument document;
    QDomElement rootNote = document.createElement("passManager");
    rootNote.setAttribute("password", password);
    document.appendChild(rootNote);

    QDomElement groupsNode = document.createElement("groups");
    rootNote.appendChild(groupsNode);


    for(Group group : CurrentObjects::groupList)
    {
        QDomElement groupNode = document.createElement("group");
        groupNode.setAttribute("id", group.getId());

        QDomElement groupNameNode = document.createElement("name");
        groupNameNode.appendChild(document.createTextNode(group.getName()));
        groupNode.appendChild(groupNameNode);

        QDomElement groupNotesNode = document.createElement("notes");
        groupNotesNode.appendChild(document.createTextNode(group.getNotes()));
        groupNode.appendChild(groupNotesNode);

        QDomElement entriesNode = document.createElement("entries");
        groupNode.appendChild(entriesNode);



        for(Entry entry : CurrentObjects::entryList)
        {
            if(QString::compare(group.getId(), entry.getGroupid()) == 0)
            {
                QDomElement entryNode = document.createElement("entry");
                entryNode.setAttribute("id", entry.getId());
                entryNode.setAttribute("groupId", entry.getGroupid());

                QDomElement entryTitleNode = document.createElement("title");
                entryTitleNode.appendChild(document.createTextNode(entry.getTitle()));

                QDomElement entryUserNameNode = document.createElement("userName");
                entryUserNameNode.appendChild(document.createTextNode(entry.getUserName()));

                QDomElement entryPasswordNode = document.createElement("password");
                entryPasswordNode.appendChild(document.createTextNode(entry.getPassword()));

                QDomElement entryURLNode = document.createElement("URL");
                entryURLNode.appendChild(document.createTextNode(entry.getURL()));

                QDomElement entryNotesNode = document.createElement("notes");
                entryNotesNode.appendChild(document.createTextNode(entry.getNotes()));

                entryNode.appendChild(entryTitleNode);
                entryNode.appendChild(entryUserNameNode);
                entryNode.appendChild(entryPasswordNode);
                entryNode.appendChild(entryURLNode);
                entryNode.appendChild(entryNotesNode);

                entriesNode.appendChild(entryNode);
            }
        }

        groupsNode.appendChild(groupNode);
    }

    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return -1;
    }
    else
    {
        QTextStream stream(&file);
        stream << document.toString().toLocal8Bit().toBase64();
        file.close();
        return 0;
    }

}

int XMLManager::open(QString filePath, QString password)
{
    QDomDocument document;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return -1;
    }
    else
    {
        QByteArray data = QByteArray::fromBase64(file.readAll());
        if(!document.setContent(data))
        {
            return -2;
        }
        file.close();
    }

    QDomElement root = document.firstChildElement();
    if(root.attribute("password") == password)
    {
        CurrentObjects::access = true;
        CurrentObjects::password = password;
        QDomNodeList groupItems = root.elementsByTagName("group");
        CurrentObjects::groupList.clear();

        for(int i = 0; i < groupItems.size(); i++)
        {
            QDomNode groupItem = groupItems.at(i);
            if(groupItem.isElement())
            {
                QDomElement groupElement = groupItem.toElement();
                Group group;
                group.setId(groupElement.attribute("id"));
                group.setName(groupElement.firstChildElement("name").text());
                group.setNotes(groupElement.firstChildElement("notes").text());
                CurrentObjects::groupList.append(group);
            }
        }

        QDomNodeList entryItems = root.elementsByTagName("entry");
        CurrentObjects::entryList.clear();

        for(int i = 0; i < entryItems.size(); i++)
        {
            QDomNode entryItem = entryItems.at(i);
            if(entryItem.isElement())
            {
                QDomElement entryElement = entryItem.toElement();
                Entry entry;
                entry.setId(entryElement.attribute("id"));
                entry.setGroupid(entryElement.attribute("groupId"));
                entry.setTitle(entryElement.firstChildElement("title").text());
                entry.setUserName(entryElement.firstChildElement("userName").text());
                entry.setPassword(entryElement.firstChildElement("password").text());
                entry.setURL(entryElement.firstChildElement("URL").text());
                entry.setNotes(entryElement.firstChildElement("notes").text());
                CurrentObjects::entryList.append(entry);
            }
        }
    }
    else CurrentObjects::access = false;
    return 0;
}
