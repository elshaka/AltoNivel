#include "db.h"

QString DB::FORMATOFECHA = "yyyy-MM-dd hh:mm:ss";

DB::DB()
{
    this->addConnection("QPSQL", "alto_nivel", "localhost", "postgres", "ucla", 5432);
}

QSqlError DB::addConnection(const QString &driver, const QString &dbName, const QString &host,
                            const QString &user, const QString &passwd, int port)
{
    static int cCount = 0;
    QSqlError err;
    if (!QSqlDatabase::contains("conexion"))
    {
        db = QSqlDatabase::addDatabase(driver, QString("conexion"));
        db.setDatabaseName(dbName);
        db.setHostName(host);
        db.setPort(port);
        if (!db.open(user, passwd))
        {
            err = db.lastError();
            db = QSqlDatabase();
            QSqlDatabase::removeDatabase(QString("conexion").arg(cCount));
            qDebug() << "Error al intentar conectar con el servidor " + host;
        }
    }
    else db = QSqlDatabase::database("conexion", true);
    return err;
}

QSqlQuery DB::excecute(QString sql)
{
    QSqlQuery q("", db);
    qDebug() << sql;
    if (!q.exec(sql)) qDebug() << q.lastError();
    return q;
}

void DB::setDatabase(QSqlDatabase db)
{
    this->db = db;
}
QSqlDatabase DB::getDatabase()
{
    return db;
}
