#include "gestionarclientes.h"
#include "ui_gestionarclientes.h"
#include "clienteform.h"
#include <QMessageBox>
#include <QDebug>

GestionarClientes::GestionarClientes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionarClientes)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->tablaClientes = new TablaClientes(Cliente::obtenerTodos());
    this->ui->clientesTableWidget->setModel(this->tablaClientes);
}

GestionarClientes::~GestionarClientes()
{
    delete ui;
}

void GestionarClientes::habilitarEditarEliminar(bool habilitar)
{
    this->ui->actionEditar->setEnabled(habilitar);
    this->ui->actionEliminar->setEnabled(habilitar);
}

void GestionarClientes::actualizarTablaClientes()
{
    this->tablaClientes->actualizarClientes(Cliente::obtenerTodos());
    this->habilitarEditarEliminar(false);
}

void GestionarClientes::on_clientesTableWidget_clicked()
{
    this->habilitarEditarEliminar(true);
}

void GestionarClientes::on_actionNuevo_triggered()
{
    ClienteForm clienteForm(this);
    if (clienteForm.exec() == QDialog::Accepted)
    {
        clienteForm.getCliente().guardar();
        this->actualizarTablaClientes();
    }
}

void GestionarClientes::on_actionEditar_triggered()
{
    int fila = this->ui->clientesTableWidget->currentIndex().row();
    ClienteForm clienteForm(this, this->tablaClientes->cliente(fila));
    if (clienteForm.exec() == QDialog::Accepted)
    {
        clienteForm.getCliente().guardar();
        this->actualizarTablaClientes();
    }
}

void GestionarClientes::on_actionEliminar_triggered()
{
    int fila = this->ui->clientesTableWidget->currentIndex().row();
    Cliente cliente = this->tablaClientes->cliente(fila);
    if (QMessageBox::question(this, "Eliminar cliente", "¿Esta seguro de querer eliminar al cliente "+cliente.getNombre()+"?")
            == QMessageBox::Yes)
    {
        if (cliente.eliminar())
            this->actualizarTablaClientes();
        else
            QMessageBox::warning(this, "No se puede eliminar el cliente", "El cliente no se puede eliminar porque tiene facturas asociadas");
    }
}
