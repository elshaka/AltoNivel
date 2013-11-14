#ifndef GESTIONARCLIENTES_H
#define GESTIONARCLIENTES_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "db.h"
#include "cliente.h"
#include "tablaclientes.h"

namespace Ui {
class GestionarClientes;
class ClientesTableModel;
}

class GestionarClientes : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionarClientes(QWidget *parent = 0);
    void actualizarTablaClientes();
    ~GestionarClientes();

private slots:
    void on_clientesTableWidget_clicked();

    void on_actionNuevo_triggered();

    void on_actionEditar_triggered();

    void on_actionEliminar_triggered();

    void habilitarEditarEliminar();

private:
    Ui::GestionarClientes *ui;
    DB *db;
    TablaClientes *tablaClientes;
    QSortFilterProxyModel* tablaFiltradaClientes;
};

#endif // GESTIONARCLIENTES_H
