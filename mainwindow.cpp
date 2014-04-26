#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"
#include "chatboxform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ChatBoxForm *form = new ChatBoxForm;
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
