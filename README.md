# Banco Quiebra Segura R.L. - Sistema de Gestión

Proyecto, Estructuras de Datos - Universidad Nacional de Costa Rica, 2024.

## 🆕 NUEVO: Sistema con Interfaz Gráfica

Este proyecto ahora incluye una **interfaz gráfica moderna** desarrollada con Qt5. 

### Versiones Disponibles:
- **GUI (Recomendada)**: `./BancoGUI` - Interfaz gráfica moderna y fácil de usar
- **Consola**: `./main` - Versión original de línea de comandos

### Características del Sistema GUI:
- ✅ Interfaz moderna con Qt5
- ✅ Gestión visual de cajeros y clientes
- ✅ Sistema de colas con prioridades visuales
- ✅ Validación en tiempo real
- ✅ Navegación intuitiva con menús y atajos

## Compilación Rápida

### GUI (Qt5)
```bash
cd ProyectoEstructuras
qmake BancoGUI.pro
make
./BancoGUI
```

### Consola
```bash
cd ProyectoEstructuras
g++ -o main Main.cpp Cajero.cpp Clientes.cpp
./main
```

## Documentación Completa

Para información detallada sobre la interfaz gráfica, consulte [README_GUI.md](README_GUI.md).

## Funcionalidades

- **Gestión de Cajeros**: CRUD completo con validaciones
- **Gestión de Clientes**: Sistema de colas con prioridades para adultos mayores
- **Interfaz Dual**: Consola tradicional y GUI moderna
- **Estructuras de Datos**: Implementación con listas enlazadas