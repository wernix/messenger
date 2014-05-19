#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "message.h"

#include "ui_chatboxdialogcontent.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectionManager = new QTcpSocket(this);

    form = new ChatBoxDialog(0);

    createdTabs = new QMap<QString, ChatBoxDialogContent*>;

    createStatusBar();

    createTrayIcon();

    openLocalDatabase();

    loadMyProfile();

    initContactsList();

    this->settings = new QSettings("settings.ini", QSettings::IniFormat);

    QString hostname = this->settings->value("Server/Hostname").toString();
    int port = this->settings->value("Server/Port").toInt();

    connect(this->connectionManager, SIGNAL(connected()), this, SLOT(authorize()));
    connectToServer(hostname, port);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent()
{
    if(this->windowState() == Qt::WindowMinimized) {
        this->hide();
        trayIcon->showMessage("Minimalize", "App is running. If you want to close click this icon and choose Quit in menu.", QSystemTrayIcon::Information, 10000);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->hide();
    trayIcon->showMessage("Minimalize", "App is running. If you want to close click this icon and choose Quit in menu.", QSystemTrayIcon::Information, 10000);
    event->ignore();
}

// Create and setup statusBar
void MainWindow::createStatusBar()
{
    statusBar()->addWidget(ui->statusComboBox);
    statusBar()->addWidget(ui->socketStateLabel);
    statusBar()->setContentsMargins(5,1,5,1);
}

// Create and setup tray icon
void MainWindow::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon;
    QIcon ico("ico/tray.svg");
    trayIcon->setIcon(ico);
    trayIcon->connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_tryIconActivated(QSystemTrayIcon::ActivationReason)));

    trayContextMenu = new QMenu(this);
    trayContextMenu->addAction(ui->actionMinimalize);
    trayContextMenu->addAction(ui->actionRestore);
    trayContextMenu->addAction(ui->actionQuit);

    trayIcon->setContextMenu(trayContextMenu);
    trayIcon->show();
}

// Tray icon actions
void MainWindow::on_tryIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
        if(connectionManager->state() == QAbstractSocket::ConnectedState)
            trayIcon->showMessage("Messenger Status", "Every thing is all right, you are connected =)", QSystemTrayIcon::Information, 500);
        else
            trayIcon->showMessage("Messenger Status", "Not Connected", QSystemTrayIcon::Critical, 50000);
        break;
    case QSystemTrayIcon::Context:
        break;
    case QSystemTrayIcon::DoubleClick:
        if(this->isHidden()) {
            this->showNormal();
        }else
            this->hide();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    case QSystemTrayIcon::Unknown:
        break;
    }
}

// Load user account data from local database
void MainWindow::loadMyProfile()
{
    myProfile = new MyProfile;
    if(accountsDb.open()) {
        QSqlQuery q("select * from accounts", accountsDb);
        q.exec();
        if(q.result())
            while(q.next()) {
                myProfile->login = q.value("login").toString();
                myProfile->alias = q.value("alias").toString();
            }

    }
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *dialog = new AboutDialog(this);
    dialog->show();
}

// Open local database (contacts, accounts)
void MainWindow::openLocalDatabase()
{
    contactsDb = QSqlDatabase::addDatabase("QSQLITE", "contacts.sqlite");
    contactsDb.setDatabaseName("contacts.sqlite");
    if(!contactsDb.open())
        QMessageBox::warning(this, "Baza kontaktów", contactsDb.lastError().text(), QMessageBox::Ok);
    contactsDb.close();

    accountsDb = QSqlDatabase::addDatabase("QSQLITE", "accounts.sqlite");
    accountsDb.setDatabaseName("accounts.sqlite");
    if(!accountsDb.open())
        QMessageBox::warning(this, "Baza z kontami", accountsDb.lastError().text(), QMessageBox::Ok);
    accountsDb.close();
}

// Initialize CL, load contacts from database and setup table
void MainWindow::initContactsList()
{
    if(contactsDb.open()) {
        contactsModel = new ContactsListModel(this, contactsDb);
        contactsModel->setTable("contacts");
        contactsModel->select();
        ui->contactsList->setModel(contactsModel);
        ui->contactsList->hideColumn(ContactProto);
        ui->contactsList->hideColumn(ContactLogin);

        QHeaderView *vHeader = ui->contactsList->verticalHeader();
        vHeader->setDefaultSectionSize(20);
        ui->contactsList->setContentsMargins(QMargins(0,0,0,0));
    }
}

// Function using to connect with server
void MainWindow::connectToServer(QString address, int port)
{
    qDebug() << "Connecting to server: " << address << ":" << port;

    connectionManager->connectToHost(address, port);
    connect(connectionManager, SIGNAL(readyRead()), SLOT(readTcpData()));

    connect(connectionManager, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(checkConnection(QAbstractSocket::SocketState)));

    if(connectionManager->waitForConnected(500)) {
        qDebug() << "Connected!";
    }else {
        qDebug() << "Timeout waiting for connection";
        QMessageBox::critical(this, "Problem during connection to server", "Server can't be reach at this time, sorry");
    }

    checkConnection(connectionManager->state());

}

// Function check and set current status in statusBar
void MainWindow::checkConnection(QAbstractSocket::SocketState state)
{
    switch(state)
    {
    case QAbstractSocket::UnconnectedState:
        ui->statusComboBox->setCurrentIndex(StatusOffline);
        ui->socketStateLabel->setText(tr("Disconnected"));
        break;
    case QAbstractSocket::HostLookupState:
        ui->socketStateLabel->setText(tr("HostLookup"));
        break;
    case QAbstractSocket::BoundState:
        ui->socketStateLabel->setText(tr("Bound"));
        break;
    case QAbstractSocket::ConnectingState:
        ui->socketStateLabel->setText(tr("Connecting"));
        break;
    case QAbstractSocket::ClosingState:
        ui->socketStateLabel->setText(tr("Closing"));
        break;
    case QAbstractSocket::ListeningState:
        ui->socketStateLabel->setText(tr("Listening"));
        break;
    case QAbstractSocket::ConnectedState:
        ui->statusComboBox->setCurrentIndex(StatusOnline);
        ui->socketStateLabel->setText(tr("Connected"));
        break;
    }
}

// Function listening and captures data sends to client,
void MainWindow::readTcpData()
{
    Message msg;
    QByteArray data = connectionManager->readAll();

    qDebug()<<"readTcp: " + data;

    msg.decode(data);
//    msg.setTimestamp();

    dispatchMessage(msg);

//    if(msg.from == myProfile->login) {
//        connect(this, SIGNAL(sendMessage(Message)), this, SLOT(recognitionMessage(Message)));
//        emit sendMessage(msg);
    //    }
}

void MainWindow::writeTcpData(Message message)
{
    QByteArray data = message.encode();
    this->connectionManager->write(data);
}

// Check if this tab is open.
int MainWindow::tabIsOpen(QString tabName)
{
    int countTabs = form->count();
    if(countTabs >= 0) {
        for(int i = 0; i <= countTabs; i++) {
            if(form->tabText(i) == tabName) {
                form->setCurrentIndex(i);
                form->activateWindow();
                // check chatbox minimalize
                return true;
            }
        }
    }
    return false;
}

// Check that ChatBoxDialog is open or minimalized.
void MainWindow::openChatBox()
{
    if (!form->isVisible())
        form->show();

    if(form->windowState() |=(Qt::WindowMinimized)) {
        form->showMinimized();
        form->showNormal();
    }

}

// Function manages that message, when send to server
// and when show to chatbox
void MainWindow::dispatchMessage(Message msg)
{
    switch (msg.type()) {
    case 1: // Ping message
        // Send reply
        qDebug() << "Pong!";
        Pong reply();
        writeTcpData((Message)reply);
        return;
    case 20: // Auth result
        if (!msg["authorization"].toBool()) {
            QMessageBox::critical(this, "Authorization failed", "Login or password are wrong");
        }
        return;
    }
    qCritical() << "NO ROUTE FOUND FOR MESSAGE";

//    if(msg.from == myProfile->login) {
//        addToConversation(msg);
//        connectionManager->write(msg.json);
//    }

//    if(msg.to == myProfile->login) {
//        addToConversation(msg);
//    }
}

// Add message to ChatBox
void MainWindow::addToConversation(ChatMessage msg)
{
    openChatBox();

    QString tabName = msg.to();

    if(msg.to() == myProfile->login)
        tabName = msg.from();

    bool tabOpen = tabIsOpen(tabName);

    if(!tabOpen)
        addNewTab(tabName);

    // Get sender CBDC widget and add to conversation message
    ChatBoxDialogContent *w = (ChatBoxDialogContent*) sender();
    w->ui->conversationHistory->append(msg.toHtml());

    qDebug()<<"client: '" + msg.from() + "' send to '" + msg.to() + "' message: '" + msg.text() + "'";
}


// Create new conversation tab
// Insert or add new tab in CBD and add connect signal to slot
void MainWindow::addNewTab(QString to)
{
    QString login;
    QSqlQuery q("SELECT login FROM contacts WHERE alias='"+to+"';", contactsDb);
    if(q.next()) {
        login = q.value("login").toString();
    }else
        return;

    openChatBox();

    ChatBoxDialogContent *newContent = new ChatBoxDialogContent();
    newContent->myProfile = myProfile;
    createdTabs->insert(to, newContent);

    form->insertTab(to.toInt(), createdTabs->take(to), to);
    newContent->receiver = login;
    connect(newContent, SIGNAL(sendMessage(Message)), this, SLOT(dispatchMessage(Message)));
    form->setCurrentIndex(to.toInt());
    form->activateWindow();
}

// Perform log in user to server
void MainWindow::authorize()
{
    QString username = this->settings->value("User/Username").toString();
    QString password = this->settings->value("User/Password").toString();

    qDebug() << "Logging in: " << username << password;
    Login authMessage;
    authMessage["username"] = username;
    authMessage["password"] = password;

    this->writeTcpData(authMessage);
}

void MainWindow::on_actionNew_conversation_triggered()
{
    QModelIndex index = ui->contactsList->currentIndex();
    if(index.model()->index(index.row(), ContactAlias, QModelIndex()).data().toString().isSimpleText())
        on_contactsList_doubleClicked(index);
}

void MainWindow::on_contactsList_doubleClicked(const QModelIndex &index)
{
    QString to = index.model()->index(index.row(), ContactAlias, QModelIndex()).data().toString();

    if(tabIsOpen(to)) {
        openChatBox();
    }else
        addNewTab(to);
}

void MainWindow::on_statusComboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case StatusOnline:
        if(connectionManager->state() == QAbstractSocket::UnconnectedState)
            connectToServer("127.0.0.1", 8008);
        break;
    case StatusOffline:
        if(connectionManager->state() == QAbstractSocket::ConnectedState)
            connectionManager->disconnectFromHost();
        break;
    }
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}
