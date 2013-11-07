# -------------------------------------------------
# Project created by QtCreator 2013-10-31T11:46:04
# -------------------------------------------------
QT += core \
    gui \
    sql
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
TARGET = AltoNivel
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    cliente.cpp \
    clienteform.cpp \
    db.cpp \
    factura.cpp
HEADERS += mainwindow.h \
    cliente.h \
    clienteform.h \
    db.h \
    factura.h
FORMS += mainwindow.ui \
    clienteform.ui
