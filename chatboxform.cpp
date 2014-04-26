#include "chatboxform.h"
#include "ui_chatboxform.h"
#include <QTextDocument>
#include <QPainter>
#include <QAbstractItemDelegate>
#include <QMap>

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
    QString msg = ui->msgEdit->toPlainText();
    if(msg.isSimpleText()) {
        QMap<QString, QString> message;
        message["data"] = "12:34 25-03-2015";
        message["sender"] = "sender_nick";
        message["reciver"] = "reciver_nick";
        message["msg"] = msg;

        ui->msgbox->append("<p><b>"+message["sender"]+" "+message["data"]+"</b><br>"+message["msg"]+"</p>");

        ui->msgEdit->clear();
    }
}
