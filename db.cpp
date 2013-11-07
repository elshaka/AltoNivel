#include "db.h"

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

QList<QString> DB::crearCliente(Cliente cliente)
{
    QSqlQuery q;
    if (cliente.valido())
    {
        qDebug() << "Crear cliente";
        q = this->excecute("INSERT INTO clientes (nombre, apellido, cedula, telefono, direccion) values ('" +
                            cliente.getNombre() + "','" +
                            cliente.getApellido() + "','" +
                            cliente.getCedula() + "','" +
                            cliente.getTelefono() + "','" +
                            cliente.getDireccion() + "')");
    }
    return cliente.errores;
}

QList<QString> DB::actualizarCliente(Cliente cliente)
{
    QSqlQuery q;
    if (cliente.valido())
    {
        qDebug() << "Crear cliente";
        q = this->excecute("UPDATE clientes SET nombre = '" + cliente.getNombre() + "', " +
                                             "apellido = '" + cliente.getApellido() + "', " +
                                               "cedula = '" + cliente.getCedula() + "', " +
                                             "telefono = '" + cliente.getTelefono() + "', " +
                                            "direccion = '" + cliente.getDireccion() + "'" +
                                            " WHERE id = " + QString::number(cliente.getId()));
    }
    return cliente.errores;
}

bool DB::eliminarCliente(Cliente cliente)
{
    QSqlQuery q;
    bool destroyed = false;
    qDebug() << "Eliminar cliente";
    q = this->excecute("SELECT COUNT(*) FROM facturas WHERE cliente_id = " + QString::number(cliente.getId()));
    q.next();
    if (q.value(0).toInt() == 0)
    {
        q = this->excecute("DELETE FROM clientes WHERE id = " + QString::number(cliente.getId()));
        destroyed = true;
    }
    else
        qDebug() << "No se puede eliminar el cliente porque tiene facturas asociadas";
    return destroyed;
}

QList<Cliente> DB::obtenerClientes()
{
    QSqlQuery q;
    QList<Cliente> clientes;
    qDebug() << "Cargar clientes";
    q = this->excecute("SELECT id, nombre, apellido, cedula, telefono, direccion FROM clientes ORDER BY id" );
    while (q.next())
    {
        clientes << (Cliente(q.value(1).toString(),
                             q.value(2).toString(),
                             q.value(3).toString(),
                             q.value(4).toString(),
                             q.value(5).toString(),
                             q.value(0).toInt()));
    }
    return clientes;
}
