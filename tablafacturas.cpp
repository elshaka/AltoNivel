#include "tablafacturas.h"
#include <QColor>
#include <QBrush>

QList<QString> TablaFacturas::headers = QList<QString>() << "Numero"
                                                         << "Cliente"
                                                         << "Tipo"
                                                         << "Estado"
                                                         << "Monto"
                                                         << "Pendiente"
                                                         << "Emitida"
                                                         << "Vence";

TablaFacturas::TablaFacturas(QList<Factura*> facturas, QObject *parent) :
    QAbstractTableModel(parent)
{
    this->facturas = facturas;
}

int TablaFacturas::rowCount(const QModelIndex & /*&parent*/) const
{
    return this->facturas.size();
}

int TablaFacturas::columnCount(const QModelIndex & /*&parent*/) const
{
    return TablaFacturas::headers.size();
}

QVariant TablaFacturas::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return TablaFacturas::headers.at(section);
    }
    return QVariant();
}

QVariant TablaFacturas::data(const QModelIndex &index, int role) const
{
    Factura* factura = this->facturas.at(index.row());
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0: return QString::number(factura->getNumero());
        case 1: return QString("%1 %2").arg(factura->getCliente()->getNombre(),
                                            factura->getCliente()->getApellido());
        case 2: return factura->getTipo();
        case 3: return factura->getEstado();
        case 4: return QString::number(factura->getMonto());
        case 5: return QString::number(factura->getSaldoPendiente());
        case 6: return factura->getFechaEmision().toString(Factura::FORMATOFECHA);
        case 7: return factura->getFechaVencimiento().toString(Factura::FORMATOFECHA);
        }
    }
    else if (role == Qt::BackgroundRole && index.column() == 3)
    {
        int row = index.row();
        QString estado = this->facturas.at(row)->getEstado();
        if (estado == Factura::CANCELADA)
            return QBrush(QColor(122, 195, 106));
        if (estado == Factura::PORCANCELAR)
            return QBrush(QColor(250, 167, 91));
        if (estado == Factura::ANULADA)
            return QBrush(QColor(241, 90, 96));
    }
    return QVariant();
}

Factura* TablaFacturas::factura(int fila)
{
    return this->facturas.at(fila);
}

void TablaFacturas::actualizarFacturas(QList<Factura*> facturas)
{
    this->beginResetModel();
    qDeleteAll(this->facturas.begin(), this->facturas.end());
    this->facturas = facturas;
    this->endResetModel();
}

TablaFacturas::~TablaFacturas()
{
    qDeleteAll(this->facturas.begin(), this->facturas.end());
}
