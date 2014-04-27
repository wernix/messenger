#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chatboxform.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QMap>
#include <QTabBar>

enum JsonParser {
    ParserCoding,
    ParserDecoding
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket *connectionManager;
    bool connectionStatus;

public slots:
    void initializeMessage(QMap<QString, QString>);

private slots:
    void on_actionAbout_triggered();
    void readTcpData();

    void on_actionNew_conversation_triggered();

private:
    Ui::MainWindow *ui;
    ChatBoxForm *form;
    void connectToServer(QString, qint32);
    void addToConversation(QString, QString, QString, QString);
    void addNewTab(QString);
    QString parserToJson(QString, JsonParser);
};



#endif // MAINWINDOW_H
