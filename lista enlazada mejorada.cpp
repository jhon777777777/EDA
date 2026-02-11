#include <iostream>
using namespace std;

// ===== Nodo =====
class Nodo {
public:
    int dato;
    Nodo* siguiente;

    Nodo(int d) {
        dato = d;
        siguiente = NULL;
    }
};

// ===== Lista =====
class Lista {
private:
    Nodo* inicio;

public:
    Lista() {
        inicio = NULL;

        // Datos iniciales
        insertarAtras(23);
        insertarAtras(66);
        insertarAtras(10);
    }

    // ===== AGREGAR ADELANTE =====
    void insertarAdelante(int valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = inicio;
        inicio = nuevo;
    }

    // ===== AGREGAR ATRÁS =====
    void insertarAtras(int valor) {
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

    // ===== AGREGAR EN POSICIÓN =====
    void insertarPosicion(int valor, int pos) {
        if (pos == 1) {
            insertarAdelante(valor);
            return;
        }

        Nodo* aux = inicio;
        for (int i = 1; i < pos - 1 && aux != NULL; i++) {
            aux = aux->siguiente;
        }

        if (aux == NULL) {
            cout << "Posicion invalida\n";
            return;
        }

        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }

    // ===== ELIMINAR ADELANTE =====
    void eliminarAdelante() {
        if (inicio == NULL) {
            cout << "Lista vacia\n";
            return;
        }

        Nodo* temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
    }

    // ===== ELIMINAR ATRÁS =====
    void eliminarAtras() {
        if (inicio == NULL) {
            cout << "Lista vacia\n";
            return;
        }

        if (inicio->siguiente == NULL) {
            delete inicio;
            inicio = NULL;
            return;
        }

        Nodo* aux = inicio;
        while (aux->siguiente->siguiente != NULL) {
            aux = aux->siguiente;
        }

        delete aux->siguiente;
        aux->siguiente = NULL;
    }

    // ===== ELIMINAR EN POSICIÓN =====
    void eliminarPosicion(int pos) {
        if (pos == 1) {
            eliminarAdelante();
            return;
        }

        Nodo* aux = inicio;
        for (int i = 1; i < pos - 1 && aux != NULL; i++) {
            aux = aux->siguiente;
        }

        if (aux == NULL || aux->siguiente == NULL) {
            cout << "Posicion invalida\n";
            return;
        }

        Nodo* temp = aux->siguiente;
        aux->siguiente = temp->siguiente;
        delete temp;
    }

    // ===== MOSTRAR =====
    void mostrar() {
        Nodo* aux = inicio;
        cout << "Inicio -> ";
        while (aux != NULL) {
            cout << aux->dato << " -> ";
            aux = aux->siguiente;
        }
        cout << "NULL\n";
    }
};

// ===== MAIN =====
int main() {
    Lista lista;
    int opcion, valor, pos;

    do {
        cout << "\nMENU LISTA ENLAZADA\n";
        cout << "1. Mostrar\n";
        cout << "2. Agregar adelante\n";
        cout << "3. Agregar atras\n";
        cout << "4. Agregar en posicion\n";
        cout << "5. Eliminar adelante\n";
        cout << "6. Eliminar atras\n";
        cout << "7. Eliminar en posicion\n";
        cout << "8. Salir\n";
        cin >> opcion;

        switch (opcion) {
        case 1:
            lista.mostrar();
            break;

        case 2:
            cout << "Valor: ";
            cin >> valor;
            lista.insertarAdelante(valor);
            break;

        case 3:
            cout << "Valor: ";
            cin >> valor;
            lista.insertarAtras(valor);
            break;

        case 4:
            cout << "Valor: ";
            cin >> valor;
            cout << "Posicion: ";
            cin >> pos;
            lista.insertarPosicion(valor, pos);
            break;

        case 5:
            lista.eliminarAdelante();
            break;

        case 6:
            lista.eliminarAtras();
            break;

        case 7:
            cout << "Posicion: ";
            cin >> pos;
            lista.eliminarPosicion(pos);
            break;
        }

    } while (opcion != 8);

    return 0;
}
