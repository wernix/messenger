#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chatboxform.h"
#include "aboutdialog.h"
#include "ui_chatboxform.h"
#include "message.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectToServer("172.30.0.7", 8008);

    form = new ChatBoxForm;
    connect(form, SIGNAL(sendMessage(QMap<QString,QString>)), this, SLOT(initializeMessage(QMap<QString,QString>)));
    form->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *dialog = new AboutDialog(this);
    dialog->show();
}

void MainWindow::connectToServer(QString address, qint32 port)
{
    connectionManager = new QTcpSocket(this);
    connectionManager->connectToHost(address, port);
    connect(connectionManager, SIGNAL(readyRead()), SLOT(readTcpData()));
    if( connectionManager->waitForConnected() ) {
        qDebug()<<"Connect to Server!";
    }
    if(connectionManager->error()) {
        qDebug()<<connectionManager->errorString();
    }
}

void MainWindow::readTcpData()
{
    QByteArray data = connectionManager->readAll();
    QMap<QString, QString> message;
    message["data"] = QTime::currentTime().toString("hh:mm:ss") + " " + QDate::currentDate().toString("dd-MM-yyyy");
    message["sender"] = "server";
    message["reciver"] = "client";
    message["msg"] = data;
    qDebug()<<QString(message["sender"]+":"+message["msg"]);
    //addMsgToMsgbox(message);

}

void MainWindow::initializeMessage(QMap<QString, QString> msg_info)
{
    Message newMessage;
    newMessage.sender = msg_info["sender"];
    newMessage.reciver = msg_info["reciver"];
    newMessage.msg = msg_info["msg"];
    newMessage.setTimeAndDateMessage();

    addToConversation(newMessage.time, newMessage.sender, newMessage.reciver, newMessage.msg);
    //sendToServer(//qDebug()<<newMessage.msg;

}

void MainWindow::addToConversation(QString time, QString sender, QString reciver, QString msg)
{
    int tabIdConversation;
    QTabBar *tabBar = new QTabBar;
    tabBar = form->ui->buddyTabs->tabBar();
    if(form->isVisible()) {
        int countTabs = tabBar->count()-1;
        for(int i = 0; i <= countTabs; i++) {
            if(tabBar->tabText(i) == reciver) {
                qDebug()<<"chat is opened!";
                tabIdConversation = i;
                break;
            }

        }
        if(!countTabs) {
            addNewTab(reciver);
            qDebug()<<"is opened!";
        }

        QString send_msg = "<p>"
                            "<b>"+time+" "+sender+"(->"+reciver+")</b><br>"
                            +msg+
                          "</p>";
        form->ui->msgbox->append(send_msg);
    }//else {
//        qDebug()<<"ChatBoxForm isnt Visable = false";
//        form = new ChatBoxForm;
//        form->ui->buddyTabs->tabBar()->setTabData(0, reciver);
//    }
}

QString MainWindow::parserToJson(QString msg, JsonParser option)
{
    return msg;
}

void MainWindow::addNewTab(QString reciver)
{
    form->ui->buddyTabs->tabBar()->insertTab(reciver.toInt(),reciver);
}

void MainWindow::on_actionNew_conversation_triggered()
{
    if(!form->isVisible()) {
        form = new ChatBoxForm;
        form->show();
        connect(form, SIGNAL(sendMessage(QMap<QString,QString>)), this, SLOT(initializeMessage(QMap<QString,QString>)));
    }
}
