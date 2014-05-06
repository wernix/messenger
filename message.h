#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QCryptographicHash>


class Message
{
public:
    enum MessageType {
        C2C,
        S2C
    };

    Message();
    int type;
    QString from;
    QString to;
    QString msg;
    QString timestamp;
    QByteArray json;
    QString html;
    void toHtml();
    void setTimestamp();
    void encode();
    void decode(QByteArray);

private:
};

#endif // MESSAGE_H
