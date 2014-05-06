#include "chatboxdialog.h"
#include "ui_chatboxdialog.h"
#include <QDebug>

ChatBoxDialog::ChatBoxDialog(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ChatBoxDialog)
{
    ui->setupUi(this);
}

ChatBoxDialog::~ChatBoxDialog()
{
    delete ui;
}

void ChatBoxDialog::on_ChatBoxDialog_tabCloseRequested(int index)
{
    int count = this->count();
        this->removeTab(index);

        if(!(count-1))
            this->close();
}


