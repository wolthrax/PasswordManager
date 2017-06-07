#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include <QInputDialog>
#include <QTreeWidgetItem>
#include <QList>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QClipboard>

#include "dialogs/AddEntryDialog.h"
#include "dialogs/AddGroupDialog.h"
#include "dialogs/AddUserDialog.h"
#include "dialogs/AddPassword.h"
#include "utils/Messages.h"
#include "entities/Group.h"
#include "entities/CurrentObjects.h"
#include "managers/GroupManager.h"
#include "managers/EntryManager.h"
#include "managers/XMLManager.h"
#include "utils/StringConverter.h"
#include "utils/CheckPassword.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GroupManager *groupManager;
    EntryManager *entryManager;
    XMLManager *xmlManager;

    QString xmlPath = "";


private slots:
    void resizeEvent(QResizeEvent* event);

    void on_actionAddGroup_triggered();

    void on_actionEditGroup_triggered();

    void on_actionRemoveGroup_triggered();

    void on_actionAddEntry_triggered();

    void on_actionCopy_password_to_clipboard_triggered();

    void on_actionEditEntry_triggered();

    void on_actionRemoveEntry_triggered();

    void on_actionAdd_windows_group_triggered();

    void on_actionEdit_windows_group_triggered();

    void on_actionRemove_windows_group_triggered();

    void on_actionAdd_windows_user_triggered();

    void on_actionEdit_windows_user_triggered();

    void on_actionRemove_windows_user_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_entryWidget_itemSelectionChanged();

    void on_groupWidget_itemSelectionChanged();

    void on_groupWidget_itemClicked(QTreeWidgetItem *item);

    void on_windowsGroupWidget_itemClicked(QTreeWidgetItem *item);

    void on_windowsGroupWidget_itemSelectionChanged();


private:
    Ui::MainWindow *ui;
    void refreshWidget(QString, QString groupId = 0);

};

#endif // CONTROLLER_H
