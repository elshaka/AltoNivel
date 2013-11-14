#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QTimer>
#include "cliente.h"
#include "factura.h"
#include "tablaclientes.h"
#include "db.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void borrarCampos();
    ~MainWindow();

private slots:


    void on_actionGestionarClientes_triggered();

    void on_actionVer_facturas_en_sistema_triggered();

    void on_tipoComboBox_currentIndexChanged(int index);

    void on_seleccionarClientePushButton_clicked();

    void timer_timeout();

    void on_crearFacturaPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Cliente *cliente;
    Factura *factura;
    FacturaCredito facturaCredito;
};

#endif // MAINWINDOW_H
