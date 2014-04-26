#include "chatboxform.h"
#include "ui_chatboxform.h"

ChatBoxForm::ChatBoxForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatBoxForm)
{
    ui->setupUi(this);
}

ChatBoxForm::~ChatBoxForm()
{
    delete ui;
}
