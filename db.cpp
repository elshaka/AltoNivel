#include "db.h"

DB::DB()
{
    this->addConnection("QPSQL","alto_nivel","localhost","postgres","ucla",5432);
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
            qDebug()<< "Conexion a la Base de Datos NO Exitosa";
        }
        else qDebug()<< "Conexion a la Base de Datos Exitosa";
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

bool DB::create(Cliente cliente)
{
    QSqlQuery q;
    qDebug() << "Crear cliente";
    q = this->excecute("INSERT into clientes (nombre, apellido, cedula) values ('" + cliente.getNombre() + "','" +
                                                                                     cliente.getApellido() + "','" +
                                                                                     cliente.getCedula() + "')");
    return true;
}

bool DB::update(Cliente cliente)
{
    QSqlQuery q;
    qDebug() << "Crear cliente";
    q = this->excecute("UPDATE clientes SET nombre = '" + cliente.getNombre() + "', " +
                                         "apellido = '" + cliente.getApellido() + "', " +
                                         "cedula = '" + cliente.getCedula() + "'" +
                                         " WHERE id = " + QString::number(cliente.getId()));
    return true;
}

bool DB::destroy(Cliente cliente)
{
    QSqlQuery q;
    qDebug() << "Eliminar cliente";
    q = this->excecute("DELETE FROM clientes WHERE id = " + QString::number(cliente.getId()));
    return true;
}

QList<Cliente> DB::find_all()
{
    QSqlQuery q;
    QList<Cliente> clientes;
    qDebug() << "Cargar clientes";
    q = this->excecute("SELECT id, nombre, apellido, cedula FROM clientes" );
    while (q.next())
    {
        clientes.append(Cliente(q.value(1).toString().trimmed(),
                                q.value(2).toString().trimmed(),
                                q.value(3).toString().trimmed(),
                                q.value(0).toInt()));
    }
    return clientes;
}
