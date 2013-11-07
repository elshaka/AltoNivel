#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
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
    ~MainWindow();
    
private slots:


    void on_actionGestionarClientes_triggered();

private:
    Ui::MainWindow *ui;
    DB db;
};

#endif // MAINWINDOW_H
