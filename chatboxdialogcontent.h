#ifndef CHATBOXDIALOGCONTENT_H
#define CHATBOXDIALOGCONTENT_H

#include <QFrame>
#include <QMap>
#include <QSettings>

#include "message.h"
#include "myprofile.h"

namespace Ui {
class ChatBoxDialogContent;
}

class ChatBoxDialogContent : public QFrame
{
    Q_OBJECT

public:
    explicit ChatBoxDialogContent(QWidget *parent = 0);
    ~ChatBoxDialogContent();
    Ui::ChatBoxDialogContent *ui;

    QString receiver;
    MyProfile *myProfile;
    void send(Message);

signals:
    void sendMessage(Message);
    void send();

private slots:
    void on_sendButton_clicked();

private:
};

#endif // CHATBOXDIALOGCONTENT_H
