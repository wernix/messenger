#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QCryptographicHash>

// Generic message class
class Message
{
public:
    Message() {}
    virtual void decode(const QByteArray &json);
    virtual QByteArray encode() const;

    const QVariant &operator[](const QString& key) const;
    QVariant &operator[](const QString& key);

    virtual int type() { return this->content["type"].toInt(); }

    static QString toHtml(const QString &message);

protected:
    QMap<QString, QVariant> content;
};

class Pong : public Message
{
public:
    Pong() : Message() { this->content["type"] = 2; }

};

class ChatMessage : public Message
{
public:
    ChatMessage() : Message() { this->content["type"] = 10; }

    QString from() const { return this->content["from"].toString(); }
    QString to() const { return this->content["to"].toString(); }
    QString text() const { return this->content["text"].toString(); }
    QString toHtml() const;
};

class Login : public Message
{
public:
    Login() : Message() { this->content["type"] = 20; }
    bool authorized() const { return this->content["authorization"].toBool(); }
};

/*
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
*/
#endif // MESSAGE_H
