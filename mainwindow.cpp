#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionarclientes.h"
#include "gestionarfacturas.h"
#include "seleccionarcliente.h"
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->timer_timeout();
    this->ui->venceDateEdit->setMinimumDate(QDate::currentDate().addDays(1));
    this->ui->venceDateEdit->setDate(QDate::currentDate().addDays(1));
    this->timer = new QTimer(this);
    this->connect(this->timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    this->timer->start(1000);
    this->ui->abonoLabel->setVisible(false);
    this->ui->abonoLineEdit->setVisible(false);
    this->ui->venceLabel->setVisible(false);
    this->ui->venceDateEdit->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::on_actionGestionarClientes_triggered()
{
    GestionarClientes* gestionarClientes = new GestionarClientes(this);
    gestionarClientes->show();
}

void MainWindow::on_actionVer_facturas_en_sistema_triggered()
{
    GestionarFacturas* gestionarFacturas = new GestionarFacturas(this);
    gestionarFacturas->show();
}

void MainWindow::on_tipoComboBox_currentIndexChanged(const QString &arg1)
{
    bool visible = arg1 == "Crédito";
    this->ui->abonoLabel->setVisible(visible);
    this->ui->abonoLineEdit->setVisible(visible);
    this->ui->venceLabel->setVisible(visible);
    this->ui->venceDateEdit->setVisible(visible);
}

void MainWindow::on_seleccionarClientePushButton_clicked()
{
    SeleccionarCliente seleccionarCliente(this);
    if (seleccionarCliente.exec() == QDialog::Accepted)
    {
        this->cliente = seleccionarCliente.getCliente();
        this->ui->clienteLineEdit->setText(this->cliente.getNombre() + " " + this->cliente.getApellido());
    }
}

void MainWindow::timer_timeout()
{
    this->ui->statusBar->showMessage(QDateTime::currentDateTime().toString("dddd, d 'de' MMMM 'de' yyyy. hh:mm:ss"));
}

void MainWindow::on_crearFacturaPushButton_clicked()
{

}
