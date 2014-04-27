#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QCryptographicHash>

class Message
{
public:
    Message();
    QString sender;
    QString reciver;
    QString msg;
    QString time;
    void setTimeAndDateMessage();

private:
    QString mIdGenerate(QString);
    QString getTimeDate();
};

#endif // MESSAGE_H
