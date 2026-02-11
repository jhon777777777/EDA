#include <iostream>
using namespace std;

#define MAX 6

// Prototipos
bool estaVacia();
bool estaLlena();
void push(int);
int pop();
void clean();
void imprimir();

// Cola circular
int cola[MAX];
int frente = 0;
int final = 0;
int contador = 0;

bool estaVacia() {
    return contador == 0;
}

bool estaLlena() {
    return contador == MAX;
}

void push(int valor) {
    if (!estaLlena()) {
        cola[final] = valor;
        final = (final + 1) % MAX;
        contador++;
        cout << "Se inserto el elemento: " << valor << endl;
    } else {
        cout << "Cola llena" << endl;
    }
}

int pop() {
    if (!estaVacia()) {
        int valor = cola[frente];
        frente = (frente + 1) % MAX;
        contador--;
        cout << "Se elimino el elemento: " << valor << endl;
        return valor;
    } else {
        cout << "Cola vacia" << endl;
        return -1;
    }
}

void clean() {
    frente = 0;
    final = 0;
    contador = 0;
    cout << "La cola fue limpiada" << endl;
}

void imprimir() {
    cout << "Elementos en la cola:" << endl;
    int i = frente;
    for (int c = 0; c < contador; c++) {
        cout << cola[i] << endl;
        i = (i + 1) % MAX;
    }
}

int main() {
    // Valores iniciales
    push(10);
    push(20);
    push(30);

    int opcion, valor;

    do {
        cout << "\nMENU" << endl;
        cout << "1. push" << endl;
        cout << "2. pop" << endl;
        cout << "3. clean" << endl;
        cout << "4. imprimir" << endl;
        cout << "5. salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Valor: ";
                cin >> valor;
                push(valor);
                break;
            case 2:
                pop();
                break;
            case 3:
                clean();
                break;
            case 4:
                imprimir();
                break;
        }
    } while (opcion != 5);

    return 0;
}
