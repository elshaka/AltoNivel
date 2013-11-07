#ifndef GESTIONARCLIENTES_H
#define GESTIONARCLIENTES_H

#include <QMainWindow>
#include "db.h"
#include "cliente.h"

namespace Ui {
class GestionarClientes;
class ClientesTableModel;
}

class ClientesTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ClientesTableModel(QList<Cliente> clientes, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Cliente cliente(int fila);
    void actualizarClientes(QList<Cliente> clientes);
private:
    QList<Cliente> clientes;
    static QList<QString> headers;
};

class GestionarClientes : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionarClientes(DB *db, QWidget *parent = 0);
    void actualizarTablaClientes();
    void habilitarEditarEliminar(bool habilitar);
    ~GestionarClientes();

private slots:
    void on_clientesTableWidget_clicked();

    void on_actionNuevo_triggered();

    void on_actionEditar_triggered();

    void on_actionEliminar_triggered();

private:
    Ui::GestionarClientes *ui;
    DB *db;
    ClientesTableModel *tablaClientes;
};

#endif // GESTIONARCLIENTES_H
