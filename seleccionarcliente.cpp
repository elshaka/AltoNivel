#include "seleccionarcliente.h"
#include "ui_seleccionarcliente.h"
#include <QMessageBox>

SeleccionarCliente::SeleccionarCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeleccionarCliente)
{
    ui->setupUi(this);
    this->cliente = new Cliente();
    this->ui->existenteWidget->setVisible(false);
    this->tablaClientes = new TablaClientes(Cliente::obtenerTodos(), this);
    this->tablaFiltradaClientes = new QSortFilterProxyModel(this);
    this->tablaFiltradaClientes->setSourceModel(this->tablaClientes);
    this->tablaFiltradaClientes->setFilterKeyColumn(-1);
    this->tablaFiltradaClientes->setFilterCaseSensitivity(Qt::CaseInsensitive);
    this->ui->clientesTableView->setModel(this->tablaFiltradaClientes);
    this->ui->clientesTableView->setColumnWidth(0, 200);
    this->ui->clientesTableView->setColumnWidth(1, 150);
    this->ui->clientesTableView->setColumnWidth(2, 150);
    this->connect(this->ui->filtroLineEdit, SIGNAL(textChanged(QString)), this->tablaFiltradaClientes, SLOT(setFilterRegExp(QString)));
}

Cliente* SeleccionarCliente::getCliente()
{
    return this->cliente;
}

SeleccionarCliente::~SeleccionarCliente()
{
    delete ui;
}

void SeleccionarCliente::on_aceptarPushButton_clicked()
{
    if(this->ui->nuevoRadioButton->isChecked())
    {
        this->cliente->setNombre(this->ui->lineEditNombre->text());
        this->cliente->setApellido(this->ui->lineEditApellido->text());
        this->cliente->setCedula(this->ui->lineEditCedula->text());
        this->cliente->setTelefono(this->ui->lineEditTelefono->text());
        this->cliente->setDireccion(this->ui->plainTextEditDireccion->toPlainText());
        if (this->cliente->valido())
        {
            this->cliente->guardar();
            this->accept();
        }
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
    else
    {
        QModelIndex filaFiltrada = this->ui->clientesTableView->currentIndex();
        int fila = this->tablaFiltradaClientes->mapToSource(filaFiltrada).row();
        if(fila >= 0)
        {
            this->cliente = this->tablaClientes->cliente(fila);
            this->accept();
        }
        else
            QMessageBox::warning(this, "Error", "Debe seleccionar un cliente");
    }
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
