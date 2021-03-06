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
    this->cliente = NULL;
    this->timer_timeout();
    this->ui->tipoComboBox->addItem("Contado", QVariant(Factura::CONTADO));
    this->ui->tipoComboBox->addItem("Credito", QVariant(Factura::CREDITO));
    this->ui->venceDateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime().addDays(1));
    this->ui->venceDateTimeEdit->setDateTime(QDateTime::currentDateTime().addDays(1));
    this->timer = new QTimer(this);
    this->connect(this->timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    this->timer->start(1000);
    this->ui->abonoLabel->setVisible(false);
    this->ui->abonoLineEdit->setVisible(false);
    this->ui->venceLabel->setVisible(false);
    this->ui->venceDateTimeEdit->setVisible(false);
}

void MainWindow::borrarCampos()
{
    this->ui->venceDateTimeEdit->setDate(QDate::currentDate().addDays(1));
    this->ui->clienteLineEdit->clear();
    this->ui->montoLineEdit->clear();
    this->ui->abonoLineEdit->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->cliente;
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

void MainWindow::on_tipoComboBox_currentIndexChanged(int index)
{
    bool visible = this->ui->tipoComboBox->itemData(index).toString() == Factura::CREDITO;
    this->ui->abonoLabel->setVisible(visible);
    this->ui->abonoLineEdit->setVisible(visible);
    this->ui->venceLabel->setVisible(visible);
    this->ui->venceDateTimeEdit->setVisible(visible);
}

void MainWindow::on_seleccionarClientePushButton_clicked()
{
    SeleccionarCliente seleccionarCliente(this);
    if (seleccionarCliente.exec() == QDialog::Accepted)
    {
        this->cliente = seleccionarCliente.getCliente();
        this->ui->clienteLineEdit->setText(this->cliente->getNombre() + " " + this->cliente->getApellido());
    }
}

void MainWindow::timer_timeout()
{
    this->ui->statusBar->showMessage(QDateTime::currentDateTime().toString(Factura::FORMATOFECHA));
}

void MainWindow::on_crearFacturaPushButton_clicked()
{
    int tipoIndex = this->ui->tipoComboBox->currentIndex();
    QString tipo = this->ui->tipoComboBox->itemData(tipoIndex).toString();
    QDateTime fechaActual = QDateTime::currentDateTime();
    if(tipo == Factura::CONTADO)
    {
        this->factura = new Factura(this->cliente,
                                    fechaActual,
                                    this->ui->montoLineEdit->text().toFloat(),
                                    Factura::PORCANCELAR);
    }
    else if (tipo == Factura::CREDITO)
    {
        float monto = this->ui->montoLineEdit->text().toFloat();
        float saldoPendiente = monto - this->ui->abonoLineEdit->text().toFloat();
        this->factura = new FacturaCredito(this->cliente,
                                           fechaActual,
                                           this->ui->venceDateTimeEdit->dateTime(),
                                           monto,
                                           saldoPendiente,
                                           Factura::PORCANCELAR);
    }
    if(this->factura->guardar())
    {
        QMessageBox::information(this, "Factura creada", "La factura fue creada exitosamente en el sistema");
        this->borrarCampos();
    }
    else
    {
        QString mensaje = "";
        QList<QString>::Iterator i;
        QList<QString> errores = this->factura->errores;
        for(i = errores.begin(); i != errores.end(); ++i)
            mensaje.append(QString("- %1\n").arg(*i));
        QMessageBox::warning(this, "Atributos invalidos", mensaje);
    }
    this->factura->setCliente(NULL);
    delete this->factura;
}
