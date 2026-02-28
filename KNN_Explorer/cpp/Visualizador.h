#ifndef VISUALIZADOR_H
#define VISUALIZADOR_H

/*
 * NOTA: Este archivo es la referencia conceptual del modulo de visualizacion.
 * En la version web, la visualizacion se hace con HTML5 Canvas (KNNCanvas.tsx).
 * 
 * Para compilar en C++ nativo con graficos, necesitas una libreria como SFML:
 *   - Instalar SFML: https://www.sfml-dev.org/download.php
 *   - Compilar con: g++ -o knn main.cpp KNN.cpp -lsfml-graphics -lsfml-window -lsfml-system
 *
 * Funciones que tendria este modulo:
 *   - dibujarEjes(ventana, anchoVentana, altoVentana)
 *   - dibujarPunto(ventana, x, y, clase, escala)
 *   - dibujarLineaVecino(ventana, x1, y1, x2, y2, distancia)
 *   - dibujarPuntoPrueba(ventana, x, y, claseResultado)
 *   - convertirAPixel(mathX, mathY, centroX, centroY, escala) -> (pixelX, pixelY)
 *   - convertirAMatematico(pixelX, pixelY, centroX, centroY, escala) -> (mathX, mathY)
 */

#include "Punto.h"

// Convierte coordenadas matematicas a pixeles de pantalla
inline void convertirAPixel(float mx, float my, float centroX, float centroY, float escala, float& px, float& py) {
    px = centroX + mx * escala;
    py = centroY - my * escala; // Y invertido en pantalla
}

// Convierte pixeles de pantalla a coordenadas matematicas
inline void convertirAMatematico(float px, float py, float centroX, float centroY, float escala, float& mx, float& my) {
    mx = (px - centroX) / escala;
    my = (centroY - py) / escala;
}

#endif // VISUALIZADOR_H
