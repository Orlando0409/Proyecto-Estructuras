#include "Clientes.h"
#include "Cajero.h"
#include "Librerias.h"
 


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
		cout << "Primer cliente agregado correctamente al primer cajero" << endl;
		return;
	}
	else {
		while (actual != NULL) {
			if (actual->inicio == NULL) {
				actual->inicio = nuevoCliente;
				cout << "Cliente agregado con éxito a un cajero vacío" << endl;
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
				cout << "Cliente A agregado con exito" << endl;
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
			cout << "No hay cajeros disponibles" << endl;
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
				cout << "Cliente tipo C agregado con exito" << endl;
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

		while (actual != NULL) {
			cout << "\n\n\n" << "|-------------------------------------------|" << endl;
			cout << left << "|ID Cajero"
				<< " | " << setw(12) << "Numero Caja"
				<< " | " << setw(16) << "Nombre Cajero"<<"|" << endl;
			cout << "|-------------------------------------------|" << endl;

			cout << left <<"|"<< actual->getId()
				<< " | " << setw(12) << actual->getNumeroCaja()
				<< " | " << setw(16) << actual->getNombreCajero() <<"|" << endl;
			cout << "|-------------------------------------------|" << endl;
		
			nodoCliente* clienteActual = actual->inicio;
			if (clienteActual == NULL) {
				cout << "No hay clientes asignados a este cajero." << endl;
			}
			else {
				cout << "\n|"<< setw(42)<<"Clientes asignados : " <<" | " << endl;
				cout << "|-------------------------------------------|" << endl;
				cout << "|" << left << setw(20) << "Ficha Cliente"
					<< " | " << setw(20) << "Tipo Cliente" <<"|" << endl;
				cout << "|-------------------------------------------|" << endl;

				while (clienteActual != NULL) {
					cout << "|" << left << setw(20) << clienteActual->getFicha()
						<< " | " << setw(20) << clienteActual->getTipo() << "|" << endl;
					cout << "|-------------------------------------------|" << endl;

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
	cout << "Primeros clientes atendidos" << endl;
};
void Cliente::eliminarCliente() {
	int ticket = 0;
	nodoCajero* actual = listaCajero;
	

	cout << "Digite el ticket del cliente que desea eliminar" << endl;
	cin >> ticket;

	if (actual == NULL) {
		cout << "No hay cajeros disponibles" << endl;
	}
	while (actual != NULL) {
		nodoCliente* clienteActual = actual->inicio;
		nodoCliente* aux = NULL;
		if (clienteActual == NULL) {
			cout << "El tickete no existe" << endl;
		}
		while (clienteActual != NULL && clienteActual->getFicha() != ticket) {
			aux = clienteActual;
			clienteActual = clienteActual->siguiente;
		}
		if (clienteActual != NULL && aux != NULL && clienteActual->getFicha() == ticket) {
			aux->siguiente = clienteActual->siguiente;
			delete clienteActual;
			cout << "Cliente eliminado" << endl;
			return;
		}
		if (aux == NULL && clienteActual != NULL) {
			actual->inicio = clienteActual->siguiente;
			delete clienteActual;
			cout << "Cliente eliminado" << endl;
			return;
		}
		actual = actual->siguiente;
	}
	if (actual == NULL) {
		cout << "El tickete no existe" << endl;
	}
};
void Cliente::menuClientes() {


	setlocale(LC_CTYPE, "Spanish");

	int opcion;
	
	do {
		system("cls");

		cout << "1. Para agregar un cliente" << endl;
		cout << "2. Para mostrar cajeros" << endl;
		cout << "3. Para atender a los cliente" << endl;
		cout << "4. Para eliminar un cliente" << endl;
		cout << "5. Para salir";
		cout <<endl<< "Digite una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			system("cls");
			ingresarCliente();
			system("pause");
			break;
		case 2:
			system("cls");
			mostrarCajeros();
			cout << "\n\n"; 
			system("pause");
			break;
		case 3:
			system("cls");
			atenderClientes();
			system("pause");
			break;
		case 4:
			system("cls");
			eliminarCliente();
			system("pause");
			break;
		case 5:
			system("cls");
			cout << "bye" << endl;
			system("pause");
			break;
		default:
			cout << "Opcion invalida" << endl;
			system("pause");
			break;
		}

	} while (opcion != 5);
};
