#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ui_chatboxdialogcontent.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    form = new ChatBoxDialog(0);

    createdTabs = new QMap<QString, ChatBoxDialogContent*>;

    connectStatusLabel = new QLabel;

    statusBar()->addWidget(connectStatusLabel);

    openLocalDatabase();

    loadMyProfile();

    initContactsList();

    //connectToServer("172.30.0.7", 8008);
    connectToServer("127.0.0.1", 8008);
}

MainWindow::~MainWindow()
{
    delete ui;
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
void MainWindow::connectToServer(QString address, qint32 port)
{
    connectionManager = new QTcpSocket(this);
    connectionManager->connectToHost(address, port);
    connect(connectionManager, SIGNAL(readyRead()), SLOT(readTcpData()));

    if(connectionManager->waitForConnected(500)) {
        emit connectionManager->connected();
    }else
        emit connectionManager->disconnected();
}

// Function listening and captures data sends to client,
void MainWindow::readTcpData()
{
    Message msg;
    QByteArray data = connectionManager->readAll();

    msg.decode(data);
    msg.setTimestamp();

    if(msg.from == myProfile->login) {
        connect(this, SIGNAL(sendMessage(Message)), this, SLOT(recognitionMessage(Message)));
        emit sendMessage(msg);
    }

    qDebug()<<"readTcp: " + data;
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

// Check that ChatBoxDialog is open.
void MainWindow::openChatBox()
{
    if (!form->isVisible())
        form->show();
}

// Function manages that message, when send to server
// and when show to chatbox
void MainWindow::recognitionMessage(Message msg)
{
    if(msg.from == myProfile->login) {
        addToConversation(msg);
        connectionManager->write(msg.json);
    }

    if(msg.to == myProfile->login) {
        addToConversation(msg);
    }
}

// Add message to ChatBox
void MainWindow::addToConversation(Message msg)
{
    openChatBox();

    QString tabName = msg.to;

    if(msg.to == myProfile->login)
        tabName = msg.from;

    bool tabOpen = tabIsOpen(tabName);

    if(!tabOpen)
        addNewTab(tabName);

    // Get sender CBDC widget and add to conversation message
    ChatBoxDialogContent *w = (ChatBoxDialogContent*) sender();
    w->ui->conversationHistory->append(msg.html);

    qDebug()<<"client: '" + msg.from + "' send to '" + msg.to + "' message: '" + msg.msg + "'";
}


// Create new conversation tab
// Insert or add new tab in CBD and add connect signal to slot
void MainWindow::addNewTab(QString to)
{
    openChatBox();

    ChatBoxDialogContent *newContent = new ChatBoxDialogContent();
    createdTabs->insert(to, newContent);

    form->insertTab(to.toInt(), createdTabs->take(to), to);
    //form->addTab(createdTabs->take(to), to);
    newContent->receiver = to;
    connect(newContent, SIGNAL(sendMessage(Message)), this, SLOT(recognitionMessage(Message)));
    form->setCurrentIndex(to.toInt());
    form->activateWindow();
}

void MainWindow::on_actionNew_conversation_triggered()
{
    QModelIndex index = ui->contactsList->currentIndex();
    if(index.model()->index(index.row(), ContactAlias, QModelIndex()).data().toString().isSimpleText())
        on_contactsList_doubleClicked(index);
}

void MainWindow::on_contactsList_doubleClicked(const QModelIndex &index)
{
    //QString to = index.data().toString();
    QString to = index.model()->index(index.row(), ContactAlias, QModelIndex()).data().toString();

    if(!tabIsOpen(to))
        addNewTab(to);
}
