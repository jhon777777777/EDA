#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* ant;
    Nodo* sig;
};

Nodo* inicio = NULL;

void insertar(int valor, int pos) {
    Nodo* nuevo = new Nodo{valor, NULL, NULL};

    if (inicio == NULL || pos == 1) {
        nuevo->sig = inicio;
        if (inicio != NULL)
            inicio->ant = nuevo;
        inicio = nuevo;
        return;
    }

    Nodo* aux = inicio;
    int i = 1;

    while (aux->sig != NULL && i < pos - 1) {
        aux = aux->sig;
        i++;
    }

    nuevo->sig = aux->sig;
    nuevo->ant = aux;

    if (aux->sig != NULL)
        aux->sig->ant = nuevo;

    aux->sig = nuevo;
}

void eliminarPos(int pos) {
    if (inicio == NULL) return;

    Nodo* aux = inicio;

    if (pos == 1) {
        inicio = aux->sig;
        if (inicio != NULL)
            inicio->ant = NULL;
        delete aux;
        return;
    }

    int i = 1;
    while (aux != NULL && i < pos) {
        aux = aux->sig;
        i++;
    }

    if (aux == NULL) return;

    if (aux->sig != NULL)
        aux->sig->ant = aux->ant;

    aux->ant->sig = aux->sig;
    delete aux;
}

void eliminarValor(int valor) {
    Nodo* aux = inicio;

    while (aux != NULL && aux->dato != valor)
        aux = aux->sig;

    if (aux == NULL) return;

    if (aux == inicio) {
        inicio = aux->sig;
        if (inicio != NULL)
            inicio->ant = NULL;
    } else {
        aux->ant->sig = aux->sig;
        if (aux->sig != NULL)
            aux->sig->ant = aux->ant;
    }

    delete aux;
}

void mostrar() {
    Nodo* aux = inicio;

    if (aux == NULL) {
        cout << "Lista vacia\n";
        return;
    }

    cout << "NULL <-> ";
    while (aux != NULL) {
        cout << aux->dato << " <-> ";
        aux = aux->sig;
    }
    cout << "NULL\n";
}

void clean() {
    while (inicio != NULL) {
        Nodo* temp = inicio;
        inicio = inicio->sig;
        delete temp;
    }
}

int main() {
    insertar(10, 1);
    insertar(20, 2);
    insertar(30, 3);

    int op, val, pos;

    do {
        cout << "\n--- MENU LISTA DOBLEMENTE ENLAZADA ---\n";
        cout << "1. Mostrar\n";
        cout << "2. Insertar en posicion\n";
        cout << "3. Eliminar por posicion\n";
        cout << "4. Eliminar por valor\n";
        cout << "5. Limpiar lista\n";
        cout << "6. Salir\n";
        cin >> op;

        switch (op) {
            case 1:
                mostrar();
                break;

            case 2:
                cout << "Valor: ";
                cin >> val;
                cout << "Posicion: ";
                cin >> pos;
                insertar(val, pos);
                break;

            case 3:
                cout << "Posicion: ";
                cin >> pos;
                eliminarPos(pos);
                break;

            case 4:
                cout << "Valor: ";
                cin >> val;
                eliminarValor(val);
                break;

            case 5:
                clean();
                cout << "Lista limpiada\n";
                break;

            case 6:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while (op != 6);

    return 0;
}
