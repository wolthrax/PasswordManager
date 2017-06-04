#include "AddGroupDialog.h"

AddGroupDialog::AddGroupDialog(QWidget* pwgt/*= 0*/,
                               QString name,
                               QString notes)
        : QDialog (pwgt, Qt::WindowTitleHint | Qt ::WindowSystemMenuHint)
{
    nameLineEdit = new QLineEdit(name);
    notesTextEdit = new QTextEdit(notes);

    QLabel *nameLbl = new QLabel("&Name");
    QLabel *noteLbl = new QLabel("&Notes");

    nameLbl->setBuddy(nameLineEdit);
    noteLbl->setBuddy(notesTextEdit);

    QPushButton* pcmdOk = new QPushButton ("&Ok") ;
    QPushButton* pcmdCancel = new QPushButton ("&Cancel");

    connect (pcmdOk, SIGNAL (clicked()), SLOT (accept()));
    connect (pcmdCancel, SIGNAL (clicked()), SLOT(reject()));

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(nameLbl, 0, 0);
    gridLayout->addWidget(noteLbl, 1, 0);

    gridLayout->addWidget(nameLineEdit, 0, 1);
    gridLayout->addWidget(notesTextEdit, 1, 1);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(pcmdOk);
    hLayout->addWidget(pcmdCancel);
    gridLayout->addLayout(hLayout, 5, 1);

    setLayout(gridLayout);

}

AddGroupDialog::~AddGroupDialog(){}

QString AddGroupDialog::getName()
{
    return nameLineEdit->text();
}

QString AddGroupDialog::getNotes()
{
    return notesTextEdit->toPlainText();
}
