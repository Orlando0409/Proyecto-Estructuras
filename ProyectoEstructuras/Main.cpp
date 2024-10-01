
#include "Cajero.h"
#include "Clientes.h"
int main() {
	nodoCajero n;
	nodoCliente m;
	
	int opc;
	do
	{
		system("cls");
		cout << "\t\tBienvenido a \n";
		cout << "\tBanco Quiebra Segura R.L. \n";
		cout << "--------------------------------------------\n";
		cout << "       1. Modulo de Cajeros\n";
		cout << "       2. Modulo de Clientes\n";
		cout << "       3. Salir\n\n";
		cout << "Ingrese una opcion: ";
		cin >> opc;
		switch (opc)
		{
			case 1:
			{
				n.menuCajero();
				break;
			}
			case 2:
			{
				m.menuClientes();
				break;
			}
			case 3:
			{
				cout << "Aio\n";
				system("pause");
				break;
			}
			default:
			{
				cout << "Opcion invalida\n";
				system("pause");
				break;
			}


		}

	} while (opc !=3);
	
	return 0;
}