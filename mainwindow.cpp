#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clienteform.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->actualizarListaClientes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarListaClientes()
{
    QList<Cliente>::iterator i;

    this->ui->listWidget->clear();

    this->clientes = this->db.find_all();

    for (i = this->clientes.begin(); i != this->clientes.end(); ++i)
        this->ui->listWidget->addItem(new QListWidgetItem((*i).getNombre()));
    this->deshabilitarEditarEliminar();
}

void MainWindow::habilitarEditarEliminar()
{
    this->ui->actionEditar->setEnabled(true);
    this->ui->actionEliminar->setEnabled(true);
}

void MainWindow::deshabilitarEditarEliminar()
{
    this->ui->actionEditar->setEnabled(false);
    this->ui->actionEliminar->setEnabled(false);
}

void MainWindow::on_listWidget_clicked()
{
    this->habilitarEditarEliminar();
}

void MainWindow::on_actionNuevo_triggered()
{
    ClienteForm clienteForm(this);
    if (clienteForm.exec() == QDialog::Accepted)
    {
        this->db.create(clienteForm.getCliente());
        this->actualizarListaClientes();
    }
}

void MainWindow::on_actionEditar_triggered()
{
    int row = this->ui->listWidget->currentRow();
    ClienteForm clienteForm(this, this->clientes.at(row), "Editar cliente");
    if (clienteForm.exec() == QDialog::Accepted)
    {
        this->db.update(clienteForm.getCliente());
        this->actualizarListaClientes();
    }
}

void MainWindow::on_actionEliminar_triggered()
{
    int row = this->ui->listWidget->currentRow();
    Cliente cliente = this->clientes.at(row);
    if (QMessageBox::question(this, "Eliminar cliente", "¿Esta seguro de querer eliminar al cliente "+cliente.getNombre()+"?")
            == QMessageBox::Yes)
    {
        this->db.destroy(this->clientes.at(row));
        this->actualizarListaClientes();
    }
}
