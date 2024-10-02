#pragma once
#include "Cajero.h"
#include <iomanip>

Cajero::Cajero(){}

Cajero::~Cajero(){}
nodoCajero* listaCajero = NULL;

bool validarCaja(int numCajero) {
    nodoCajero* actual = listaCajero;
    while (actual != NULL) {
        if (actual->getNumeroCaja() == numCajero) {
            return false;
        }
        actual = actual->siguiente;
    }
    return true;
}

bool validarID(int id) //busca id y verifica 
{
    nodoCajero* actual = listaCajero;
    while (actual != NULL) {
        if (actual->getId() == id) {
            return false;
        }
        actual = actual->siguiente;
    }
    return true;
}

bool validarCajasDisponibles() {
    int cajasOcupadas = 0;
    nodoCajero* actual = listaCajero;
    while (actual != NULL) {
        cajasOcupadas++;
        actual = actual->siguiente;
    }
    return cajasOcupadas <= 6;
}

void Cajero::ingresarCajero() {
	int id; 
	int numCajero;
    string nombre;

    cout << "Ingrese ID del cajero: ";
    cin >> id;
    cout << "Ingrese numero de caja: ";
    cin >> numCajero;
    cout << "Ingrese nombre del cajero: ";
    cin.ignore();
    getline(cin, nombre);

    if (!validarID(id)) {
        cout << "El ID del cajero ya se encuentra en uso." << endl;
        return;
    }

    if (!validarCaja(numCajero)) {
        cout << "El numero de caja ya se encuentra en uso." << endl;
        return;
    }

    if (!validarCajasDisponibles()) {
        cout << "No hay cajas disponibles." << endl;
        return;
    }

    nodoCajero* nuevoCajero = new nodoCajero();
    nuevoCajero->setId(id);
    nuevoCajero->setNumeroCaja(numCajero);
    nuevoCajero->setNombreCajero(nombre);
    nuevoCajero->siguiente = listaCajero;
    listaCajero = nuevoCajero;
    cout << "Cajero ingresado correctamente." << endl;
}

void Cajero::mostrarCajeros() {
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
			actual = actual->siguiente;
		}
	}
}

void Cajero::modificarCajero()
{
	int id;
	cout << "Ingrese ID del cajero que desea modificar: ";
	cin >> id;

	if (validarID(id) == NULL) //igual a null porque si lo encuentra en la funcion va a mandar un false
	{
		nodoCajero* actual = listaCajero;
		while (actual != NULL) {
			if (actual->getId() == id) {

				int numCajero;
				string nombre;
				cout << "Ingrese nuevo numero de caja: ";
				cin >> numCajero;
				cout << "Ingrese nuevo nombre del cajero: ";
				cin.ignore();
				getline(cin, nombre);

				if (!validarCaja(numCajero)) {
					cout << "El numero de caja ya se encuentra en uso." << endl;
					return;
				}

				actual->setNumeroCaja(numCajero);
				actual->setNombreCajero(nombre);
				cout << "Cajero modificado correctamente." << endl;
			}
			actual = actual->siguiente;
		}

	}
	else {
		cout << "Cajero no encontrado." << endl;
		return;
	}
}

void Cajero::eliminarCajero() {
	int id;
	cout << "Ingrese ID del cajero que desea eliminar: ";
	cin >> id;
	nodoCajero* anterior = NULL;
	nodoCajero* actual = listaCajero;
	while (actual != NULL) {
		if (actual->getId() == id) {
			if (anterior == NULL) {
				listaCajero = actual->siguiente;
			}
			else {
				anterior->siguiente = actual->siguiente;
			}
			delete actual;
			cout << "Cajero eliminado correctamente." << endl;
			return;
		}
		anterior = actual;
		actual = actual->siguiente;
	}
	cout << "Cajero no encontrado." << endl;
}

void Cajero::menuCajero()
{
	setlocale(LC_CTYPE, "Spanish");

	int opt;
	do
	{
		system("cls");
		cout << "\tMODULO de CAJEROS" << endl;
		cout << "--------------------------------------\n";
		cout << "1. Ingresar cajero." << endl;
		cout << "2. Mostrar lista de cajeros. " << endl;
		cout << "3. Modificar cajero." << endl;
		cout << "4. Eliminar cajero." << endl;
		cout << "5. Salir. \n" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opt;
		switch (opt) {
		case 1:
			system("cls");
			cout << "\tIngresar un cajero nuevo.\n";
			cout << "------------------------------------\n\n";
			ingresarCajero();
			system("pause");
			break;
		case 2:
			system("cls");
			cout << "\tLista de cajeros activos.\n";
			cout << "------------------------------------\n\n";
			mostrarCajeros();
			system("pause");
			break;
		case 3:
			system("cls");
			cout << "\tEditar un cajero.\n";
			cout << "------------------------------------\n\n";
			modificarCajero();
			system("pause");
			break;
		case 4:
			system("cls");
			cout << "\tDespedir a un cajero. \n";
			cout << "------------------------------------\n\n";
			eliminarCajero();
			system("pause");
			break;
		case 5:
			cout << "Gracias por usar nuestro modulo de cajeros!" << endl;
			system("pause");
			break;
		default:
			cout << "Opcion invalida" << endl;
			system("pause");
		}

	} while (opt != 5);
}
