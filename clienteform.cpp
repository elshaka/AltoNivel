#include "clienteform.h"
#include "ui_clienteform.h"

ClienteForm::ClienteForm(QWidget *parent, Cliente cliente, QString titulo) :
    QDialog(parent),
    ui(new Ui::ClienteForm)
{
    ui->setupUi(this);
    this->cliente = cliente;
    this->setWindowTitle(titulo);
    this->ui->lineEditNombre->setText(cliente.getNombre());
    this->ui->lineEditApellido->setText(cliente.getApellido());
    this->ui->lineEditCedula->setText(cliente.getCedula());
}

Cliente ClienteForm::getCliente()
{
    return this->cliente;
}

ClienteForm::~ClienteForm()
{
    delete ui;
}

void ClienteForm::on_buttonBox_accepted()
{
    this->cliente.setNombre(this->ui->lineEditNombre->text());
    this->cliente.setApellido(this->ui->lineEditApellido->text());
    this->cliente.setCedula(this->ui->lineEditCedula->text());
    this->accept();
}
