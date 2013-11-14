#ifndef TABLAFACTURAS_H
#define TABLAFACTURAS_H
#include "factura.h"

class TablaFacturas : public QAbstractTableModel
{
    Q_OBJECT
public:
    TablaFacturas(QList<Factura *> facturas, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Factura *factura(int fila);
    void actualizarFacturas(QList<Factura *> facturas);
private:
    QList<Factura *> facturas;
    static QList<QString> headers;
};

#endif // TABLAFACTURAS_H
