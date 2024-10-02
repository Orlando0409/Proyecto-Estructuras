#include "Clientes.h"
#include "Cajero.h"
#include <iomanip>
#include <cstdlib> 
#include <ctime>   


Cliente::Cliente(){}

extern nodoCajero* listaCajero;
nodoCliente* listaCliente = NULL;
nodoCliente* aux1 = listaCliente;
nodoCliente* aux2;


int ticket = 1;

void Cliente::ingresarCliente() {
	int edad;
	cout << "Digite la edad del cliente: ";
	cin >> edad;

	nodoCliente* nuevoCliente = new nodoCliente();

	nuevoCliente->setEdad(edad);
	nuevoCliente->setFicha(ticket++);

	nodoCajero* actual = listaCajero;

	if (listaCajero == NULL) {
		cout << "No hay cajeros disponibles" << endl;
		return;
	}
	if (actual->inicio == NULL) {
		actual->inicio = nuevoCliente;
		cout << "Primer cliente agregado al primer cajero correctamente. " << endl;
		return;
	}
	else {
		while (actual != NULL) {
			if (actual->inicio == NULL) {
				actual->inicio = nuevoCliente;
				cout << "Cliente agregado a un cajero vacío con éxito. " << endl;
				return;
			}
			actual = actual->siguiente;
		}
	}
	actual = listaCajero;
	if (nuevoCliente->tipo == "A") {
		while (actual != NULL) {
			if (actual->inicio->tipo == "C") {
				nodoCliente* clienteActual = actual->inicio;
				nuevoCliente->siguiente = actual->inicio;
				actual->inicio = nuevoCliente;
				return;
			}
			actual = actual->siguiente;
		}
	}
	actual = listaCajero;
	if (nuevoCliente->tipo == "A") {
		while (actual != NULL) {
			if (actual->inicio->tipo == "A") {
				nodoCliente* clienteActual = actual->inicio;
				while (clienteActual != NULL && clienteActual->tipo != "C") {
					aux1 = clienteActual;
					aux2 = clienteActual->siguiente;
					clienteActual = clienteActual->siguiente;
				}
				aux1->siguiente = nuevoCliente;
				nuevoCliente->siguiente = aux2;
				cout << "Cliente de tipo A agregado con éxito. " << endl;
				return;
			}
		}
	}
	actual = listaCajero;
	if (nuevoCliente->tipo == "C") {
		int contador = 0;
		nodoCajero* cajeroActual = listaCajero;

		while (cajeroActual != NULL) {
			contador++;
			cajeroActual = cajeroActual->siguiente;
		}

		if (contador == 0) {
			cout << "No hay cajeros disponibles. Por favor, ingrese un cajero e inténtelo de nuevo. " << endl;
		}

		srand(time(0)); 
		int cajeroAleatorio = rand() % contador; 

		cajeroActual = listaCajero;
		int indice = 0;
		while (cajeroActual != NULL) {
			if (indice == cajeroAleatorio) {
				nodoCliente* clienteActual = cajeroActual->inicio;
				while (clienteActual != NULL) {
					aux1 = clienteActual;
					aux2 = clienteActual->siguiente;
					clienteActual = clienteActual->siguiente;
				}
				aux1->siguiente = nuevoCliente;
				nuevoCliente->siguiente = aux2;
				cout << "Cliente de tipo C agregado con éxito. " << endl;
				return;
			}
			cajeroActual = cajeroActual->siguiente;
			indice++;
		}
	}
}

static void mostrarCajeros() {
	nodoCajero* actual = listaCajero;

	if (actual == NULL) {
		cout << "No hay cajeros ingresados." << endl;
	}
	else {
		cout << left << setw(10) << "ID Cajero"
			<< " | " << setw(12) << "Numero Caja"
			<< " | " << setw(20) << "Nombre Cajero" << endl;
		cout << "--------------------------------------------" << endl;

		while (actual != NULL) {
			
			cout << left << setw(10) << actual->getId()
				<< " | " << setw(12) << actual->getNumeroCaja()
				<< " | " << setw(20) << actual->getNombreCajero() << endl;

		
			nodoCliente* clienteActual = actual->inicio;
			if (clienteActual == NULL) {
				cout << "   No hay clientes asignados a este cajero." << endl;
			}
			else {
				cout << "   Clientes asignados:" << endl;
				cout << "   " << left << setw(12) << "Ficha Cliente"
					<< " | " << setw(12) << "Tipo Cliente" << endl;
				cout << "   --------------------------------------------" << endl;

				while (clienteActual != NULL) {
					cout << "   " << left << setw(12) << clienteActual->getFicha()
						<< " | " << setw(12) << clienteActual->getTipo() << endl;

					clienteActual = clienteActual->siguiente;
				}
			}

			actual = actual->siguiente;
		}
	}

}

void Cliente::atenderClientes() {
	nodoCajero* actual = listaCajero;

	while (actual != NULL) {
		if(actual->inicio != NULL){
			actual->inicio = actual->inicio->siguiente;
		}
		actual = actual->siguiente;
	}
	cout << "Los clientes al inicio de la cola han sido atendidos. " << endl;
}

void Cliente::eliminarCliente() {
	int ticket = 0;
	nodoCajero* actual = listaCajero;
	
	cout << "Digite el ticket del cliente que desea eliminar: ";
	cin >> ticket;

	if (actual == NULL) {
		cout << "No hay cajeros disponibles. " << endl;
	}
	while (actual != NULL) {
		nodoCliente* clienteActual = actual->inicio;
		nodoCliente* aux = NULL;
		if (clienteActual == NULL) {
			cout << "El ticket no existe en el sistema. " << endl;
		}
		while (clienteActual != NULL && clienteActual->getFicha() != ticket) {
			aux = clienteActual;
			clienteActual = clienteActual->siguiente;
		}
		if (clienteActual != NULL && aux != NULL && clienteActual->getFicha() == ticket) {
			aux->siguiente = clienteActual->siguiente;
			delete clienteActual;
			cout << "Cliente eliminado. " << endl;
			return;
		}
		if (aux == NULL && clienteActual != NULL) {
			actual->inicio = clienteActual->siguiente;
			delete clienteActual;
			cout << "Cliente eliminado. " << endl;
			return;
		}
		actual = actual->siguiente;
	}
	if (actual == NULL) {
		cout << "El ticket no existe en el sistema. " << endl;
	}
}

void Cliente::menuClientes() {

	int opcion;
	
	do {
		system("cls");
		cout << "\tMÓDULO de CLIENTES" << endl;
		cout << "--------------------------------------\n";
		cout << "1. Ingresar un cliente." << endl;
		cout << "2. Mostrar cola actual." << endl;
		cout << "3. Atender clientes." << endl;
		cout << "4. Eliminar un cliente." << endl;
		cout << "5. Salir. ";
		cout <<endl<< "Ingrese una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:{
			system("cls");
			cout << "\tIngresar un cliente nuevo.\n";
			cout << "------------------------------------\n\n";
			ingresarCliente();
			system("pause");
			break;
		}
		case 2:{
			system("cls");
			cout << "\tMostrar Cola de Cajeros.\n";
			cout << "------------------------------------\n\n";
			mostrarCajeros();
			system("pause");
			break;
		}
		case 3:{
			system("cls");
			cout << "\tAtender Clientes.\n";
			cout << "------------------------------------\n\n";
			atenderClientes();
			system("pause");
			break;
		}
		case 4:{
			system("cls");
			cout << "\tEliminar Cliente.\n";
			cout << "------------------------------------\n\n";
			eliminarCliente();
			system("pause");
			break;
		}
			
		case 5:
			cout << "¡Gracias por usar el Módulo de Clientes!" << endl;
			system("pause");
			break;
		}

	} while (opcion != 5);
};
