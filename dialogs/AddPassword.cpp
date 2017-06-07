#include "AddPassword.h"

AddPassword::AddPassword(QWidget* pwgt/*= 0*/)
                : QDialog (pwgt, Qt::WindowTitleHint | Qt ::WindowSystemMenuHint)
{
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    repeatLineEdit = new QLineEdit();
    repeatLineEdit->setEchoMode(QLineEdit::Password);

    QLabel *passwordLbl = new QLabel("&Password");
    QLabel *repeatLbl = new QLabel("&Repeat");

    passwordLbl->setBuddy(passwordLineEdit);
    repeatLbl->setBuddy(repeatLineEdit);

    QPushButton* pcmdOk = new QPushButton ("&Ok") ;
    QPushButton* pcmdCancel = new QPushButton ("&Cancel");

    connect (pcmdOk, SIGNAL (clicked()), SLOT (accept()));
    connect (pcmdCancel, SIGNAL (clicked()), SLOT(reject()));

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(passwordLbl, 0, 0);
    gridLayout->addWidget(repeatLbl, 1, 0);

    gridLayout->addWidget(passwordLineEdit, 0, 1);
    gridLayout->addWidget(repeatLineEdit, 1, 1);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(pcmdOk);
    hLayout->addWidget(pcmdCancel);
    gridLayout->addLayout(hLayout, 5, 1);

    setLayout(gridLayout);

}

AddPassword::~AddPassword(){}

QString AddPassword::getPassword()
{
    return passwordLineEdit->text();
}

QString AddPassword::getRepeat()
{
    return repeatLineEdit->text();
}
