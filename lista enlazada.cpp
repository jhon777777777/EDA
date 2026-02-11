#include <iostream>
using namespace std;

class Nodo {
public:
    int dato;
    Nodo* siguiente;

    Nodo(int d) {
        dato = d;
        siguiente = NULL;
    }
};

class Lista {
private:
    Nodo* inicio;

public:
    // Constructor
    Lista() {
        inicio = NULL;

        insertar(23);
        insertar(66);
        insertar(10);
    }

    void insertar(int valor) {
        Nodo* nuevo = new Nodo(valor);

        if (inicio == NULL) {
            inicio = nuevo;
        } else {
            Nodo* aux = inicio;
            while (aux->siguiente != NULL) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
    }

    void eliminar(int valor) {
        if (inicio == NULL) {
            cout << "Lista vacia\n";
            return;
        }

        if (inicio->dato == valor) {
            Nodo* temp = inicio;
            inicio = inicio->siguiente;
            delete temp;
            cout << "Dato eliminado\n";
            return;
        }

        Nodo* aux = inicio;
        while (aux->siguiente != NULL && aux->siguiente->dato != valor) {
            aux = aux->siguiente;
        }

        if (aux->siguiente != NULL) {
            Nodo* temp = aux->siguiente;
            aux->siguiente = temp->siguiente;
            delete temp;
            cout << "Dato eliminado\n";
        } else {
            cout << "Dato no encontrado\n";
        }
    }

    // Mostrar lista
    void mostrar() {
        Nodo* aux = inicio;

        if (aux == NULL) {
            cout << "Lista vacia\n";
            return;
        }

        cout << "Inicio -> ";
        while (aux != NULL) {
            cout << aux->dato << " -> ";
            aux = aux->siguiente;
        }
        cout << "NULL\n";
    }
};


int main() {
    Lista lista;
    int opcion, valor;

    do {
        cout << "\n===== MENU LISTA ENLAZADA =====\n";
        cout << "1. Mostrar\n";
        cout << "2. Insertar\n";
        cout << "3. Eliminar\n";
        cout << "4. Salir\n";
        cin >> opcion;

        switch (opcion) {
        case 1:
            lista.mostrar();
            break;

        case 2:
            cout << "Ingrese valor: ";
            cin >> valor;
            lista.insertar(valor);
            break;

        case 3:
            cout << "Ingrese valor: ";
            cin >> valor;
            lista.eliminar(valor);
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 4);

    return 0;
}
