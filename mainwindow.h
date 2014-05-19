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
#include <QEvent>
#include <QCloseEvent>

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

    bool connectionStatus;
    void setWindowFlags(Qt::WindowFlags flags);
    QTcpSocket *connectionManager;
    ChatBoxDialog *form;
    MyProfile *myProfile;

public slots:
    void dispatchMessage(Message);

signals:
    void sendMessage(Message);

private slots:
    void readTcpData();
    void writeTcpData(Message message);
    void checkConnection(QAbstractSocket::SocketState);
    void authorize();

    void on_actionAbout_triggered();
    void on_actionNew_conversation_triggered();
    void on_contactsList_doubleClicked(const QModelIndex &index);
    void on_statusComboBox_currentIndexChanged(int index);
    void on_tryIconActivated(QSystemTrayIcon::ActivationReason);
    void on_actionQuit_triggered();

private:

    void openLocalDatabase();
    void openChatBox();
    void loadMyProfile();
    void initContactsList();
    void createTrayIcon();
    int tabIsOpen(QString);
    void createStatusBar();
    void connectToServer(QString hostname, int port);
    void addToConversation(ChatMessage);
    void addNewTab(QString);

    bool isMinimalized;

    Ui::MainWindow *ui;
    QMap<QString, QString> *config;
    QSettings *settings;
    QSqlDatabase contactsDb, accountsDb;
    QSystemTrayIcon *trayIcon;
    QMenu *trayContextMenu;
    QSqlTableModel *contactsModel;
    ChatBoxDialogContent *templateChat;
    QMap<QString, ChatBoxDialogContent*> *createdTabs;

protected:
    void closeEvent(QCloseEvent *);
    void changeEvent();
};



#endif // MAINWINDOW_H
