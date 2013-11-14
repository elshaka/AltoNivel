#include "factura.h"

QString Factura::FORMATOFECHA = "d 'de' MMMM 'de' yyyy. hh:mm:ss";

QString Factura::PORCANCELAR = "PORCANCELAR";
QString Factura::CANCELADA = "CANCELADA";
QString Factura::ANULADA = "ANULADA";
QList<QString> Factura::ESTADOS = QList<QString>() << Factura::PORCANCELAR
                                                   << Factura::CANCELADA
                                                   << Factura::ANULADA;

QString Factura::CONTADO = "CONTADO";
QString Factura::CREDITO = "CREDITO";
QList<QString> Factura::TIPOS = QList<QString>() << Factura::CONTADO
                                                 << Factura::CREDITO;

DB* Factura::db = new DB();

Factura::Factura()
{
    this->tipo = Factura::CONTADO;
    this->cliente = NULL;
    this->fechaEmision = QDateTime();
    this->monto = 0;
    this->estado = Factura::PORCANCELAR;
    this->numero = 0;
    this->id = 0;
}

Factura::Factura(Cliente* cliente, QDateTime fechaEmision, float monto, QString estado, int numero, int id)
{
    this->tipo = Factura::CONTADO;
    this->cliente = cliente;
    this->fechaEmision = fechaEmision;
    this->monto = monto;
    this->estado = estado;
    this->numero = numero;
    this->id = id;
}

void Factura::setTipo(QString tipo)
{
    this->tipo = tipo;
}

void Factura::setCliente(Cliente* cliente)
{
    this->cliente = cliente;
}

void Factura::setFechaEmision(QDateTime fechaEmision)
{
    this->fechaEmision = fechaEmision;
}

void Factura::setMonto(float monto)
{
    this->monto = monto;
}

void Factura::setEstado(QString estado)
{
    this->estado = estado;
}

Cliente* Factura::getCliente()
{
    return this->cliente;
}

QString Factura::getTipo()
{
    return this->tipo;
}

int Factura::getId()
{
    return this->id;
}

int Factura::getNumero()
{
    return this->numero;
}

QDateTime Factura::getFechaEmision()
{
    return this->fechaEmision;
}

float Factura::getMonto()
{
    return this->monto;
}

QString Factura::getEstado()
{
    return this->estado;
}

bool Factura::cancelar()
{
    if (this->getEstado() != Factura::ANULADA)
    {
        this->setEstado(Factura::CANCELADA);
        return true;
    }
    return false;
}

void Factura::anular()
{
    this->setEstado(Factura::ANULADA);
}

bool Factura::valida()
{
    this->errores.clear();
    if (this->cliente == NULL)
        this->errores.append("No se ha seleccionado un cliente");
    else
    {
        QSqlQuery q;
        qDebug() << "Verificando existencia del cliente";
        q = this->db->excecute(QString("SELECT COUNT(*) FROM clientes WHERE id = %1")
                               .arg(this->cliente->getId()));
        q.next();
        if (q.value(0).toInt() != 1)
            this->errores.append("El cliente no es valido");
    }
    if (!this->getFechaEmision().isValid())
        this->errores.append("La fecha de emision no es valida");
    if (!this->monto > 0)
        this->errores.append("El monto es invalido");
    if (!Factura::ESTADOS.contains(this->getEstado()))
        this->errores.append("El estado es invalido");
    return this->errores.size() == 0;
}

bool Factura::guardar()
{
    QSqlQuery q;
    if (this->valida())
    {
        if (this->getId() == 0)
        {
            qDebug() << "Crear nueva factura";
            QString fechaVencimiento = this->getFechaVencimiento().isNull() ? "NULL" : QString("'%1'").arg(this->getFechaVencimiento().toString(DB::FORMATOFECHA));
            q = this->db->excecute(QString("INSERT INTO facturas (cliente_id, tipo, fecha_emision, fecha_vencimiento, monto, saldo_pendiente, estado) "
                                   "values ('%1', '%2', '%3', %4, '%5', '%6', '%7') RETURNING id")
                                   .arg(QString::number(this->cliente->getId()),
                                        this->getTipo(),
                                        this->getFechaEmision().toString(DB::FORMATOFECHA),
                                        fechaVencimiento,
                                        QString::number(this->getMonto()),
                                        QString::number(this->getSaldoPendiente()),
                                        this->getEstado()));
            q.next();
            this->id = q.value(0).toInt();
        }
        else
        {
            qDebug() << "Actualizar factura";
            q = this->db->excecute(QString("UPDATE facturas SET saldo_pendiente = %1, estado = '%2' WHERE id = %3")
                                   .arg(QString::number(this->getSaldoPendiente()),
                                        this->getEstado(),
                                        QString::number(this->getId())));
        }
        return true;
    }
    return false;
}

bool Factura::eliminar()
{
    QSqlQuery q;
    qDebug() << "Eliminar factura";
    q = Factura::db->excecute("DELETE FROM facturas WHERE id = " + QString::number(this->getId()));
    return true;
}

QList<Factura> Factura::obtenerTodas()
{
    QSqlQuery q;
    QList<Factura> facturas;
    qDebug() << "Cargar facturas";
    q = Factura::db->excecute("SELECT clientes.id, nombre, apellido, cedula, telefono, direccion, "
                              "facturas.id, numero, tipo, fecha_emision, fecha_vencimiento, monto, saldo_pendiente, estado "
                              "FROM facturas INNER JOIN clientes ON clientes.id = facturas.cliente_id "
                              "ORDER BY fecha_emision DESC");
    while (q.next())
    {
        Cliente* cliente = new Cliente(q.value(1).toString(),
                                       q.value(2).toString(),
                                       q.value(3).toString(),
                                       q.value(4).toString(),
                                       q.value(5).toString(),
                                       q.value(0).toInt());
        if (q.value(8) == Factura::CONTADO)
            facturas << Factura(cliente,
                                q.value(9).toDateTime(),
                                q.value(11).toFloat(),
                                q.value(13).toString(),
                                q.value(7).toInt(),
                                q.value(6).toInt());
        else
            facturas << FacturaCredito(cliente,
                                       q.value(9).toDateTime(),
                                       q.value(10).toDateTime(),
                                       q.value(11).toFloat(),
                                       q.value(12).toFloat(),
                                       q.value(13).toString(),
                                       q.value(7).toInt(),
                                       q.value(6).toInt());
    }
    return facturas;
}

Factura::~Factura()
{
    //delete this->cliente;
}

FacturaCredito::FacturaCredito() : Factura()
{
    this->setTipo(Factura::CREDITO);
    this->fechaVencimiento = QDateTime();
    this->saldoPendiente = 0;
}

FacturaCredito::FacturaCredito(Cliente* cliente, QDateTime fechaEmision, QDateTime fechaVencimiento, float monto, float saldoPendiente, QString estado, int numero, int id) :
    Factura(cliente, fechaEmision, monto, estado, numero, id)
{
    this->setTipo(Factura::CREDITO);
    this->fechaVencimiento = fechaVencimiento;
    this->saldoPendiente = saldoPendiente;
}

void FacturaCredito::setFechaVencimiento(QDateTime fechaVencimiento)
{
    this->fechaVencimiento = fechaVencimiento;
}

void FacturaCredito::setSaldoPendiente(float saldoPendiente)
{
    this->saldoPendiente = saldoPendiente;
}

QDateTime FacturaCredito::getFechaVencimiento()
{
    return this->fechaVencimiento;
}

float FacturaCredito::getSaldoPendiente()
{
    return this->saldoPendiente;
}

bool FacturaCredito::abonar(float abono)
{
    if(abono > 0 && (this->saldoPendiente + abono) <= this->getMonto())
    {
        this->saldoPendiente -= abono;
        if (this->saldoPendiente == 0)
            this->setEstado(Factura::CANCELADA);
        return true;
    }
    return false;
}

bool FacturaCredito::cancelar()
{
    if (this->getEstado() != Factura::ANULADA && this->getSaldoPendiente() == 0)
    {
        this->setEstado(Factura::CANCELADA);
        return true;
    }
    return false;
}

bool FacturaCredito::valida()
{
    Factura::valida();
    if(!this->getFechaVencimiento().isValid())
        this->errores.append("La fecha de vencimiento no es valida");
    else if(this->getFechaVencimiento() < this->getFechaEmision())
        this->errores.append("La fecha de vencimiento debe ser mayor a la fecha de emision");
    if(this->getSaldoPendiente() <= 0 || (this->getMonto() - this->getSaldoPendiente()) <= 0)
        this->errores.append("El abono es invalido");
    if(this->getId() != 0 && this->getEstado() == Factura::PORCANCELAR && this->getSaldoPendiente() == 0)
        this->errores.append("La factura no puede tener saldo pendiente 0");
    return this->errores.size() == 0;
}
