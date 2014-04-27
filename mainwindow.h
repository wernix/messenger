#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chatboxform.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QMap>

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
    void initializeMessage(QMap<QString, QString>);

private slots:
    void on_actionAbout_triggered();
    void readTcpData();

private:
    Ui::MainWindow *ui;
    void connectToServer(QString, qint32);
};



#endif // MAINWINDOW_H
