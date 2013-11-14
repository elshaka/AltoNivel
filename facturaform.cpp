#include "facturaform.h"
#include "ui_facturaform.h"
#include <QMessageBox>

FacturaForm::FacturaForm(Factura* factura, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FacturaForm)
{
    ui->setupUi(this);
    this->factura = factura;
    if (this->factura->getTipo() == Factura::CONTADO)
        this->ui->groupBoxCredito->hide();
    this->actualizarCampos();
}

Factura* FacturaForm::getFactura()
{
    return this->factura;
}

void FacturaForm::actualizarCampos()
{
    this->ui->lineEditNumero->setText(QString::number(this->factura->getNumero()));
    this->ui->lineEditCliente->setText(QString("%1 %2").arg(this->factura->getCliente()->getNombre(),
                                                            this->factura->getCliente()->getApellido()));
    this->ui->lineEditTipo->setText(this->factura->getTipo());
    this->ui->lineEditEstado->setText(this->factura->getEstado());
    this->ui->lineEditMonto->setText(QString::number(this->factura->getMonto()));
    this->ui->dateTimeEditFechaEmision->setDateTime(this->factura->getFechaEmision());
    this->ui->dateTimeEditFechaVencimiento->setDateTime(this->factura->getFechaVencimiento());
    this->ui->lineEditSaldoPendiente->setText(QString::number(this->factura->getSaldoPendiente()));
    this->ui->lineEditAbono->setText("");
    if(this->factura->getEstado() == Factura::CANCELADA || this->factura->getEstado() == Factura::ANULADA)
    {
        this->ui->pushButtonCancelar->setEnabled(false);
        this->ui->pushButtonAbonar->setEnabled(false);
        this->ui->lineEditAbono->setEnabled(false);
    }
}

FacturaForm::~FacturaForm()
{
    delete ui;
}

void FacturaForm::on_pushButtonCancelar_clicked()
{
    if(this->factura->cancelar())
        this->actualizarCampos();
    else
        QMessageBox::warning(this, "Error", "No se puede cancelar la factura en el estado actual");
}

void FacturaForm::on_pushButtonDescartar_clicked()
{
    this->reject();
}

void FacturaForm::on_pushButtonAbonar_clicked()
{
    float abono = this->ui->lineEditAbono->text().toFloat();
    if(this->factura->abonar(abono))
        this->actualizarCampos();
    else
        QMessageBox::warning(this, "Error", "El monto a abonar no es valido");
}

void FacturaForm::on_pushButtonAceptar_clicked()
{
    this->accept();
}
