#ifndef ADDPASSWORD_H
#define ADDPASSWORD_H

#include<QWidget>
#include<QDialog>
#include<QLineEdit>
#include<QString>
#include<QLabel>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QTextEdit>

class AddPassword : public QDialog
{
    Q_OBJECT
private:
    QLineEdit* passwordLineEdit;
    QLineEdit* repeatLineEdit;

public:
    AddPassword(QWidget* pwgt = 0);
    virtual ~AddPassword();

    QString getPassword();
    QString getRepeat();
};

#endif // ADDPASSWORD_H
