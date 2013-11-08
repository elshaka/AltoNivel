#ifndef FACTURA_H
#define FACTURA_H
#include "cliente.h"

class Factura
{
    int id;
    QString tipo;
    int cliente_id;
    Cliente cliente;
    int numero;
    QString fechaEmision;
    float monto;
    QString estado;

public:
    Factura();
    Factura(int cliente_id, QString fechaEmision, float monto, QString estado, int numero = 0, int id = 0);
    void setClienteId(int cliente_id);
    void setCliente(Cliente cliente);
    void setNumero(int numero);
    void setFechaEmision(QString fechaEmision);
    void setMonto(float monto);
    void setEstado(QString estado);
    int getClienteId();
    Cliente getCliente();
    int getNumero();
    QString getFechaEmision();
    virtual QString getFechaVencimiento();
    float getMonto();
    virtual float getSaldoPendiente();
    void cancelar();
    void anular();
    virtual bool valida();
};

class FacturaCredito : public Factura
{
    QString fechaVencimiento;
    float saldoPendiente;
public:
    FacturaCredito();
    FacturaCredito(int cliente_id, QString fechaEmision, QString fechaVencimiento, float monto, float saldoPendiente, QString estado, int numero = 0, int id = 0);
    void setFechaVencimiento(QString fechaVencimiento);
    void setSaldoPendiente(float saldoPendiente);
    void abonar();
    bool valida();
};

#endif // FACTURA_H
