#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionarclientes.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
