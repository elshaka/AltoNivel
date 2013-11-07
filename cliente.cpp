#include "cliente.h"

Cliente::Cliente()
{
    this->nombre = "";
    this->apellido = "";
    this->cedula = "";
    this->id = 0;
}

Cliente::Cliente(QString nombre, QString apellido, QString cedula, QString telefono, QString direccion, unsigned int id)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->cedula = cedula;
    this->direccion = direccion;
    this->telefono = telefono;
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

void Cliente::setDireccion(QString direccion)
{
    this->direccion = direccion;
}

void Cliente::setTelefono(QString telefono)
{
    this->telefono = telefono;
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

QString Cliente::getDireccion()
{
    return this->direccion;
}

QString Cliente::getTelefono()
{
    return this->telefono;
}

unsigned int Cliente::getId()
{
    return this->id;
}

bool Cliente::valido()
{
    this->errores.clear();
    // Agregar validaciones
    return this->errores.size() == 0;
}

Cliente::~Cliente() {}
