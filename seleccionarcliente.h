#ifndef SELECCIONARCLIENTE_H
#define SELECCIONARCLIENTE_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "cliente.h"
#include "tablaclientes.h"

namespace Ui {
class SeleccionarCliente;
}

class SeleccionarCliente : public QDialog
{
    Q_OBJECT

public:
    explicit SeleccionarCliente(QWidget *parent = 0);
    Cliente* getCliente();
    ~SeleccionarCliente();

private slots:
    void on_aceptarPushButton_clicked();

    void on_cancelarPushButton_clicked();

    void on_nuevoRadioButton_toggled(bool checked);

private:
    Ui::SeleccionarCliente *ui;
    Cliente* cliente;
    TablaClientes* tablaClientes;
    QSortFilterProxyModel* tablaFiltradaClientes;
};

#endif // SELECCIONARCLIENTE_H
