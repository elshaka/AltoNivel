#ifndef GESTIONARFACTURAS_CPP
#define GESTIONARFACTURAS_CPP

#include "gestionarfacturas.h"
#include "ui_gestionarfacturas.h"
#include "clienteform.h"
#include <QMessageBox>

GestionarFacturas::GestionarFacturas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionarFacturas)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->tablaFacturas = new TablaFacturas(Factura::obtenerTodas());
    this->ui->facturasTableWidget->setModel(this->tablaFacturas);
}

GestionarFacturas::~GestionarFacturas()
{
    delete ui;
}

void GestionarFacturas::habilitarEditarEliminar(bool habilitar)
{
    this->ui->actionEditarFactura->setEnabled(habilitar);
    this->ui->actionEliminarFactura->setEnabled(habilitar);
}

void GestionarFacturas::actualizarTablaFacturas()
{
    this->tablaFacturas->actualizarFacturas(Factura::obtenerTodas());
    this->habilitarEditarEliminar(false);
}

void GestionarFacturas::on_facturasTableWidget_clicked()
{
    this->habilitarEditarEliminar(true);
}
/*
void GestionarFacturas::on_actionEditarFactura_triggered()
{
    int fila = this->ui->facturasTableWidget->currentIndex().row();
    ClienteForm clienteForm(this, this->tablaClientes->cliente(fila));
    if (clienteForm.exec() == QDialog::Accepted)
    {
        clienteForm.getCliente().guardar();
        this->actualizarTablaFacturas();
    }
}

void GestionarFacturas::on_actionEliminarFactura_triggered()
{
    int fila = this->ui->facturasTableWidget->currentIndex().row();
    Factura factura = this->tablaFacturas->factura(fila);
    if (QMessageBox::question(this, "Eliminar factura", "¿Esta seguro de querer eliminar la factura "+factura.getNumero()+"?")
            == QMessageBox::Yes)
    {
        if (factura.eliminar())
            this->actualizarTablaFacturas();
        else
            QMessageBox::warning(this, "No se puede eliminar el cliente", "El cliente no se puede eliminar porque tiene facturas asociadas");
    }
}
*/
#endif // GESTIONARFACTURAS_CPP

void GestionarFacturas::on_actionEditarFactura_triggered()
{

}

void GestionarFacturas::on_actionEliminarFactura_triggered()
{

}
