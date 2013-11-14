#ifndef GESTIONARFACTURAS_H
#define GESTIONARFACTURAS_H

#include <QMainWindow>
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

private:
    Ui::GestionarFacturas *ui;
    DB *db;
    TablaFacturas *tablaFacturas;
};

#endif // GESTIONARFACTURAS_H
