#ifndef CHATBOXFORM_H
#define CHATBOXFORM_H

#include <QWidget>

namespace Ui {
class ChatBoxForm;
}

class ChatBoxForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBoxForm(QWidget *parent = 0);
    ~ChatBoxForm();

private slots:
    void on_sendButton_clicked();

private:
    Ui::ChatBoxForm *ui;
};

#endif // CHATBOXFORM_H
