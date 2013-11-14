#ifndef GESTIONARCLIENTES_H
#define GESTIONARCLIENTES_H

#include <QMainWindow>
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
    void habilitarEditarEliminar(bool habilitar);
    ~GestionarClientes();

private slots:
    void on_clientesTableWidget_clicked();

    void on_actionNuevo_triggered();

    void on_actionEditar_triggered();

    void on_actionEliminar_triggered();

private:
    Ui::GestionarClientes *ui;
    DB *db;
    TablaClientes *tablaClientes;
};

#endif // GESTIONARCLIENTES_H
