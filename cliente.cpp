#include "cliente.h"

DB* Cliente::db = new DB();

Cliente::Cliente()
{
    this->nombre = "";
    this->apellido = "";
    this->cedula = "";
    this->telefono = "";
    this->direccion = "";
    this->id = 0;
}

Cliente::Cliente(QString nombre, QString apellido, QString cedula, QString telefono, QString direccion, int id)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->cedula = cedula;
    this->direccion = direccion;
    this->telefono = telefono;
    this->id = id;
}

void Cliente::setNombre(QString nombre)
{
    this->nombre = nombre;
}

void Cliente::setApellido(QString apellido)
{
    this->apellido = apellido;
}

void Cliente::setCedula(QString cedula)
{
    this->cedula = cedula;
}

void Cliente::setDireccion(QString direccion)
{
    this->direccion = direccion;
}

void Cliente::setTelefono(QString telefono)
{
    this->telefono = telefono;
}

QString Cliente::getNombre()
{
    return this->nombre;
}

QString Cliente::getApellido()
{
    return this->apellido;
}

QString Cliente::getCedula()
{
    return this->cedula;
}

QString Cliente::getDireccion()
{
    return this->direccion;
}

QString Cliente::getTelefono()
{
    return this->telefono;
}

int Cliente::getId()
{
    return this->id;
}

bool Cliente::valido()
{
    this->errores.clear();
    // Agregar validaciones
    return this->errores.size() == 0;
}

bool Cliente::guardar()
{
    QSqlQuery q;
    if (this->valido())
    {
        if (this->getId() == 0)
        {
            qDebug() << "Crear nuevo cliente";
            q = this->db->excecute("INSERT INTO clientes (nombre, apellido, cedula, telefono, direccion) values ('" +
                                this->getNombre() + "','" +
                                this->getApellido() + "','" +
                                this->getCedula() + "','" +
                                this->getTelefono() + "','" +
                                this->getDireccion() + "')");
        }
        else
        {
            qDebug() << "Actualizar cliente";
            q = this->db->excecute("UPDATE clientes SET nombre = '" + this->getNombre() + "', " +
                                   "apellido = '" + this->getApellido() + "', " +
                                   "cedula = '" + this->getCedula() + "', " +
                                   "telefono = '" + this->getTelefono() + "', " +
                                   "direccion = '" + this->getDireccion() + "'" +
                                   " WHERE id = " + QString::number(this->getId()));
        }
        return true;
    }
    return false;
}

bool Cliente::eliminar()
{
    QSqlQuery q;
    bool eliminado = false;
    qDebug() << "Eliminar cliente";
    q = Cliente::db->excecute("SELECT COUNT(*) FROM facturas WHERE cliente_id = " + QString::number(this->getId()));
    q.next();
    if (q.value(0).toInt() == 0)
    {
        q = Cliente::db->excecute("DELETE FROM clientes WHERE id = " + QString::number(this->getId()));
        eliminado = true;
    }
    else
        qDebug() << "No se puede eliminar el cliente porque tiene facturas asociadas";
    return eliminado;
}

QList<Cliente> Cliente::obtenerTodos()
{
    QSqlQuery q;
    QList<Cliente> clientes;
    qDebug() << "Cargar clientes";
    q = Cliente::db->excecute("SELECT id, nombre, apellido, cedula, telefono, direccion FROM clientes ORDER BY id" );
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

Cliente::~Cliente() {}
