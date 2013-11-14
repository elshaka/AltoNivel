#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include <QList>
#include "db.h"

class Cliente
{
    int id;
    QString nombre;
    QString apellido;
    QString cedula;
    QString direccion;
    QString telefono;

    static DB* db;

public:
    Cliente();
    Cliente(QString nombre, QString apellido, QString cedula, QString telefono, QString direccion, int id = 0);
    QString getNombre();
    QString getApellido();
    QString getCedula();
    QString getDireccion();
    QString getTelefono();
    int getId();
    void setNombre(QString nombre);
    void setApellido(QString apellido);
    void setCedula(QString cedula);
    void setDireccion(QString direccion);
    void setTelefono(QString telefono);
    bool valido();
    QList<QString> errores;

    bool guardar();
    bool eliminar();
    static QList<Cliente> obtenerTodos();

    ~Cliente();
};

#endif // CLIENTE_H
