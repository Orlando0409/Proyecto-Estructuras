#pragma once
#include "Librerias.h"

typedef class Cliente {
private:
    int ficha;
    string fecha;
    string hora;
    int edad;
    string tipo;
public:
    Cliente();

    int getFicha() const { return ficha; }
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }
    int getEdad() const { return edad; }
    string getTipo() const { return tipo; }

    void setFicha(int _ficha) {
        ficha = _ficha;
    }
    void setFecha(string _fecha) {
        fecha = _fecha;
    }
    void setHora(string _hora) {
        hora = _hora;
    }
    void setEdad(int _edad) {
        edad = _edad;
        setTipo();
    }
    void setTipo() {
        if (edad >= 65) {
            tipo = "A";
        }
        else {
            tipo = "C";
        }
    }

    class Cliente* siguiente = NULL;

    void ingresarCliente();
    void atenderClientes();
    void eliminarCliente();
    void menuClientes();
} nodoCliente;
