#ifndef GESTIONARFACTURAS_H
#define GESTIONARFACTURAS_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "db.h"
#include "factura.h"
#include "tablafacturas.h"

namespace Ui {
class GestionarFacturas;
class FacturasTableModel;
}

class GestionarFacturas : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionarFacturas (QWidget *parent = 0);
    void actualizarTablaFacturas();
    void habilitarEditarAnular(bool habilitar);
    ~GestionarFacturas();

private slots:
    void on_facturasTableWidget_clicked();

    void on_actionEditarFactura_triggered();

    void on_actionAnularFactura_triggered();

    void on_radioButtonPorCancelar_clicked();

    void on_radioButtonCanceladas_clicked();

    void on_radioButtonAnuladas_clicked();

    void on_radioButtonTodas_clicked();

    void on_radioButtonPorCancelar_toggled(bool /*checked*/);

private:
    Ui::GestionarFacturas *ui;
    DB *db;
    TablaFacturas *tablaFacturas;
    QSortFilterProxyModel* tablaFiltradaFacturas;
};

#endif // GESTIONARFACTURAS_H
