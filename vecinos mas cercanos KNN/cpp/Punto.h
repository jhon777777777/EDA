#ifndef PUNTO_H
#define PUNTO_H

struct Punto {
    float x, y;
    int clase; // 0: Rojo (A), 1: Azul (B), -1: Sin clasificar
};

struct VecinoConDistancia {
    Punto punto;
    float distancia;
};

#endif // PUNTO_H
