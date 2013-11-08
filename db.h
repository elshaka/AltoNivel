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

private:
    QSqlQuery excecute(QString sql);
    QSqlError addConnection(const QString &driver, const QString &dbName,
                            const QString &host, const QString &user, const QString &passwd, int port);
    void setDatabase(QSqlDatabase db);
    QSqlDatabase getDatabase();

public:
    DB();
    QList<QString> crearCliente(Cliente cliente);
    QList<QString> actualizarCliente(Cliente cliente);
    bool eliminarCliente(Cliente cliente);
    QList<Cliente> obtenerClientes();
};

#endif // DB_H
