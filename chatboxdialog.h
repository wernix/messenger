#ifndef CHATBOXDIALOG_H
#define CHATBOXDIALOG_H

#include <QTabWidget>
#include <QDebug>
#include <QEvent>
#include <QWindowStateChangeEvent>
#include "chatboxdialogcontent.h"

namespace Ui {
class ChatBoxDialog;
}

class ChatBoxDialog : public QTabWidget
{
    Q_OBJECT

public:
    explicit ChatBoxDialog(QWidget *parent = 0);
    ~ChatBoxDialog();

signals:
    void sendMessage(QMap<QString, QString> map);

private slots:
    void on_ChatBoxDialog_tabCloseRequested(int index);

private:
    Ui::ChatBoxDialog *ui;

protected:

};

#endif // CHATBOXDIALOG_H
