#ifndef CHATBOXFORM_H
#define CHATBOXFORM_H

#include <QWidget>
#include "message.h"
#include <QDebug>

namespace Ui {
class ChatBoxForm;
}

class ChatBoxForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBoxForm(QWidget *parent = 0);
    ~ChatBoxForm();
    Ui::ChatBoxForm *ui;

signals:
    void sendMessage(QMap<QString, QString> map);

private slots:
    void on_sendButton_clicked();

    void on_buddyTabs_tabCloseRequested(int index);

private:

};


#endif // CHATBOXFORM_H
