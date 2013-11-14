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
    return this->nombre.trimmed();
}

QString Cliente::getApellido()
{
    return this->apellido.trimmed();
}

QString Cliente::getCedula()
{
    return this->cedula.trimmed();
}

QString Cliente::getDireccion()
{
    return this->direccion.trimmed();
}

QString Cliente::getTelefono()
{
    return this->telefono.trimmed();
}

int Cliente::getId()
{
    return this->id;
}

bool Cliente::valido()
{
    QSqlQuery q;
    this->errores.clear();
    if (this->getNombre() == "")
        this->errores.append("El nombre no puede estar en blanco");
    if (this->getApellido() == "")
        this->errores.append("El apellido no puede estar en blanco");
    if (this->getCedula() == "")
        this->errores.append("La cedula no puede estar en blanco");
    if (this->getTelefono() == "")
        this->errores.append("El telefono no puede estar en blanco");
    if (this->getDireccion() == "")
        this->errores.append("La direccion no puede estar en blanco");
    if (this->getNombre() != "" && this->getApellido() != "")
    {
        qDebug() << "Verificando existencia de Nombre y Apellido";
        q = this->db->excecute(QString("SELECT COUNT(*) FROM clientes WHERE LOWER(nombre) = LOWER('%1') AND LOWER(apellido) = LOWER('%2') AND id != %3")
                               .arg(this->getNombre(),
                                    this->getApellido(),
                                    QString::number(this->getId())));
        q.next();
        if (q.value(0).toInt() > 0)
            this->errores.append("Ya existe un cliente con el mismo nombre y apellido");
    }
    if (this->getCedula() != "")
    {
        qDebug() << "Verificando existencia de cedula";
        q = this->db->excecute(QString("SELECT COUNT(*) FROM clientes WHERE cedula = '%1' AND id != %2")
                               .arg(this->getCedula(),
                                    QString::number(this->getId())));
        q.next();
        if (q.value(0).toInt() > 0)
            this->errores.append("Ya existe un cliente con la misma cedula");
    }
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
            q = this->db->excecute(QString("INSERT INTO clientes (nombre, apellido, cedula, telefono, direccion) values ('%1', '%2', '%3', '%4', '%5')")
                                   .arg(this->getNombre(),
                                        this->getApellido(),
                                        this->getCedula(),
                                        this->getTelefono(),
                                        this->getDireccion()));
        }
        else
        {
            qDebug() << "Actualizar cliente";
            q = this->db->excecute(QString("UPDATE clientes SET nombre = '%1', apellido = '%2', cedula = '%3', telefono = '%4', direccion = '%5' WHERE id = %6")
                                   .arg(this->getNombre(),
                                        this->getApellido(),
                                        this->getCedula(),
                                        this->getTelefono(),
                                        this->getDireccion(),
                                        QString::number(this->getId())));
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
    q = Cliente::db->excecute(QString("SELECT COUNT(*) FROM facturas WHERE cliente_id = %1")
                              .arg(QString::number(this->getId())));
    q.next();
    if (q.value(0).toInt() == 0)
    {
        q = Cliente::db->excecute(QString("DELETE FROM clientes WHERE id = %1")
                                  .arg(QString::number(this->getId())));
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
