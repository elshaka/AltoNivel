#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "cliente.h"
#include "db.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void actualizarListaClientes();
    void habilitarEditarEliminar();
    void deshabilitarEditarEliminar();
    ~MainWindow();
    
private slots:
    void on_listWidget_clicked();

    void on_actionNuevo_triggered();

    void on_actionEditar_triggered();

    void on_actionEliminar_triggered();

private:
    Ui::MainWindow *ui;
    QList<Cliente> clientes;
    DB db;
};

#endif // MAINWINDOW_H
