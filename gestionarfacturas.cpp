#include "gestionarfacturas.h"
#include "ui_gestionarfacturas.h"
#include "facturaform.h"
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

void GestionarFacturas::habilitarEditarAnular(bool habilitar)
{
    this->ui->actionEditarFactura->setEnabled(habilitar);
    this->ui->actionAnularFactura->setEnabled(habilitar);
}

void GestionarFacturas::actualizarTablaFacturas()
{
    this->tablaFacturas->actualizarFacturas(Factura::obtenerTodas());
    this->habilitarEditarAnular(false);
}

void GestionarFacturas::on_facturasTableWidget_clicked()
{
    this->habilitarEditarAnular(true);
}

void GestionarFacturas::on_actionEditarFactura_triggered()
{
    int fila = this->ui->facturasTableWidget->currentIndex().row();
    Factura factura = this->tablaFacturas->factura(fila);
    FacturaForm facturaForm(factura, this);
    if (facturaForm.exec() == QDialog::Accepted)
    {
        facturaForm.getFactura().guardar();
        this->actualizarTablaFacturas();
    }

}

void GestionarFacturas::on_actionAnularFactura_triggered()
{
    int fila = this->ui->facturasTableWidget->currentIndex().row();
    Factura factura = this->tablaFacturas->factura(fila);
    if (factura.getEstado() != Factura::ANULADA)
    {
        if (QMessageBox::question(this, "Anular factura", QString("¿Esta seguro de querer anular la factura N° %1?").arg(factura.getNumero()))
                == QMessageBox::Yes)
        {
            factura.anular();
            factura.guardar();
            this->actualizarTablaFacturas();
        }
    }
    else
    {
        QMessageBox::information(this, "Anular factura", "La factura ya esta anulada");
    }
}
