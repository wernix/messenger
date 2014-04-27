#include "message.h"


Message::Message()
{
}


QString Message::mIdGenerate(QString time)
{
    QCryptographicHash sha1(QCryptographicHash::Sha1);
    sha1.addData(time.toUtf8());
    return sha1.result();
}

bool Message::sendMsgToServer(QString jsonMsg)
{
    QByteArray data(jsonMsg.toUtf8());
    bool status = QTcpSocket::isValid();
    if(status) {
        QTcpSocket::write( data );
        qDebug()<<"isOpen?!";
        return 1;
    }else {
        qDebug()<<"isClose!";
    }

    return 0;
}


void Message::addMsgToMsgbox()
{
    QString send_msg = "<p>"
                        "<b>"+time+" "+sender+"(->"+reciver+")</b><br>"
                        +msg+
                      "</p>";
    ui->msgbox->append(send_msg);
}

QString Message::parserToJson(QString msg)
{
    return msg;
}

void Message::setTimeAndDateMessage()
{
    time = getTimeDate();
}

QString Message::getTimeDate()
{
    QString timeDate = QTime::currentTime().toString("hh:mm:ss") + " " + QDate::currentDate().toString("dd-MM-yyyy");
    return timeDate;
}


void Message::prepareMessageToSending()
{
    QString send = parserToJson(sender+":"+reciver+":"+time+":"+msg);
    sendMsgToServer(send);
}
