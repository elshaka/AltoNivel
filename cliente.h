#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>

class Cliente
{
    unsigned int id;
    QString nombre;
    QString apellido;
    QString cedula;

public:
        Cliente();
        Cliente(QString nombre, QString apellido, QString cedula, unsigned int id = 0);
        QString getNombre();
        QString getApellido();
        QString getCedula();
        unsigned int getId();
        void setNombre(QString nombre);
        void setApellido(QString apellido);
        void setCedula(QString cedula);
        bool operator==(Cliente cliente);
        ~Cliente();
};

#endif // CLIENTE_H
