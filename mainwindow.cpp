#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatboxform.h"

#include "aboutdialog.h"
#include "chatboxform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectTcp();

    ChatBoxForm *form = new ChatBoxForm;
    form->_pSocket = _pSocket;
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

void MainWindow::connectTcp()
{
    _pSocket = new QTcpSocket(this);
    connect( _pSocket, SIGNAL(readyRead()), SLOT(readTcpData()) );

    _pSocket->connectToHost("172.30.0.9", 8008);
    if( _pSocket->waitForConnected() ) {
        qDebug()<<"Connect to Server!";
    }
}

void MainWindow::readTcpData()
{
    QByteArray data = _pSocket->readAll();
    qDebug()<<data;
}
