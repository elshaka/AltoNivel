#ifndef TABLACLIENTES_H
#define TABLACLIENTES_H
#include "cliente.h"
#include <QSize>

class TablaClientes : public QAbstractTableModel
{
    Q_OBJECT
public:
    TablaClientes(QList<Cliente> clientes, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Cliente cliente(int fila);
    void actualizarClientes(QList<Cliente> clientes);
private:
    QList<Cliente> clientes;
    static QList<QString> headers;
};

#endif // TABLACLIENTES_H
