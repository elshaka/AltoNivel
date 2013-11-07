#include "clienteform.h"
#include "ui_clienteform.h"
#include <QMessageBox>

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
    this->ui->lineEditTelefono->setText(cliente.getTelefono());
    this->ui->plainTextEditDireccion->setPlainText(cliente.getDireccion());
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
    this->cliente.setTelefono(this->ui->lineEditTelefono->text());
    this->cliente.setDireccion(this->ui->plainTextEditDireccion->toPlainText());
    if (this->cliente.valido())
        this->accept();
    else
    {
        QString mensaje = "";
        QList<QString>::Iterator i;
        QList<QString> errores = this->cliente.errores;
        for(i = errores.begin(); i != errores.end(); ++i)
            mensaje.append(QString("- %1\n").arg(*i));
        QMessageBox::warning(this, "Atributos invalidos", mensaje);
    }
}
