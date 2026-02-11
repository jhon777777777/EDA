#include "drone.h"
#include <cmath>
#include <sstream>
#include <iomanip>

/**
 * Implementación de la clase Drone
 */

Drone::Drone(int id, float x, float y, const std::string& color, float tamano)
    : id(id), x(x), y(y), objetivoX(x), objetivoY(y), 
      color(color), colorObjetivo(color), tamano(tamano) {}

// Getters
int Drone::obtenerId() const { return id; }
float Drone::obtenerX() const { return x; }
float Drone::obtenerY() const { return y; }
float Drone::obtenerObjetivoX() const { return objetivoX; }
float Drone::obtenerObjetivoY() const { return objetivoY; }
std::string Drone::obtenerColor() const { return color; }
std::string Drone::obtenerColorObjetivo() const { return colorObjetivo; }
float Drone::obtenerTamano() const { return tamano; }

// Setters
void Drone::establecerPosicion(float nuevoX, float nuevoY) {
    x = nuevoX;
    y = nuevoY;
}

void Drone::establecerObjetivo(float nuevoObjetivoX, float nuevoObjetivoY) {
    objetivoX = nuevoObjetivoX;
    objetivoY = nuevoObjetivoY;
}

void Drone::establecerColor(const std::string& nuevoColor) {
    color = nuevoColor;
}

void Drone::establecerColorObjetivo(const std::string& nuevoColorObjetivo) {
    colorObjetivo = nuevoColorObjetivo;
}

void Drone::establecerTamano(float nuevoTamano) {
    tamano = nuevoTamano;
}

// Interpolación lineal
float Drone::interpolar(float inicio, float fin, float t) {
    return inicio + (fin - inicio) * t;
}

// Actualizar posición con interpolación suave
void Drone::actualizarPosicion(float velocidad) {
    if (!haLlegadoAlObjetivo()) {
        x = interpolar(x, objetivoX, velocidad);
        y = interpolar(y, objetivoY, velocidad);
    } else {
        x = objetivoX;
        y = objetivoY;
    }
}

// Calcular distancia euclidiana al objetivo
float Drone::calcularDistanciaAlObjetivo() const {
    float dx = objetivoX - x;
    float dy = objetivoY - y;
    return std::sqrt(dx * dx + dy * dy);
}

// Verificar si el drone ha llegado al objetivo
bool Drone::haLlegadoAlObjetivo(float umbral) const {
    return calcularDistanciaAlObjetivo() < umbral;
}

// Convertir hex a RGB
static void hexARgb(const std::string& hex, int& r, int& g, int& b) {
    std::string hexLimpio = hex;
    if (hexLimpio[0] == '#') {
        hexLimpio = hexLimpio.substr(1);
    }
    
    unsigned int valor;
    std::stringstream ss;
    ss << std::hex << hexLimpio;
    ss >> valor;
    
    r = (valor >> 16) & 0xFF;
    g = (valor >> 8) & 0xFF;
    b = valor & 0xFF;
}

// Convertir RGB a hex
static std::string rgbAHex(int r, int g, int b) {
    std::stringstream ss;
    ss << "#" << std::hex << std::setfill('0')
       << std::setw(2) << r
       << std::setw(2) << g
       << std::setw(2) << b;
    return ss.str();
}

// Interpolación de color
std::string Drone::interpolarColor(const std::string& color1, const std::string& color2, float t) {
    int r1, g1, b1, r2, g2, b2;
    hexARgb(color1, r1, g1, b1);
    hexARgb(color2, r2, g2, b2);
    
    int r = static_cast<int>(interpolar(static_cast<float>(r1), static_cast<float>(r2), t));
    int g = static_cast<int>(interpolar(static_cast<float>(g1), static_cast<float>(g2), t));
    int b = static_cast<int>(interpolar(static_cast<float>(b1), static_cast<float>(b2), t));
    
    // Clamp valores
    r = std::max(0, std::min(255, r));
    g = std::max(0, std::min(255, g));
    b = std::max(0, std::min(255, b));
    
    return rgbAHex(r, g, b);
}

// Actualizar color con interpolación
void Drone::actualizarColor(float velocidad) {
    if (color != colorObjetivo) {
        color = interpolarColor(color, colorObjetivo, velocidad);
    }
}
