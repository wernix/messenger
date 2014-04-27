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



void ChatBoxForm::on_buddyTabs_tabCloseRequested(int index)
{
//    if(ui->buddyTabs->count() > 1) {
//        ui->buddyTabs->removeTab(index);
//    }
    int count = ui->buddyTabs->tabBar()->count();
    ui->buddyTabs->tabBar()->removeTab(index);

    if(!(count-1))
        this->close();
    qDebug()<<QString::number(count)+":"+QString::number(index);
}
