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

void MainWindow::on_actionAddEntry_triggered()
{
    AddEntryDialog* addEntryDialog = new AddEntryDialog;
    if (addEntryDialog->exec() == QDialog::Accepted)
    {
        Entry entry;
        entry.setTitle(addEntryDialog->getTitle());
        entry.setUserName(addEntryDialog->getUserName());
        entry.setPassword(addEntryDialog->getPassword());
        entry.setURL(addEntryDialog->getURL());
        entry.setNotes( addEntryDialog->getNotes());
        entry.setGroupid(ui->groupWidget->currentItem()->text(100));
        entryManager->addEntry(entry);
        refreshWidget("entryWidget", entry.getGroupid());
    }
    delete addEntryDialog;
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

void MainWindow::on_entryWidget_itemSelectionChanged()
{
    if(ui->entryWidget->selectedItems().isEmpty())
    {
        ui->actionEditEntry->setEnabled(false);
        ui->actionRemoveEntry->setEnabled(false);
    } else
    {
        ui->actionEditEntry->setEnabled(true);
        ui->actionRemoveEntry->setEnabled(true);
    }
}

void MainWindow::on_actionEditEntry_triggered()
{
    AddEntryDialog* addEntryDialog = new AddEntryDialog(0,
                                                        ui->entryWidget->currentItem()->text(0),
                                                        ui->entryWidget->currentItem()->text(1),
                                                        ui->entryWidget->currentItem()->text(2),
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
        entryManager->editEntry(entry);
        refreshWidget("entryWidget", entry.getGroupid());
    }
    delete addEntryDialog;
}

void MainWindow::on_groupWidget_itemClicked(QTreeWidgetItem *item)
{
    refreshWidget("entryWidget", item->text(100));
}

void MainWindow::on_actionSave_triggered()
{
    QString newXMLPath;
    int status = 0;
    if(QString::compare(xmlPath, "") == 0)
    {
        newXMLPath = QFileDialog::getSaveFileName(this, tr("Open Image"), "/home/newDatabase", tr("XML File (*.xml)"));
        qDebug() << newXMLPath;
        if(newXMLPath != "")
        {
            status = xmlManager->save(newXMLPath);
        }
        if(status == 0)
        {
            xmlPath = newXMLPath;
        }
    }
    else
    {
        status = xmlManager->save(xmlPath);
    }

    if(status != 0)
    {
        int n = QMessageBox::warning(0,
                                    "Warning",
                                    "The file can not be written to this directory"
                                    "\nDo you want to change another directory?",
                                    QMessageBox::Yes |
                                    QMessageBox::No,
                                    QMessageBox::Yes
                                    );
        if (n == QMessageBox::Yes) {
            on_actionSave_triggered();
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString openFilePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/newDatabase", tr("XML File (*.xml)"));
    int status = 0;

    if(xmlPath == "")
    {
        status = xmlManager->open(openFilePath);
    }
    if(status == -1)
    {
        int n = QMessageBox::critical (0,
                                    "Attention",
                                    "Can not open file"
                                    "\nDo you want to change another file?",
                                    QMessageBox::Yes | QMessageBox::No);

        if (n == QMessageBox::Yes)
        {
            on_actionOpen_triggered();
        }
    }
    if(status == -2)
    {
        QMessageBox::critical (0, "Attention", "Invalid file", QMessageBox::Ok);
    }
    if(status == 0)
    {
        xmlPath = openFilePath;
    }

    refreshWidget("groupWidget");
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_windowsGroupWidget_itemClicked(QTreeWidgetItem *item)
{
    refreshWidget("windowsEntryWidget", item->text(0));
}

void MainWindow::on_actionAdd_windows_group_triggered()
{
    AddGroupDialog* addGroupDialog = new AddGroupDialog();
    int status;
    if (addGroupDialog->exec() == QDialog::Accepted)
    {
        status = groupManager->addWindowsGroup(addGroupDialog->getName(), addGroupDialog->getNotes());
    }
    if(status == 0)
    {
        refreshWidget("windowsGroupWidget");
    }
    else if(status == -1)
    {
        QMessageBox::critical (0,
                                "Error",
                                "Not enough rights to create a group of windows",
                                QMessageBox::Ok);
    }
    if(status == -2)
    {
        QMessageBox::critical (0,
                                "Error",
                                "Group " + addGroupDialog->getName() + " already exists",
                                QMessageBox::Ok);
    }
    if(status == -3)
    {
        QMessageBox::critical (0,
                                "Error",
                                "Unnown error",
                                QMessageBox::Ok);
    }
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
    }
    if(status == 0)
    {
        refreshWidget("windowsGroupWidget");
    }
    else if(status == -1)
    {
        QMessageBox::critical (0,
                                "Error",
                                "Not enough rights to update a group of windows",
                                QMessageBox::Ok);
    }
    if(status == -2)
    {
        QMessageBox::critical (0,
                                "Error",
                                "Group " + addGroupDialog->getName() + " already exists",
                                QMessageBox::Ok);
    }
    if(status == -3)
    {
        QMessageBox::critical (0,
                                "Error",
                                "Unnown error",
                                QMessageBox::Ok);
    }
}

void MainWindow::on_actionRemove_windows_group_triggered()
{
    QTreeWidgetItem* item = ui->windowsGroupWidget->currentItem();
    QMessageBox *message = new QMessageBox(QMessageBox::Information, "Remove windows group",
                                           "Do you want to delete group " + item->text(0), QMessageBox::Yes | QMessageBox::No);
    int n = message->exec();
    delete message;
    if(n == QMessageBox::Yes)
    {
        int status = groupManager->removeWindowsGroup(item->text(0));
        if(status == 0)
        {
            refreshWidget("windowsGroupWidget");
        }
        else if(status == -1)
        {
            QMessageBox::critical (0,
                                    "Error",
                                    "Not enough rights to remove a group of windows",
                                    QMessageBox::Ok);
        }
        else if(status == -2)
        {
            QMessageBox::critical (0,
                                    "Error",
                                    "Group " + item->text(0) + " does not exists",
                                    QMessageBox::Ok);
        }
        else if(status == -3)
        {
            QMessageBox::critical (0,
                                    "Error",
                                    "Unnown error",
                                    QMessageBox::Ok);
        }
    }
}
