QT += core widgets

TARGET = BancoGUI
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main_gui.cpp \
    mainwindow.cpp \
    cajerosdialog.cpp \
    clientesdialog.cpp \
    Cajero.cpp \
    Clientes.cpp

HEADERS += \
    mainwindow.h \
    cajerosdialog.h \
    clientesdialog.h \
    Cajero.h \
    Clientes.h \
    Librerias.h