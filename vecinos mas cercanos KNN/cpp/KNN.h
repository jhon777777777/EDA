#ifndef KNN_H
#define KNN_H

#include "Punto.h"
#include <vector>

// Calcula la distancia euclidiana entre dos puntos
float calcularDistanciaEuclidiana(const Punto& p1, const Punto& p2);

// Obtiene los k vecinos mas cercanos al puntoNuevo
std::vector<VecinoConDistancia> obtenerVecinos(
    const std::vector<Punto>& puntos,
    const Punto& puntoNuevo,
    int k
);

// Clasifica el puntoNuevo segun los k vecinos mas cercanos
// Retorna la clase ganadora (0 o 1)
int clasificar(
    const std::vector<Punto>& puntos,
    const Punto& puntoNuevo,
    int k,
    std::vector<VecinoConDistancia>& vecinosResultado
);

#endif // KNN_H
