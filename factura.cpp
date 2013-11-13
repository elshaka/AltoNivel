#include "factura.h"

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
    this->fechaEmision = NULL;
    this->monto = 0;
    this->estado = Factura::PORCANCELAR;
    this->numero = 0;
    this->id = 0;
}

Factura::Factura(Cliente &cliente, QDateTime &fechaEmision, float monto, QString estado, int numero, int id)
{
    this->tipo = Factura::CONTADO;
    this->cliente = &cliente;
    this->fechaEmision = &fechaEmision;
    this->monto = monto;
    this->estado = estado;
    this->numero = numero;
    this->id = id;
}

void Factura::setTipo(QString tipo)
{
    this->tipo = tipo;
}

void Factura::setCliente(Cliente &cliente)
{
    this->cliente = &cliente;
}

void Factura::setFechaEmision(QDateTime &fechaEmision)
{
    this->fechaEmision = &fechaEmision;
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

int Factura::getNumero()
{
    return this->numero;
}

QDateTime* Factura::getFechaEmision()
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
    if (!this->cliente->valido())
        this->errores.append("El cliente no es valido");
    if (!this->getFechaEmision()->isValid())
        this->errores.append("La fecha de emision no es valida");
    if (!this->monto > 0)
        this->errores.append("El monto es invalido");
    if (!Factura::ESTADOS.contains(this->getEstado()))
        this->errores.append("El estado es invalido");
    return this->errores.size() == 0;
}

FacturaCredito::FacturaCredito() : Factura()
{
    this->setTipo(Factura::CREDITO);
    this->fechaVencimiento = new QDateTime();
    this->saldoPendiente = 0;
}

FacturaCredito::FacturaCredito(Cliente &cliente, QDateTime &fechaEmision, QDateTime &fechaVencimiento, float monto, float saldoPendiente, QString estado, int numero, int id) :
    Factura(cliente, fechaEmision, monto, estado, numero, id)
{
    this->setTipo(Factura::CREDITO);
    this->fechaVencimiento = &fechaVencimiento;
    this->saldoPendiente = saldoPendiente;
}

void FacturaCredito::setFechaVencimiento(QDateTime &fechaVencimiento)
{
    this->fechaVencimiento = &fechaVencimiento;
}

void FacturaCredito::setSaldoPendiente(float saldoPendiente)
{
    this->saldoPendiente = saldoPendiente;
}

QDateTime* FacturaCredito::getFechaVencimiento()
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

bool FacturaCredito::valida()
{
    Factura::valida();
    // Validaciones de factura a credito
    return this->errores.size() == 0;
}
