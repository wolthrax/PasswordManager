#include "Controller.h"
#include "ui_Mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->splitter1->setSizes(QList<int>() << 500 << 400);
    ui->splitter2->setSizes(QList<int>() << 200 << 700);

    ui->windowsGroupWidget->addTopLevelItems(groupManager->getWindowsGroupItemList());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   ui->splitter2->resize(ui->centralWidget->geometry().width(), ui->centralWidget->geometry().height()-20);
}

void MainWindow::on_actionAddGroup_triggered()
{
    AddGroupDialog* addGroupDialog = new AddGroupDialog();
    if (addGroupDialog->exec() == QDialog::Accepted)
    {
        Group group;
        group.setName(addGroupDialog->getName());
        group.setNotes(addGroupDialog->getNotes());
        groupManager->addGroup(group);
        refreshWidget("groupWidget");
    }
}

void MainWindow::on_actionEditGroup_triggered()
{
    AddGroupDialog* addGroupDialog = new AddGroupDialog(0,
                ui->groupWidget->currentItem()->text(0),
                ui->groupWidget->currentItem()->toolTip(0).remove(0, 6));
    if (addGroupDialog->exec() == QDialog::Accepted)
    {
        Group group;
        group.setId(ui->groupWidget->currentItem()->text(100));
        group.setName(addGroupDialog->getName());
        group.setNotes(addGroupDialog->getNotes());
        groupManager->editGroup(group);
        refreshWidget("groupWidget");
    }
}

void MainWindow::on_actionRemoveGroup_triggered()
{
    QTreeWidgetItem* item = ui->groupWidget->currentItem();
    QMessageBox *message = new QMessageBox(QMessageBox::Information, "Remove group", "Do you want to delete group " + item->text(0), QMessageBox::Yes | QMessageBox::No);
    int n = message->exec();
    delete message;
    if(n==QMessageBox::Yes)
    {
        groupManager->removeGroup(item->text(100));
        refreshWidget("groupWidget");
        refreshWidget("entryWidget");
    }
}

void MainWindow::on_actionAddEntry_triggered()
{
    AddEntryDialog* addEntryDialog = new AddEntryDialog;
    Entry entry;
    if (addEntryDialog->exec() == QDialog::Accepted)
    {
        entry.setTitle(addEntryDialog->getTitle());
        entry.setUserName(addEntryDialog->getUserName());
        entry.setPassword(addEntryDialog->getPassword());
        entry.setURL(addEntryDialog->getURL());
        entry.setNotes( addEntryDialog->getNotes());
        entry.setGroupid(ui->groupWidget->currentItem()->text(100));
        if(CheckPassword::check(addEntryDialog->getPassword(), addEntryDialog->getPasswordRepeat()))
        {
            entryManager->addEntry(entry);
            refreshWidget("entryWidget", entry.getGroupid());
            delete addEntryDialog;
        } else
        {
            QMessageBox *message = new QMessageBox(QMessageBox::Information, "Password", "Passwords do not match", QMessageBox::Ok);
            message->exec();
            delete addEntryDialog;
            delete message;
            on_actionAddEntry_triggered();
        }
    }
}

void MainWindow::on_actionCopy_password_to_clipboard_triggered()
{
    QApplication::clipboard()->setText(ui->entryWidget->currentItem()->text(104));
}

void MainWindow::on_actionRemoveEntry_triggered()
{
    QTreeWidgetItem* item = ui->entryWidget->currentItem();
    QMessageBox *message = new QMessageBox(QMessageBox::Information, "Remove entry", "Do you want to delete entry " + item->text(0), QMessageBox::Yes | QMessageBox::No);
    int n = message->exec();
    delete message;
    if(n==QMessageBox::Yes)
    {
        entryManager->removeEntry(item->text(100));
        refreshWidget("entryWidget", item->text(101));
    }
}

void MainWindow::on_actionEditEntry_triggered()
{
    AddEntryDialog* addEntryDialog = new AddEntryDialog(0,
                                                        ui->entryWidget->currentItem()->text(0),
                                                        ui->entryWidget->currentItem()->text(1),
                                                        ui->entryWidget->currentItem()->text(104),
                                                        ui->entryWidget->currentItem()->text(104),
                                                        ui->entryWidget->currentItem()->text(3),
                                                        ui->entryWidget->currentItem()->text(4));
    if (addEntryDialog->exec() == QDialog::Accepted)
    {
        Entry entry;
        entry.setTitle(addEntryDialog->getTitle());
        entry.setUserName(addEntryDialog->getUserName());
        entry.setPassword(addEntryDialog->getPassword());
        entry.setURL(addEntryDialog->getURL());
        entry.setNotes(addEntryDialog->getNotes());
        entry.setId(ui->entryWidget->currentItem()->text(100));
        entry.setGroupid(ui->groupWidget->currentItem()->text(100));
        if(CheckPassword::check(addEntryDialog->getPassword(), addEntryDialog->getPasswordRepeat()))
        {
            entryManager->editEntry(entry);
            refreshWidget("entryWidget", entry.getGroupid());
            delete addEntryDialog;
        } else
        {
            QMessageBox *message = new QMessageBox(QMessageBox::Information, "Password", "Passwords do not match", QMessageBox::Ok);
            message->exec();
            delete addEntryDialog;
            delete message;
            on_actionEditEntry_triggered();
        }
    }
}

void MainWindow::on_actionAdd_windows_group_triggered()
{
    AddGroupDialog* addGroupDialog = new AddGroupDialog();
    int status;
    if (addGroupDialog->exec() == QDialog::Accepted)
    {
        status = groupManager->addWindowsGroup(addGroupDialog->getName(), addGroupDialog->getNotes());
        refreshWidget("windowsGroupWidget");
    }
    if(status != 0)
        QMessageBox::critical (0, "Error", Messages::getMessage(status), QMessageBox::Ok);
}

void MainWindow::on_actionEdit_windows_group_triggered()
{
    AddGroupDialog* addGroupDialog = new AddGroupDialog(0,
                                                        ui->windowsGroupWidget->currentItem()->text(0),
                                                        ui->windowsGroupWidget->currentItem()->toolTip(0));
    int status;
    if (addGroupDialog->exec() == QDialog::Accepted)
    {
        status = groupManager->editWindowsGroup(ui->windowsGroupWidget->currentItem()->text(0),
                                                addGroupDialog->getName(),
                                                addGroupDialog->getNotes());
        refreshWidget("windowsGroupWidget");
    }
    if(status != 0)
        QMessageBox::critical (0, "Error", Messages::getMessage(status), QMessageBox::Ok);
}

void MainWindow::on_actionRemove_windows_group_triggered()
{
    QTreeWidgetItem* item = ui->windowsGroupWidget->currentItem();
    QMessageBox *message = new QMessageBox(QMessageBox::Information, "Remove windows group",
                                           "Do you want to remove group " + item->text(0), QMessageBox::Yes | QMessageBox::No);
    int n = message->exec();
    delete message;
    if(n == QMessageBox::Yes)
    {
        int status = groupManager->removeWindowsGroup(item->text(0));
        if(status != 0)
            QMessageBox::critical (0, "Error", Messages::getMessage(status), QMessageBox::Ok);
        refreshWidget("windowsGroupWidget");
    }
}

void MainWindow::on_actionAdd_windows_user_triggered()
{
    AddUserDialog* addUserDialog = new AddUserDialog();
    if (addUserDialog->exec() == QDialog::Accepted)
    {
        USER_INFO_1 userInfo;
        userInfo.usri1_name = StringConverter::toWCHAR(addUserDialog->getUserName());
        userInfo.usri1_comment = StringConverter::toWCHAR(addUserDialog->getNotes());
        userInfo.usri1_home_dir = StringConverter::toWCHAR("C:\\Users\\" + addUserDialog->getUserName());
        userInfo.usri1_flags = UF_SCRIPT;
        userInfo.usri1_script_path = NULL;
        userInfo.usri1_priv = USER_PRIV_USER;

        if(CheckPassword::check(addUserDialog->getPassword(), addUserDialog->getPasswordRepeat()))
        {
            userInfo.usri1_password = StringConverter::toWCHAR(addUserDialog->getPassword());
            int status = entryManager->addWindowsUser(userInfo);
            status = groupManager->addMemberInWindowsGroup(ui->windowsGroupWidget->currentItem()->text(0) ,addUserDialog->getUserName());
            if(status != 0)
                QMessageBox::critical (0, "Error", Messages::getMessage(status), QMessageBox::Ok);
            else refreshWidget("windowsEntryWidget", ui->windowsGroupWidget->currentItem()->text(0));

        }
        else
        {
            QMessageBox *message = new QMessageBox(QMessageBox::Information, "Password", "Passwords do not match", QMessageBox::Ok);
            message->exec();
            delete message;
            on_actionAdd_windows_user_triggered();
        }
    }
}

void MainWindow::on_actionEdit_windows_user_triggered()
{
    AddUserDialog* addUserDialog = new AddUserDialog(0, "",
                                                     ui->entryWidget->currentItem()->text(1),
                                                     ui->entryWidget->currentItem()->text(2),
                                                     ui->entryWidget->currentItem()->text(2),
                                                     ui->entryWidget->currentItem()->text(4));
    if (addUserDialog->exec() == QDialog::Accepted)
    {
        USER_INFO_1 userInfo;
        userInfo.usri1_name = StringConverter::toWCHAR(addUserDialog->getUserName());

        userInfo.usri1_password = StringConverter::toWCHAR(addUserDialog->getPassword());
        int status = entryManager->editWindowsUser(userInfo, ui->entryWidget->currentItem()->text(1), addUserDialog->getPasswordRepeat());
        if(status != 0)
            QMessageBox::critical (0, "Error", Messages::getMessage(status), QMessageBox::Ok);
        else refreshWidget("windowsEntryWidget", ui->windowsGroupWidget->currentItem()->text(0));
    }
}

void MainWindow::on_actionRemove_windows_user_triggered()
{
    QTreeWidgetItem* item = ui->entryWidget->currentItem();
    QMessageBox *message = new QMessageBox(QMessageBox::Information, "Remove group", "Do you want to remove user " + item->text(0), QMessageBox::Yes | QMessageBox::No);
    int n = message->exec();
    delete message;
    if(n==QMessageBox::Yes)
    {
        int status = entryManager->removeWindowsUser(item->text(1));
        if(status != 0)
            QMessageBox::critical (0, "Error", Messages::getMessage(status), QMessageBox::Ok);
        else refreshWidget("windowsEntryWidget", ui->windowsGroupWidget->currentItem()->text(0));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString openFilePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/newDatabase", tr("Pass File (*.pass)"));
    int status = 0;
    if(openFilePath != "")
    {
        bool bOk;
        QString str = QInputDialog::getText (0, "Input", "Name:", QLineEdit::Password, "", &bOk);
        if(bOk)
        {
            status = xmlManager->open(openFilePath, str);
            if(!CurrentObjects::access)
            {
                QMessageBox *message = new QMessageBox(QMessageBox::Information, "Accsess", "Access dinaed", QMessageBox::Ok);
                message->exec();
            }

        }

        if(status != 0)
        {
            int n = QMessageBox::critical (0,
                                        "Attention",
                                        Messages::getMessage(status),
                                        QMessageBox::Yes | QMessageBox::No);

            if (n == QMessageBox::Yes)
            {
                on_actionOpen_triggered();
            }
        }
        else
        {
            xmlPath = openFilePath;
            ui->actionSave->setEnabled(true);
        }
        refreshWidget("groupWidget");
        refreshWidget("entryWidget");
    }
}

void MainWindow::on_actionSave_triggered()
{

    int status = 0;
    status = xmlManager->save(xmlPath, CurrentObjects::password);
    if (status != 0)
    {
        int n = QMessageBox::warning(0,
                                    "Warning",
                                    Messages::getMessage(status),
                                    QMessageBox::Yes |
                                    QMessageBox::No,
                                    QMessageBox::Yes
                                    );
        if (n == QMessageBox::Yes)
        {
            on_actionSave_triggered();
        }
    }
}

void MainWindow::on_actionNew_triggered()
{
    QString newXMLPath = QFileDialog::getSaveFileName(this, tr("Open database"), "", tr("Pass File (*.pass)"));
    AddPassword *addPassword = new AddPassword();
    if(newXMLPath != "")
    {
        if (addPassword->exec() == QDialog::Accepted)
        {
            if(addPassword->getPassword() == addPassword->getRepeat())
            {
                CurrentObjects::entryList.clear();
                CurrentObjects::groupList.clear();
                if(xmlManager->save(newXMLPath, addPassword->getPassword()) == 0)
                {
                    CurrentObjects::password = addPassword->getPassword();
                    xmlPath = newXMLPath;
                    xmlManager->open(xmlPath, CurrentObjects::password);
                    ui->actionSave->setEnabled(true);
                    refreshWidget("groupWidget");
                    refreshWidget("entryWidget");
                }
            }
            else
            {
                QMessageBox *message = new QMessageBox(QMessageBox::Information, "Password", "Passwords do not match", QMessageBox::Ok);
                message->exec();
            }
        }
    }
}

void MainWindow::refreshWidget(QString widgetName, QString groupId)
{
    if(QString::compare(widgetName, "groupWidget") == 0)
    {
        ui->groupWidget->clear();
        ui->groupWidget->addTopLevelItems(groupManager->getGroupItemList());
    }
    else if(QString::compare(widgetName, "entryWidget") == 0)
    {
        ui->entryWidget->clear();
        ui->entryWidget->addTopLevelItems(entryManager->getEntryItemListByGroupId(groupId));
    }
    else if(QString::compare(widgetName, "windowsEntryWidget") == 0)
    {
        ui->entryWidget->clear();
        ui->entryWidget->addTopLevelItems(entryManager->getWindowsEntryItemListNyGroupName(groupId));
    }else if(QString::compare(widgetName, "windowsGroupWidget") == 0)
    {
        ui->windowsGroupWidget->clear();
        ui->windowsGroupWidget->addTopLevelItems(groupManager->getWindowsGroupItemList());
    }
}

void MainWindow::on_groupWidget_itemSelectionChanged()
{
    if(ui->groupWidget->selectedItems().isEmpty())
    {
        ui->actionAddEntry->setEnabled(false);
        ui->actionEditGroup->setEnabled(false);
        ui->actionRemoveGroup->setEnabled(false);
    } else
    {
        ui->actionAddEntry->setEnabled(true);
        ui->actionEditGroup->setEnabled(true);
        ui->actionRemoveGroup->setEnabled(true);
    }
}

void MainWindow::on_entryWidget_itemSelectionChanged()
{
    if(ui->entryWidget->selectedItems().isEmpty())
    {
        ui->actionEditEntry->setEnabled(false);
        ui->actionRemoveEntry->setEnabled(false);
        ui->actionCopy_password_to_clipboard->setEnabled(false);
        ui->actionEdit_windows_user->setEnabled(false);
        ui->actionRemove_windows_user->setEnabled(false);
    }
    else
    {
        if(ui->entryWidget->currentItem()->text(105) == "c")
        {
            ui->actionEditEntry->setEnabled(true);
            ui->actionRemoveEntry->setEnabled(true);
            ui->actionCopy_password_to_clipboard->setEnabled(true);
        }
        if(ui->entryWidget->currentItem()->text(105) == "w")
        {
            ui->actionEdit_windows_user->setEnabled(true);
            ui->actionRemove_windows_user->setEnabled(true);
        }
    }
}

void MainWindow::on_windowsGroupWidget_itemSelectionChanged()
{
    if(ui->windowsGroupWidget->selectedItems().isEmpty())
    {
        ui->actionAdd_windows_user->setEnabled(false);
        ui->actionEdit_windows_group->setEnabled(false);
        ui->actionRemove_windows_group->setEnabled(false);
    } else
    {
        ui->actionAdd_windows_user->setEnabled(true);
        ui->actionEdit_windows_group->setEnabled(true);
        ui->actionRemove_windows_group->setEnabled(true);
    }
}

void MainWindow::on_groupWidget_itemClicked(QTreeWidgetItem *item)
{
    refreshWidget("entryWidget", item->text(100));
}

void MainWindow::on_windowsGroupWidget_itemClicked(QTreeWidgetItem *item)
{
    refreshWidget("windowsEntryWidget", item->text(0));
}
