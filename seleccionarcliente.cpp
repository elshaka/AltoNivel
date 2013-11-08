#include "seleccionarcliente.h"
#include "ui_seleccionarcliente.h"

SeleccionarCliente::SeleccionarCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeleccionarCliente)
{
    ui->setupUi(this);
    this->ui->existenteWidget->setVisible(false);

}

SeleccionarCliente::~SeleccionarCliente()
{
    delete ui;
}

void SeleccionarCliente::on_aceptarPushButton_clicked()
{
    this->accept();
}

void SeleccionarCliente::on_cancelarPushButton_clicked()
{
    this->reject();
}

void SeleccionarCliente::on_nuevoRadioButton_toggled(bool checked)
{
    this->ui->nuevoWidget->setVisible(checked);
    this->ui->existenteWidget->setVisible(!checked);
}
