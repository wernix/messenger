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

void Message::setTimeAndDateMessage()
{
    time = getTimeDate();
}

QString Message::getTimeDate()
{
    QString timeDate = QTime::currentTime().toString("hh:mm:ss") + " " + QDate::currentDate().toString("dd-MM-yyyy");
    return timeDate;
}

