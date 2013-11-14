#include "clienteform.h"
#include "ui_clienteform.h"
#include <QMessageBox>

ClienteForm::ClienteForm(QWidget *parent, Cliente* cliente, QString titulo) :
    QDialog(parent),
    ui(new Ui::ClienteForm)
{
    ui->setupUi(this);
    if(cliente == NULL)
        this->cliente = new Cliente();
    else
        this->cliente = cliente;
    this->setWindowTitle(titulo);
    this->ui->lineEditNombre->setText(this->cliente->getNombre());
    this->ui->lineEditApellido->setText(this->cliente->getApellido());
    this->ui->lineEditCedula->setText(this->cliente->getCedula());
    this->ui->lineEditTelefono->setText(this->cliente->getTelefono());
    this->ui->plainTextEditDireccion->setPlainText(this->cliente->getDireccion());
}

Cliente* ClienteForm::getCliente()
{
    return this->cliente;
}

ClienteForm::~ClienteForm()
{
    delete ui;
}

void ClienteForm::on_pushButtonAceptar_clicked()
{
    this->cliente->setNombre(this->ui->lineEditNombre->text());
    this->cliente->setApellido(this->ui->lineEditApellido->text());
    this->cliente->setCedula(this->ui->lineEditCedula->text());
    this->cliente->setTelefono(this->ui->lineEditTelefono->text());
    this->cliente->setDireccion(this->ui->plainTextEditDireccion->toPlainText());
    if (this->cliente->valido())
        this->accept();
    else
    {
        QString mensaje = "";
        QList<QString>::Iterator i;
        QList<QString> errores = this->cliente->errores;
        for(i = errores.begin(); i != errores.end(); ++i)
            mensaje.append(QString("- %1\n").arg(*i));
        QMessageBox::warning(this, "Atributos invalidos", mensaje);
    }
}

void ClienteForm::on_pushButtonCancelar_clicked()
{
    delete this->cliente;
    this->reject();
}
