#ifndef ADDPASSWORDDIALOG_H
#define ADDPASSWORDDIALOG_H

#include<QWidget>
#include<QDialog>
#include<QLineEdit>
#include<QString>
#include<QLabel>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QTextEdit>

#include<entities/Entry.h>


class AddEntryDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit *titleLineEdit;
    QLineEdit *userNameLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *passwordRepeatLineEdit;
    QLineEdit *URLLineEdit;
    QTextEdit *notesTextEdit;

public:
    AddEntryDialog(QWidget* pwgt = 0,
                   QString title = 0,
                   QString userName = 0,
                   QString password = 0,
                   QString passwordRepeat = 0,
                   QString URL = 0,
                   QString notes = 0);
    virtual ~AddEntryDialog();

    QString getTitle();
    QString getUserName();
    QString getPassword();
    QString getPasswordRepeat();
    QString getURL();
    QString getNotes();

};

#endif // ADDPASSWORDDIALOG_H
