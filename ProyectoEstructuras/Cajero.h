#pragma once
#include "Librerias.h"

typedef class Cajero {
	private:
		int id;
		int numeroCaja;
		string nombreCajero;
	public:

		Cajero();
		~Cajero(); // destructor

		//metodos get/set de los atributos
		int cantidadCliente = 0;
		int getId() const { return id; }
		int getNumeroCaja() const { return numeroCaja; }
		string getNombreCajero() const { return nombreCajero; }

		void setId(int _id) { 
			this->id = _id; 
		}
		
		void setNumeroCaja(int _numeroCaja) { 
			this->numeroCaja = _numeroCaja; 
		}
		
		void setNombreCajero(string _nombreCajero) { 
			this->nombreCajero = _nombreCajero; 
		}

		class Cajero* siguiente;
		class Cajero* atras;
		class Cliente* inicio = NULL;

		// Métodos para administrar los cajeros
		void ingresarCajero();
		void mostrarCajeros();
		void eliminarCajero();
		void modificarCajero();
		void menuCajero();
	
}nodoCajero;
