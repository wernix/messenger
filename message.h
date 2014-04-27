#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <QDebug>

class Message
{
public:
    Message();
    QString sender;
    QString reciver;
    QString msg;
    QString time;
    void setTimeAndDateMessage();
    void prepareMessageToSending();
    void addMsgToMsgbox();

private:
    QString mIdGenerate(QString);
    QString getTimeDate();
    QString parserToJson(QString);
    QString jsonMessage();
protected:
    bool sendMsgToServer(QString);
};

#endif // MESSAGE_H
