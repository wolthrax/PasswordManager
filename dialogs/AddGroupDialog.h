#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include<QWidget>
#include<QDialog>
#include<QLineEdit>
#include<QString>
#include<QLabel>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QTextEdit>

class AddGroupDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit* nameLineEdit;
    QTextEdit* notesTextEdit;

public:
    AddGroupDialog(QWidget* pwgt = 0,
                   QString name = 0,
                   QString notes = 0);
    virtual ~AddGroupDialog();

    QString getName();
    QString getNotes();
};

#endif // ADDGROUPDIALOG_H
