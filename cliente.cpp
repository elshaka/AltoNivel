#include "cliente.h"

Cliente::Cliente()
{
    this->nombre = "";
    this->apellido = "";
    this->cedula = "";
    this->id = 0;
}

Cliente::Cliente(QString nombre, QString apellido, QString cedula, unsigned int id)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->cedula = cedula;
    this->id = id;
}

void Cliente::setNombre(QString nombre)
{
    this->nombre = nombre;
}

void Cliente::setApellido(QString apellido)
{
    this->apellido = apellido;
}

void Cliente::setCedula(QString cedula)
{
    this->cedula = cedula;
}

QString Cliente::getNombre()
{
    return this->nombre;
}

QString Cliente::getApellido()
{
    return this->apellido;
}

QString Cliente::getCedula()
{
    return this->cedula;
}

unsigned int Cliente::getId()
{
    return this->id;
}

bool Cliente::operator ==(Cliente cliente)
{
    return this->id == cliente.getId();
}

Cliente::~Cliente() {}
