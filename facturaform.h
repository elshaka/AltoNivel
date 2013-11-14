#ifndef FACTURAFORM_H
#define FACTURAFORM_H

#include <QDialog>
#include "factura.h"

namespace Ui {
class FacturaForm;
}

class FacturaForm : public QDialog
{
    Q_OBJECT

public:
    explicit FacturaForm(Factura *factura, QWidget *parent = 0);
    Factura *getFactura();
    ~FacturaForm();

private slots:
    void on_pushButtonCancelar_clicked();

    void on_pushButtonDescartar_clicked();

    void on_pushButtonAbonar_clicked();

    void on_pushButtonAceptar_clicked();

private:
    Ui::FacturaForm *ui;
    Factura *factura;
    void actualizarCampos();
};

#endif // FACTURAFORM_H
