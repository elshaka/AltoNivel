#ifndef CLIENTEFORM_H
#define CLIENTEFORM_H

#include <QDialog>
#include "cliente.h"
#include "db.h"

namespace Ui {
class ClienteForm;
}

class ClienteForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit ClienteForm(QWidget *parent = 0, Cliente cliente = Cliente(), QString titulo = "Nuevo cliente");
    Cliente getCliente();
    ~ClienteForm();

private slots:

    void on_pushButtonAceptar_clicked();

private:
    Ui::ClienteForm *ui;
    Cliente cliente;
};

#endif // CLIENTEFORM_H
