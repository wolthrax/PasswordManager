#include "AddUserDialog.h"

AddUserDialog::AddUserDialog(QWidget* pwgt/*= 0*/,
                             QString userName,
                             QString password,
                             QString passwordRepeat,
                             QString notes)
    : QDialog (pwgt, Qt::WindowTitleHint | Qt ::WindowSystemMenuHint)

{
    userNameLineEdit = new QLineEdit(userName);
    passwordLineEdit = new QLineEdit(password);
    passwordRepeatLineEdit = new QLineEdit(passwordRepeat);
    notesTextEdit = new QTextEdit(notes);

    QLabel *userNameLbl = new QLabel("&User name");
    QLabel *passwordLbl = new QLabel("&Password");
    QLabel *passwordRepeatLbl = new QLabel("&Repeat");
    QLabel *notesLbl = new QLabel("&Notes");

    userNameLbl->setBuddy(userNameLineEdit);
    passwordLbl->setBuddy(passwordLineEdit);
    passwordRepeatLbl->setBuddy(passwordRepeatLineEdit);
    notesLbl->setBuddy(notesTextEdit);

    QPushButton* pcmdOk = new QPushButton ("&Ok") ;
    QPushButton* pcmdCancel = new QPushButton ("&Cancel");

    connect (pcmdOk, SIGNAL (clicked()), SLOT (accept()));
    connect (pcmdCancel, SIGNAL (clicked()), SLOT(reject()));

    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(userNameLbl, 0, 0);
    gridLayout->addWidget(passwordLbl, 1, 0);
    gridLayout->addWidget(passwordRepeatLbl, 2, 0);
    gridLayout->addWidget(notesLbl, 3, 0);

    gridLayout->addWidget(userNameLineEdit, 0, 1);
    gridLayout->addWidget(passwordLineEdit, 1, 1);
    gridLayout->addWidget(passwordRepeatLineEdit, 2, 1);
    gridLayout->addWidget(notesTextEdit, 3, 1);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(pcmdOk);
    hLayout->addWidget(pcmdCancel);
    gridLayout->addLayout(hLayout, 4, 1);

    setLayout(gridLayout);
}

AddUserDialog::~AddUserDialog(){}

QString AddUserDialog::getUserName()
{
    return userNameLineEdit->text();
}

QString AddUserDialog::getPassword()
{
    return passwordLineEdit->text();
}

QString AddUserDialog::getPasswordRepeat()
{
    return passwordRepeatLineEdit->text();
}

QString AddUserDialog::getNotes()
{
    return notesTextEdit->toPlainText();
}
