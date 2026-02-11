#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

// =====================
// NODO
// =====================
struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;

    Nodo(int v) {
        dato = v;
        izq = der = NULL;
    }
};

// =====================
// ARBOL BINARIO
// =====================
class ArbolBinario {
private:
    Nodo* raiz;

    // ---------- INSERCION ----------
    Nodo* insertar(Nodo* r, int v) {
        if (!r) return new Nodo(v);

        if (v < r->dato)
            r->izq = insertar(r->izq, v);
        else if (v > r->dato)
            r->der = insertar(r->der, v);

        return r;
    }

    // ---------- BUSCAR ----------
    bool buscar(Nodo* r, int v) {
        if (!r) return false;
        if (r->dato == v) return true;
        if (v < r->dato) return buscar(r->izq, v);
        return buscar(r->der, v);
    }

    // ---------- RECORRIDOS ----------
    void inOrden(Nodo* r, vector<int>& v) {
        if (r) {
            inOrden(r->izq, v);
            v.push_back(r->dato);
            inOrden(r->der, v);
        }
    }

    void preOrden(Nodo* r, vector<int>& v) {
        if (r) {
            v.push_back(r->dato);
            preOrden(r->izq, v);
            preOrden(r->der, v);
        }
    }

    void postOrden(Nodo* r, vector<int>& v) {
        if (r) {
            postOrden(r->izq, v);
            postOrden(r->der, v);
            v.push_back(r->dato);
        }
    }

    // ---------- ALTURA ----------
    int altura(Nodo* r) {
        if (!r) return 0;
        return 1 + max(altura(r->izq), altura(r->der));
    }

    // ---------- DIBUJAR ----------
    void dibujar(Nodo* r, int fila, int col, int sep,
                 vector<vector<char>>& canvas) {
        if (!r) return;

        string s = to_string(r->dato);
        for (int i = 0; i < s.size(); i++)
            canvas[fila][col + i] = s[i];

        if (r->izq) {
            canvas[fila + 1][col - sep / 2] = '/';
            dibujar(r->izq, fila + 2, col - sep, sep / 2, canvas);
        }
        if (r->der) {
            canvas[fila + 1][col + sep / 2] = '\\';
            dibujar(r->der, fila + 2, col + sep, sep / 2, canvas);
        }
    }

public:
    ArbolBinario() { raiz = NULL; }

    void insertar(int v) { raiz = insertar(raiz, v); }
    bool buscar(int v) { return buscar(raiz, v); }

    // ---------- MOSTRAR ARBOL PERFECTO ----------
    void mostrarArbol() {
        if (!raiz) {
            cout << "Arbol vacio\n";
            return;
        }

        int h = altura(raiz);
        int filas = h * 2;
        int cols = pow(2, h + 1);

        vector<vector<char>> canvas(filas, vector<char>(cols, ' '));

        dibujar(raiz, 0, cols / 2, cols / 4, canvas);

        for (auto& fila : canvas) {
            for (char c : fila) cout << c;
            cout << endl;
        }
    }

    // ---------- MOSTRAR RECORRIDOS ----------
    void mostrarInOrden() {
        vector<int> v;
        inOrden(raiz, v);
        for (int x : v) cout << x << " ";
        cout << endl;
    }

    void mostrarPreOrden() {
        vector<int> v;
        preOrden(raiz, v);
        for (int x : v) cout << x << " ";
        cout << endl;
    }

    void mostrarPostOrden() {
        vector<int> v;
        postOrden(raiz, v);
        for (int x : v) cout << x << " ";
        cout << endl;
    }
};

// =====================
// MAIN
// =====================
int main() {
    ArbolBinario arbol;

    int datos[] = {5,2,9,1,3,7,10,6,8,11};
    for (int x : datos)
        arbol.insertar(x);

    int op, x;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Mostrar arbol\n";
        cout << "2. Insertar\n";
        cout << "3. Buscar\n";
        cout << "4. Eliminar\n";
        cout << "5. InOrden\n";
        cout << "6. PreOrden\n";
        cout << "7. PostOrden\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
        case 1: arbol.mostrarArbol(); break;
        case 2: cout << "Valor: "; cin >> x; arbol.insertar(x); break;
        case 3: cout << "Valor: "; cin >> x;
                cout << (arbol.buscar(x) ? "Encontrado\n" : "No encontrado\n");
                break;
        case 5: arbol.mostrarInOrden(); break;
        case 6: arbol.mostrarPreOrden(); break;
        case 7: arbol.mostrarPostOrden(); break;
        }
    } while (op != 0);

    return 0;
}
