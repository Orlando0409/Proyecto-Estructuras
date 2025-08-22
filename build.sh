#!/bin/bash

echo "==================================="
echo "Banco Quiebra Segura R.L. - Builder"
echo "==================================="
echo ""

cd ProyectoEstructuras

echo "1. Compilando versión de consola..."
g++ -o main Main.cpp Cajero.cpp Clientes.cpp
if [ $? -eq 0 ]; then
    echo "✅ Consola compilada exitosamente -> ./main"
else
    echo "❌ Error compilando versión de consola"
    exit 1
fi

echo ""
echo "2. Compilando versión GUI (Qt5)..."

if command -v qmake &> /dev/null; then
    qmake BancoGUI.pro
    make
    if [ $? -eq 0 ]; then
        echo "✅ GUI compilada exitosamente -> ./BancoGUI"
        echo ""
        echo "🚀 Para ejecutar:"
        echo "   Consola: cd ProyectoEstructuras && ./main"
        echo "   GUI:     cd ProyectoEstructuras && ./BancoGUI"
    else
        echo "❌ Error compilando versión GUI"
        exit 1
    fi
else
    echo "⚠️  Qt5 no encontrado. Solo versión de consola disponible."
    echo "   Para instalar Qt5: sudo apt install qtbase5-dev qt5-qmake"
fi

echo ""
echo "🎉 Compilación completada!"