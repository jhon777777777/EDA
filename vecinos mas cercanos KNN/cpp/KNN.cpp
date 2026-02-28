#include "KNN.h"
#include <cmath>
#include <algorithm>

float calcularDistanciaEuclidiana(const Punto& p1, const Punto& p2) {
    return std::sqrt(
        std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2)
    );
}

std::vector<VecinoConDistancia> obtenerVecinos(
    const std::vector<Punto>& puntos,
    const Punto& puntoNuevo,
    int k
) {
    std::vector<VecinoConDistancia> conDistancia;
    conDistancia.reserve(puntos.size());

    for (const auto& p : puntos) {
        VecinoConDistancia v;
        v.punto = p;
        v.distancia = calcularDistanciaEuclidiana(p, puntoNuevo);
        conDistancia.push_back(v);
    }

    // Ordenar de menor a mayor distancia
    std::sort(conDistancia.begin(), conDistancia.end(),
        [](const VecinoConDistancia& a, const VecinoConDistancia& b) {
            return a.distancia < b.distancia;
        }
    );

    // Tomar solo los primeros k
    int efectivoK = std::min(k, (int)conDistancia.size());
    conDistancia.resize(efectivoK);

    return conDistancia;
}

int clasificar(
    const std::vector<Punto>& puntos,
    const Punto& puntoNuevo,
    int k,
    std::vector<VecinoConDistancia>& vecinosResultado
) {
    vecinosResultado = obtenerVecinos(puntos, puntoNuevo, k);

    int votosRojo = 0;
    int votosAzul = 0;

    for (const auto& v : vecinosResultado) {
        if (v.punto.clase == 0) votosRojo++;
        else if (v.punto.clase == 1) votosAzul++;
    }

    return (votosRojo >= votosAzul) ? 0 : 1;
}
