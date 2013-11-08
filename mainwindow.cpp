#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionarclientes.h"
#include "seleccionarcliente.h"
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->tipoComboBox->addItem(QString("Sencilla"));
    this->ui->tipoComboBox->addItem(QString("Credito"));
    this->on_timer_timeout();
    this->timer = new QTimer(this);
    this->connect(this->timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    this->timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGestionarClientes_triggered()
{
    GestionarClientes* gestionarClientes = new GestionarClientes(&this->db, this);
    gestionarClientes->show();
}

void MainWindow::on_tipoComboBox_currentIndexChanged(const QString &arg1)
{
    bool visible = arg1 == "Credito";
    this->ui->abonoLabel->setVisible(visible);
    this->ui->abonoLineEdit->setVisible(visible);
    this->ui->venceLabel->setVisible(visible);
    this->ui->venceDateEdit->setVisible(visible);
}

void MainWindow::on_seleccionarClientePushButton_clicked()
{
    SeleccionarCliente seleccionarCliente;
    seleccionarCliente.exec();
}

void MainWindow::on_timer_timeout()
{
    this->ui->statusBar->showMessage(QTime::currentTime().toString());
}
