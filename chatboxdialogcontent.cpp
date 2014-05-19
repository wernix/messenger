#include "chatboxdialogcontent.h"
#include "ui_chatboxdialogcontent.h"

//#include "mainwindow.h"

ChatBoxDialogContent::ChatBoxDialogContent(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ChatBoxDialogContent)
{
    ui->setupUi(this);

    //myProfile = new MyProfile;
}

ChatBoxDialogContent::~ChatBoxDialogContent()
{
    delete ui;
}

void ChatBoxDialogContent::on_sendButton_clicked()
{
    Message msg;

    QString text = ui->msgEdit->toPlainText();
    if(text.isSimpleText()) {
        msg["type"] = 10;
        msg["from"] = myProfile->login;
        msg["to"] = receiver;
        msg["text"] = text;
//        msg.setTimestamp();
//        msg.encode();
//        msg.toHtml();

        emit sendMessage(msg);

        // When msg sent msgEdit is cleaning
        ui->msgEdit->clear();
    }
}

void ChatBoxDialogContent::send(Message msg)
{
    emit send();
}
