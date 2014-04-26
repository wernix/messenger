#ifndef CHATBOXFORM_H
#define CHATBOXFORM_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class ChatBoxForm;
}

class ChatBoxForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBoxForm(QWidget *parent = 0);
    ~ChatBoxForm();
    QTcpSocket *_pSocket;

private slots:
    void on_sendButton_clicked();

private:
    Ui::ChatBoxForm *ui;
    void sendMsgToServer(QString);
    QString parserToJson(QString);

};

#endif // CHATBOXFORM_H
