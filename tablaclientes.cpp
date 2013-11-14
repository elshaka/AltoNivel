#include "tablaclientes.h"

QList<QString> TablaClientes::headers = QList<QString>() << "Nombre y Apellido"
                                                         << "Cedula"
                                                         << "Telefono"
                                                         << "Direccion";

TablaClientes::TablaClientes(QList<Cliente> clientes, QObject *parent) :
    QAbstractTableModel(parent)
{
    this->clientes = clientes;
}

int TablaClientes::rowCount(const QModelIndex & /*&parent*/) const
{
    return this->clientes.size();
}

int TablaClientes::columnCount(const QModelIndex & /*&parent*/) const
{
    return TablaClientes::headers.size();
}

QVariant TablaClientes::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return TablaClientes::headers.at(section);
    }
    return QVariant();
}

QVariant TablaClientes::data(const QModelIndex &index, int role) const
{
    Cliente cliente = this->clientes.at(index.row());
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0: return QString("%1 %2").arg(cliente.getNombre(), cliente.getApellido());
        case 1: return cliente.getCedula();
        case 2: return cliente.getTelefono();
        case 3: return cliente.getDireccion();
        }
    }
    return QVariant();
}

Cliente* TablaClientes::cliente(int fila)
{
    return new Cliente(this->clientes.at(fila));
}

void TablaClientes::actualizarClientes(QList<Cliente> clientes)
{
    this->beginResetModel();
    this->clientes = clientes;
    this->endResetModel();
}
