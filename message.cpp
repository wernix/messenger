#include "message.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

Message::Message()
{
}

void Message::setTimestamp()
{
    timestamp = QTime::currentTime().toString("hh:mm:ss") + " " + QDate::currentDate().toString("dd.MM.yyyy");
}

void Message::encode()
{
    QJsonDocument jsonDoc;
    QJsonObject jsonObj;
    jsonObj.insert("Type", QJsonValue(type));
    jsonObj.insert("From", QJsonValue(from));
    jsonObj.insert("To", QJsonValue(to));
    jsonObj.insert("Message", QJsonValue(msg));

    jsonDoc.setObject(jsonObj);
    json = jsonDoc.toJson();
}

void Message::decode(QByteArray data)
{
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data,&jsonError);
    QJsonObject jsonObj = jsonDoc.object();

    type = jsonObj["Type"].toInt();
    from = jsonObj["From"].toString();
    to = jsonObj["To"].toString();
    msg = jsonObj["Message"].toString();
}

void Message::toHtml()
{
    html = "<p><font size='-3'>" + timestamp + "</font><b> " + from + "</b><br>" + msg + "</p>";
}