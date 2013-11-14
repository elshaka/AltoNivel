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
    this->tablaFiltradaClientes = new QSortFilterProxyModel(this);
    this->tablaFiltradaClientes->setSourceModel(this->tablaClientes);
    this->tablaFiltradaClientes->setFilterKeyColumn(-1);
    this->tablaFiltradaClientes->setFilterCaseSensitivity(Qt::CaseInsensitive);
    this->ui->clientesTableWidget->setModel(this->tablaFiltradaClientes);
    this->ui->clientesTableWidget->setColumnWidth(0, 200);
    this->ui->clientesTableWidget->setColumnWidth(1, 150);
    this->ui->clientesTableWidget->setColumnWidth(2, 150);
    this->ui->clientesTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->connect(this->ui->filtroLineEdit, SIGNAL(textChanged(QString)), this->tablaFiltradaClientes, SLOT(setFilterRegExp(QString)));
    this->connect(this->ui->filtroLineEdit, SIGNAL(textChanged(QString)), this, SLOT(habilitarEditarEliminar()));
}

GestionarClientes::~GestionarClientes()
{
    delete ui;
}

void GestionarClientes::habilitarEditarEliminar()
{
    bool habilitar = false;
    if(this->ui->clientesTableWidget->currentIndex().row() >= 0)
        habilitar = true;
    this->ui->actionEditar->setEnabled(habilitar);
    this->ui->actionEliminar->setEnabled(habilitar);
}

void GestionarClientes::actualizarTablaClientes()
{
    this->tablaClientes->actualizarClientes(Cliente::obtenerTodos());
    this->habilitarEditarEliminar();
}

void GestionarClientes::on_clientesTableWidget_clicked()
{
    this->habilitarEditarEliminar();
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
    QModelIndex filaFiltrada = this->ui->clientesTableWidget->currentIndex();
    int fila = this->tablaFiltradaClientes->mapToSource(filaFiltrada).row();
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
