#include "tablafacturas.h"

QList<QString> TablaFacturas::headers = QList<QString>() << "Numero"
                                                         << "Cliente"
                                                         << "Tipo"
                                                         << "Monto"
                                                         << "Pendiente"
                                                         << "Emitida"
                                                         << "Vence";

TablaFacturas::TablaFacturas(QList<Factura> facturas, QObject *parent) :
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
    Factura factura = this->facturas.at(index.row());
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0: return QString::number(factura.getNumero());
        case 1: return QString("%1 %2").arg(factura.getCliente()->getNombre(),
                                            factura.getCliente()->getApellido());
        case 2: return factura.getTipo();
        case 3: return QString::number(factura.getMonto());
        case 4: return QString::number(factura.getSaldoPendiente());
        case 5: return factura.getFechaEmision().toString(DB::formatoFecha);
        case 6: return factura.getFechaVencimiento().toString(DB::formatoFecha);
        }
    }
    return QVariant();
}

Factura TablaFacturas::factura(int fila)
{
    return this->facturas.at(fila);
}

void TablaFacturas::actualizarFacturas(QList<Factura> facturas)
{
    this->beginResetModel();
    this->facturas = facturas;
    this->endResetModel();
}
