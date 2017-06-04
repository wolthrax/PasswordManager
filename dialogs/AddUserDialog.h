#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include<QWidget>
#include<QDialog>
#include<QLineEdit>
#include<QString>
#include<QLabel>
#include<QComboBox>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QTextEdit>

class AddUserDialog : QDialog
{
public:
    AddUserDialog();
    virtual ~AddUserDialog();

    QString getUserName();
    QString getPassword();
    QString getNotes();
    QString getGroup();


private:
    QLineEdit *userNameLineEdit;
    QLineEdit *passwordLineEdit;
    QTextEdit *notesTextEdit;
    QComboBox *groupComboBox;



};

#endif // ADDUSERDIALOG_H
