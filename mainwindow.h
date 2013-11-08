#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QTimer>
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

    void on_tipoComboBox_currentIndexChanged(const QString &arg1);

    void on_seleccionarClientePushButton_clicked();

    void on_timer_timeout();

private:
    Ui::MainWindow *ui;
    DB db;
    QTimer *timer;
};

#endif // MAINWINDOW_H
