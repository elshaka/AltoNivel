#ifndef FACTURA_H
#define FACTURA_H
#include "cliente.h"
#include "db.h"
#include <QDateTime>

class Factura
{
    int id;
    QString tipo;
    Cliente* cliente;
    int numero;
    QDateTime fechaEmision;
    float monto;
    QString estado;

    static DB* db;

protected:
    void setTipo(QString tipo);

public:
    Factura();
    Factura(Cliente* cliente, QDateTime fechaEmision, float monto, QString estado, int numero = 0, int id = 0);
    void setCliente(Cliente* cliente);
    void setFechaEmision(QDateTime fechaEmision);
    virtual void setFechaVencimiento(QDateTime /*fechaVencimiento*/);
    void setMonto(float monto);
    void setEstado(QString estado);
    virtual void setSaldoPendiente(float /*saldoPendiente*/);
    QString getTipo();
    int getId();
    Cliente* getCliente();
    int getNumero();
    QDateTime getFechaEmision();
    virtual QDateTime getFechaVencimiento();
    float getMonto();
    QString getEstado();
    virtual float getSaldoPendiente();
    virtual bool cancelar();
    void anular();
    virtual bool abonar(float /*abono*/);
    virtual bool valida();
    virtual ~Factura();
    QList<QString> errores;

    static QList<Factura *> obtenerTodas();
    bool guardar();
    bool eliminar();

    static QString PORCANCELAR;
    static QString CANCELADA;
    static QString ANULADA;
    static QList<QString> ESTADOS;
    static QString CONTADO;
    static QString CREDITO;
    static QList<QString> TIPOS;
    static QString FORMATOFECHA;
};

class FacturaCredito : public Factura
{
    QDateTime fechaVencimiento;
    float saldoPendiente;
public:
    FacturaCredito();
    FacturaCredito(Cliente* cliente, QDateTime fechaEmision, QDateTime fechaVencimiento, float monto, float saldoPendiente, QString estado, int numero = 0, int id = 0);
    void setFechaVencimiento(QDateTime fechaVencimiento);
    void setSaldoPendiente(float saldoPendiente);
    QDateTime getFechaVencimiento();
    float getSaldoPendiente();
    bool abonar(float abono);
    bool cancelar();
    bool valida();
};

#endif // FACTURA_H
