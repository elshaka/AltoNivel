#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include <QList>

class Cliente
{
    unsigned int id;
    QString nombre;
    QString apellido;
    QString cedula;
    QString direccion;
    QString telefono;

public:
    Cliente();
    Cliente(QString nombre, QString apellido, QString cedula, QString telefono, QString direccion, unsigned int id = 0);
    QString getNombre();
    QString getApellido();
    QString getCedula();
    QString getDireccion();
    QString getTelefono();
    unsigned int getId();
    void setNombre(QString nombre);
    void setApellido(QString apellido);
    void setCedula(QString cedula);
    void setDireccion(QString direccion);
    void setTelefono(QString telefono);
    bool valido();
    QList<QString> errores;
    ~Cliente();
};

#endif // CLIENTE_H
