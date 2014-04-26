#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket *_pSocket;

private slots:
    void on_actionAbout_triggered();
    void readTcpData();

private:
    Ui::MainWindow *ui;
    void connectTcp();
};

#endif // MAINWINDOW_H
