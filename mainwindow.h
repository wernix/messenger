#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chatboxdialog.h"
#include "aboutdialog.h"
#include "message.h"
#include "myprofile.h"
#include "contactslistmodel.cpp"
#include <QMainWindow>
#include <QTcpSocket>
#include <QMap>
#include <QtSql>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSettings>
#include <QSystemTrayIcon>

enum JsonParser {
    ParserCoding,
    ParserDecoding
};

enum ContactsList {
    ContactStatus,
    ContactProto,
    ContactAlias,
    ContactLogin
};

enum ConnectionStatus {
    StatusOnline,
    StatusOffline
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

    ChatBoxDialog *form;
    MyProfile *myProfile;

public slots:
    void recognitionMessage(Message);

signals:
    void sendMessage(Message);

private slots:
    void readTcpData();

    void checkConnection(QAbstractSocket::SocketState);

    void on_actionAbout_triggered();

    void on_actionNew_conversation_triggered();

    void on_contactsList_doubleClicked(const QModelIndex &index);

    void on_statusComboBox_currentIndexChanged(int index);

    void on_tryIconActivated(QSystemTrayIcon::ActivationReason);

private:
    QMap<QString, QString> *config;

    QSqlDatabase contactsDb, accountsDb;

    QSystemTrayIcon *trayIcon;

    QMenu *trayContextMenu;

    bool isMinimalized;

    QSqlTableModel *contactsModel;

    void openLocalDatabase();

    void loadMyProfile();

    void openChatBox();

    int tabIsOpen(QString);

    Ui::MainWindow *ui;

    ChatBoxDialogContent *templateChat;

    QMap<QString, ChatBoxDialogContent*> *createdTabs;

    void connectToServer(QString, qint32);

    void addToConversation(Message);

    void addNewTab(QString);

    void initContactsList();

    void createTrayIcon();

    void createStatusBar();

};



#endif // MAINWINDOW_H
