#include "chatboxform.h"
#include "ui_chatboxform.h"
#include "mainwindow.h"



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


void ChatBoxForm::on_sendButton_clicked()
{


    QString text = ui->msgEdit->toPlainText();
    //QString msg = ui->msgEdit->toPlainText();
    if(text.isSimpleText()) {
        // Prepare message and info before sending
        QMap<QString, QString> msg;
        msg["msg"] = text;
        msg["sender"] = "sender_nick";
        msg["reciver"] = "reciver_nick";

        emit sendMessage(msg);

        // When msg sent msgEdit is cleaning
        ui->msgEdit->clear();
    }
}


