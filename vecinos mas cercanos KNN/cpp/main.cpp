/*
 * =============================================================
 * KNN Visualizador - Version Consola C++
 * =============================================================
 * 
 * Este programa implementa el algoritmo K-Nearest Neighbors
 * con entrada por consola. La version grafica equivalente
 * esta en los archivos web (TypeScript/React).
 *
 * Compilar:
 *   g++ -o knn main.cpp KNN.cpp -std=c++17
 *
 * Ejecutar:
 *   ./knn
 *
 * Para version grafica con SFML:
 *   g++ -o knn main.cpp KNN.cpp -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
 * =============================================================
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include "KNN.h"
#include "Visualizador.h"

using namespace std;

void mostrarMenu() {
    cout << "\n===== KNN VISUALIZADOR =====" << endl;
    cout << "1. Agregar punto Clase A (Rojo)" << endl;
    cout << "2. Agregar punto Clase B (Azul)" << endl;
    cout << "3. Clasificar un punto nuevo" << endl;
    cout << "4. Cambiar valor de K" << endl;
    cout << "5. Ver todos los puntos" << endl;
    cout << "6. Limpiar todos los puntos" << endl;
    cout << "7. Salir" << endl;
    cout << "Opcion: ";
}

void mostrarPuntos(const vector<Punto>& puntos) {
    if (puntos.empty()) {
        cout << "No hay puntos registrados." << endl;
        return;
    }
    cout << "\n--- Puntos de entrenamiento ---" << endl;
    cout << left << setw(6) << "#" << setw(10) << "X" << setw(10) << "Y" << "Clase" << endl;
    cout << string(36, '-') << endl;
    for (size_t i = 0; i < puntos.size(); i++) {
        cout << left << setw(6) << (i + 1)
             << setw(10) << fixed << setprecision(2) << puntos[i].x
             << setw(10) << fixed << setprecision(2) << puntos[i].y
             << (puntos[i].clase == 0 ? "A (Rojo)" : "B (Azul)") << endl;
    }
    cout << "Total: " << puntos.size() << " puntos" << endl;
}

void mostrarResultado(const Punto& puntoNuevo, int claseResultado,
                       const vector<VecinoConDistancia>& vecinos, int k) {
    cout << "\n===== RESULTADO =====" << endl;
    cout << "Punto (" << fixed << setprecision(2) << puntoNuevo.x
         << ", " << puntoNuevo.y << ") -> ";
    if (claseResultado == 0)
        cout << "CLASE A (ROJO)" << endl;
    else
        cout << "CLASE B (AZUL)" << endl;

    cout << "\nVecinos mas cercanos (k=" << k << "):" << endl;
    cout << left << setw(6) << "#" << setw(10) << "X" << setw(10) << "Y"
         << setw(14) << "Distancia" << "Clase" << endl;
    cout << string(50, '-') << endl;

    for (size_t i = 0; i < vecinos.size(); i++) {
        cout << left << setw(6) << (i + 1)
             << setw(10) << fixed << setprecision(2) << vecinos[i].punto.x
             << setw(10) << fixed << setprecision(2) << vecinos[i].punto.y
             << setw(14) << fixed << setprecision(4) << vecinos[i].distancia
             << (vecinos[i].punto.clase == 0 ? "A (Rojo)" : "B (Azul)") << endl;
    }
}

int main() {
    vector<Punto> puntos;
    int k = 3;
    int opcion;

    cout << "=== Algoritmo KNN - K Nearest Neighbors ===" << endl;
    cout << "K inicial = " << k << endl;

    while (true) {
        mostrarMenu();
        
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intente de nuevo." << endl;
            continue;
        }

        if (opcion == 7) {
            cout << "Saliendo..." << endl;
            break;
        }

        float x, y;

        switch (opcion) {
            case 1: // Agregar punto Rojo
            case 2: {
                cout << "Ingrese X: ";
                cin >> x;
                cout << "Ingrese Y: ";
                cin >> y;
                Punto p;
                p.x = x;
                p.y = y;
                p.clase = (opcion == 1) ? 0 : 1;
                puntos.push_back(p);
                cout << "Punto (" << x << ", " << y << ") agregado como "
                     << (opcion == 1 ? "Clase A (Rojo)" : "Clase B (Azul)") << endl;
                break;
            }

            case 3: { // Clasificar
                if (puntos.empty()) {
                    cout << "Primero agrega puntos de entrenamiento." << endl;
                    break;
                }
                cout << "Ingrese X del punto a clasificar: ";
                cin >> x;
                cout << "Ingrese Y del punto a clasificar: ";
                cin >> y;

                Punto puntoNuevo;
                puntoNuevo.x = x;
                puntoNuevo.y = y;
                puntoNuevo.clase = -1;

                vector<VecinoConDistancia> vecinos;
                int efectivoK = min(k, (int)puntos.size());
                int resultado = clasificar(puntos, puntoNuevo, efectivoK, vecinos);

                mostrarResultado(puntoNuevo, resultado, vecinos, efectivoK);
                break;
            }

            case 4: { // Cambiar K
                cout << "Nuevo valor de K (actual=" << k << "): ";
                cin >> k;
                if (k < 1) k = 1;
                cout << "K actualizado a " << k << endl;
                break;
            }

            case 5: // Ver puntos
                mostrarPuntos(puntos);
                break;

            case 6: // Limpiar
                puntos.clear();
                cout << "Todos los puntos eliminados." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }
    }

    return 0;
}
