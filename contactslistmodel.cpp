#include <QSqlTableModel>
#include <QSqlDatabase>

class ContactsListModel: public QSqlTableModel
{
public:
    ContactsListModel(QObject * parent = 0, QSqlDatabase contactsDb = QSqlDatabase()):
        QSqlTableModel(parent, contactsDb)
    { }

    ~ContactsListModel() { }

    Qt::ItemFlags flags (const QModelIndex & index) const
    {
        if (index.column() == 1)
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable /*| Qt::ItemIsEditable*/;
        else
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
};
