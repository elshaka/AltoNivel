#include "gestionarclientes.h"
#include "ui_gestionarclientes.h"
#include "clienteform.h"
#include <QMessageBox>

QList<QString> ClientesTableModel::headers = QList<QString>() << "Nombre"
                                                              << "Apellido"
                                                              << "Cedula"
                                                              << "Telefono"
                                                              << "Direccion";

ClientesTableModel::ClientesTableModel(QList<Cliente> clientes, QObject *parent) :
    QAbstractTableModel(parent)
{
    this->clientes = clientes;
}

int ClientesTableModel::rowCount(const QModelIndex & /*&parent*/) const
{
    return this->clientes.size();
}

int ClientesTableModel::columnCount(const QModelIndex & /*&parent*/) const
{
    return ClientesTableModel::headers.size();
}

QVariant ClientesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return ClientesTableModel::headers.at(section);
    }
    return QVariant();
}

QVariant ClientesTableModel::data(const QModelIndex &index, int role) const
{
    Cliente cliente = this->clientes.at(index.row());
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
            case 0: return cliente.getNombre();
            case 1: return cliente.getApellido();
            case 2: return cliente.getCedula();
            case 3: return cliente.getTelefono();
            case 4: return cliente.getDireccion();
        }
    }
    return QVariant();
}

Cliente ClientesTableModel::cliente(int fila)
{
    return this->clientes.at(fila);
}

void ClientesTableModel::actualizarClientes(QList<Cliente> clientes)
{
    this->beginResetModel();
    this->clientes = clientes;
    this->endResetModel();
}

GestionarClientes::GestionarClientes(DB *db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionarClientes)
{
    ui->setupUi(this);
    this->db = db;
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->tablaClientes = new ClientesTableModel(Cliente::obtenerTodos());
    this->ui->clientesTableWidget->setModel(this->tablaClientes);
}

GestionarClientes::~GestionarClientes()
{
    delete ui;
}

void GestionarClientes::habilitarEditarEliminar(bool habilitar)
{
    this->ui->actionEditar->setEnabled(habilitar);
    this->ui->actionEliminar->setEnabled(habilitar);
}

void GestionarClientes::actualizarTablaClientes()
{
    this->tablaClientes->actualizarClientes(Cliente::obtenerTodos());
    this->habilitarEditarEliminar(false);
}

void GestionarClientes::on_clientesTableWidget_clicked()
{
    this->habilitarEditarEliminar(true);
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
    int fila = this->ui->clientesTableWidget->currentIndex().row();
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
