#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "cliente.h"

class DB
{
protected:
    QSqlDatabase db;

public:
    DB();
    QSqlError addConnection(const QString &driver, const QString &dbName,
                            const QString &host, const QString &user, const QString &passwd, int port);
    QSqlQuery excecute(QString sql);
    void setDatabase(QSqlDatabase db);
    QSqlDatabase getDatabase();

    bool create(Cliente cliente);
    bool update(Cliente cliente);
    bool destroy(Cliente cliente);
    QList<Cliente> find_all();
};

#endif // DB_H
