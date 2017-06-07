#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include<QWidget>
#include<QDialog>
#include<QLineEdit>
#include<QString>
#include<QLabel>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QTextEdit>

class AddUserDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit *userNameLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *passwordRepeatLineEdit;
    QTextEdit *notesTextEdit;

public:
    AddUserDialog(QWidget* pwgt = 0,
                  QString type = "add",
                  QString userName = 0,
                  QString password = 0,
                  QString passwordRepeat = 0,
                  QString notes = 0);
    virtual ~AddUserDialog();

    QString getUserName();
    QString getPassword();
    QString getPasswordRepeat();
    QString getNotes();
};

#endif // ADDUSERDIALOG_H
