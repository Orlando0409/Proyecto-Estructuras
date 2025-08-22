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
            actual = actual->siguiente;
        }
    }
    
    // Para clientes comunes (tipo C)
    actual = listaCajero;
    int menorCola = 999;
    nodoCajero* cajeroMenorCola = NULL;
    
    while (actual != NULL) {
        int contadorCola = 0;
        nodoCliente* clienteActual = actual->inicio;
        while (clienteActual != NULL) {
            contadorCola++;
            clienteActual = clienteActual->siguiente;
        }
        
        if (contadorCola < menorCola) {
            menorCola = contadorCola;
            cajeroMenorCola = actual;
        }
        actual = actual->siguiente;
    }
    
    if (cajeroMenorCola != NULL) {
        nodoCliente* clienteActual = cajeroMenorCola->inicio;
        if (clienteActual == NULL) {
            cajeroMenorCola->inicio = nuevoCliente;
        } else {
            while (clienteActual->siguiente != NULL) {
                clienteActual = clienteActual->siguiente;
            }
            clienteActual->siguiente = nuevoCliente;
        }
        cout << "Cliente de tipo C agregado con éxito. " << endl;
    }
}

static void mostrarCajeros() {
    nodoCajero* actual = listaCajero;
    if (actual == NULL) {
        cout << "No hay cajeros disponibles." << endl;
        return;
    }
    
    cout << "Estado actual de las colas:" << endl;
    cout << "============================" << endl;
    
    while (actual != NULL) {
        cout << "Cajero ID: " << actual->getId() 
             << " | Caja: " << actual->getNumeroCaja() 
             << " | Nombre: " << actual->getNombreCajero() << endl;
        
        nodoCliente* cliente = actual->inicio;
        if (cliente == NULL) {
            cout << "  Cola vacía" << endl;
        } else {
            cout << "  Clientes en cola: ";
            while (cliente != NULL) {
                cout << "[Ticket:" << cliente->getFicha() 
                     << ", Edad:" << cliente->getEdad() 
                     << ", Tipo:" << cliente->getTipo() << "] ";
                cliente = cliente->siguiente;
            }
            cout << endl;
        }
        cout << "----------------------------" << endl;
        actual = actual->siguiente;
    }
}

void Cliente::atenderClientes() {
    if (listaCajero == NULL) {
        cout << "No hay cajeros disponibles." << endl;
        return;
    }
    
    nodoCajero* actual = listaCajero;
    bool clienteAtendido = false;
    
    while (actual != NULL) {
        if (actual->inicio != NULL) {
            nodoCliente* clienteParaAtender = actual->inicio;
            cout << "Atendiendo cliente - Ticket: " << clienteParaAtender->getFicha()
                 << ", Edad: " << clienteParaAtender->getEdad()
                 << ", Tipo: " << clienteParaAtender->getTipo()
                 << " en Caja: " << actual->getNumeroCaja() << endl;
            
            actual->inicio = clienteParaAtender->siguiente;
            delete clienteParaAtender;
            clienteAtendido = true;
            break;
        }
        actual = actual->siguiente;
    }
    
    if (!clienteAtendido) {
        cout << "No hay clientes en cola para atender." << endl;
    }
}

void Cliente::eliminarCliente() {
    int ticketBuscar;
    cout << "Ingrese el número de ticket del cliente a eliminar: ";
    cin >> ticketBuscar;
    
    nodoCajero* actual = listaCajero;
    bool ticketeEncontrado = false;
    
    while (actual != NULL && !ticketeEncontrado) {
        if (actual->inicio != NULL && actual->inicio->getFicha() == ticketBuscar) {
            nodoCliente* clienteActual = actual->inicio;
            actual->inicio = clienteActual->siguiente;
            delete clienteActual;
            cout << "Cliente eliminado" << endl;
            ticketeEncontrado = true;
            return;
        }
        
        nodoCliente* anterior = actual->inicio;
        if (anterior != NULL) {
            nodoCliente* clienteActual = anterior->siguiente;
            while (clienteActual != NULL) {
                if (clienteActual->getFicha() == ticketBuscar) {
                    anterior->siguiente = clienteActual->siguiente;
                    delete clienteActual;
                    cout << "Cliente eliminado" << endl;
                    ticketeEncontrado = true;
                    return;
                }
                anterior = clienteActual;
                clienteActual = clienteActual->siguiente;
            }
        }
        actual = actual->siguiente;
    }
    
    if (!ticketeEncontrado) {
        cout << "El tickete no existe" << endl;
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
        cout << endl << "Ingrese una opcion: ";
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
            cout << "\n\n"; 
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
        default:
            cout << "Opcion invalida" << endl;
            system("pause");
            break;
        }

    } while (opcion != 5);
}