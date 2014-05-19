#include "message.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

/*
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
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &jsonError);

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error occured during decoding message from JSON, abort";
        qDebug() << jsonError.errorString();
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    if (!jsonObj.contains("type")) {
        qDebug() << "Incorrect message arrived";
        qDebug() << jsonObj;
        return;
    }
    type = jsonObj["type"].toInt();

    switch (type) {
    case 1: // Ping
        break; // No data to decode
    case 10: // Chat message
        from = jsonObj["from"].toString();
        to = jsonObj["to"].toString();
        msg = jsonObj["text"].toString();
        timestamp =  jsonObj["receive_timestamp"].toString();
    }
}

void Message::toHtml()
{
    html = "<p><font size='-3'>" + timestamp + "</font><b> " + from + "</b><br>" + msg + "</p>";
}
*/


void Message::decode(const QByteArray &json)
{
    qDebug() << "Data before decoding" << json;
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json, &jsonError);

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error occured during decoding message from JSON, abort";
        qDebug() << jsonError.errorString();
        return;
    }
    QJsonObject jsonObj = jsonDoc.object();

    this->content = jsonObj.toVariantMap();
    qDebug() << "Data after decoding" << this->content;
}

QByteArray Message::encode() const
{
    qDebug() << "Data before encoding" << this->content;
    QJsonObject jsonObj = QJsonObject::fromVariantMap(this->content);
    QJsonDocument jsonDoc(jsonObj);
    return jsonDoc.toJson();
}

const QVariant &Message::operator[](const QString &key) const
{
    if (this->content.contains(key)) {
        return this->content[key];
    }
    qDebug() << "Key" << key << "not found in" << this->content;
    return this->content[key];
    return QVariant();
}

QVariant &Message::operator[](const QString &key)
{
    if (this->content.contains(key)) {
        return this->content[key];
    }
    qDebug() << "Key" << key << "not found in" << this->content;
    return this->content[key];
}


QString ChatMessage::toHtml() const
{
    QString html = "<p><font size='-3'>" + this->content["send_timestamp"].toString()
            + "</font><b> " + this->from() + "</b><br>" + this->text() + "</p>";
    return html;
}
