
#include "Cajero.h"
int main() {
	nodoCajero n;

	 int opt;
	do
	{
		system("cls");
		cout << "MODULO_CAJEROS" << endl;
		cout << "1. Ingresar cajero" << endl;
		cout << "2. Mostrar lista de cajeros" << endl;
		cout << "3. modificar cajero" << endl;
		cout << "4. Eliminar cajero" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opt;
		switch (opt) {
		case 1:
			n.ingresarCajero();
			system("pause");
			break;
		case 2:
			n.mostrarCajeros();
			system("pause");
			break;
		case 3:
			n.modificarCajero();
			system("pause");
			break;
		case 4:
			n.eliminarCajero();
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
	return 0;
}