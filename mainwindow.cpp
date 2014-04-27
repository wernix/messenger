#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chatboxform.h"
#include "aboutdialog.h"
#include "message.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectToServer("172.30.0.7", 8008);

    ChatBoxForm *form = new ChatBoxForm;
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
    qDebug()<<newMessage.msg;

}
