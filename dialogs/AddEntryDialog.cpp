#include "AddEntryDialog.h"

AddEntryDialog::AddEntryDialog (QWidget* pwgt/*= 0*/,
                                QString title,
                                QString userName,
                                QString password,
                                QString URL,
                                QString notes)
    : QDialog (pwgt, Qt::WindowTitleHint | Qt ::WindowSystemMenuHint)
{
    titleLineEdit = new QLineEdit(title);
    userNameLineEdit = new QLineEdit(userName);
    passwordLineEdit = new QLineEdit(password);
    URLLineEdit = new QLineEdit(URL);
    notesTextEdit = new QTextEdit(notes);

    QLabel *titleLbl = new QLabel("&Title");
    QLabel *userNameLbl = new QLabel("&User name");
    QLabel *passwordLbl = new QLabel("&Password");
    QLabel *URLLbl = new QLabel("&URL");
    QLabel *noteLbl = new QLabel("&Note");

    titleLbl->setBuddy(titleLineEdit);
    userNameLbl->setBuddy(userNameLineEdit);
    passwordLbl->setBuddy(passwordLineEdit);
    URLLbl->setBuddy(URLLineEdit);
    noteLbl->setBuddy(notesTextEdit);

    QPushButton* pcmdOk = new QPushButton ("&Ok") ;
    QPushButton* pcmdCancel = new QPushButton ("&Cancel");

    connect (pcmdOk, SIGNAL (clicked()), SLOT (accept()));
    connect (pcmdCancel, SIGNAL (clicked()), SLOT(reject()));

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(titleLbl, 0, 0);
    gridLayout->addWidget(userNameLbl, 1, 0);
    gridLayout->addWidget(passwordLbl, 2, 0);
    gridLayout->addWidget(URLLbl, 3, 0);
    gridLayout->addWidget(noteLbl, 4, 0);

    gridLayout->addWidget(titleLineEdit, 0, 1);
    gridLayout->addWidget(userNameLineEdit, 1, 1);
    gridLayout->addWidget(passwordLineEdit, 2, 1);
    gridLayout->addWidget(URLLineEdit, 3, 1);
    gridLayout->addWidget(notesTextEdit, 4, 1);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(pcmdOk);
    hLayout->addWidget(pcmdCancel);
    gridLayout->addLayout(hLayout, 5, 1);

    setLayout(gridLayout);
}

AddEntryDialog::~AddEntryDialog(){}

QString AddEntryDialog::getTitle()
{
    return titleLineEdit->text();
}

QString AddEntryDialog::getUserName()
{
    return userNameLineEdit->text();
}

QString AddEntryDialog::getPassword()
{
    return passwordLineEdit->text();
}

QString AddEntryDialog::getURL()
{
    return URLLineEdit->text();
}

QString AddEntryDialog::getNotes()
{
    return notesTextEdit->toPlainText().replace("\n", " ");
}
