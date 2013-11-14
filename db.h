#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DB
{
protected:
    QSqlDatabase db;

private:
    QSqlError addConnection(const QString &driver, const QString &dbName,
                            const QString &host, const QString &user,
                            const QString &passwd, int port);
    void setDatabase(QSqlDatabase db);
    QSqlDatabase getDatabase();

public:
    DB();
    QSqlQuery excecute(QString sql);
    static QString FORMATOFECHA;
};

#endif // DB_H
