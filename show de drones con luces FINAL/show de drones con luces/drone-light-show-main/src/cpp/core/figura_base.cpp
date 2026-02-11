#include "figura_base.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Definición de colores estáticos
const std::string FiguraBase::COLOR_DORADO = "#FFD700";
const std::string FiguraBase::COLOR_CELESTE = "#00D4FF";
const std::string FiguraBase::COLOR_BLANCO = "#FFFFFF";
const std::string FiguraBase::COLOR_ROJO = "#FF3333";
const std::string FiguraBase::COLOR_MAGENTA = "#FF00FF";
const std::string FiguraBase::COLOR_AMARILLO = "#FFFF00";
const std::string FiguraBase::COLOR_NARANJA = "#FF8C00";

// Constructor
FiguraBase::FiguraBase(const std::string& id, const std::string& nombre,
                       const std::string& categoria, int cantidadDrones,
                       float anchoCanvas, float altoCanvas)
    : id(id), nombre(nombre), categoria(categoria),
      cantidadDrones(cantidadDrones), anchoCanvas(anchoCanvas), altoCanvas(altoCanvas) {}

// Getters
std::string FiguraBase::obtenerId() const { return id; }
std::string FiguraBase::obtenerNombre() const { return nombre; }
std::string FiguraBase::obtenerCategoria() const { return categoria; }
int FiguraBase::obtenerCantidadDrones() const { return cantidadDrones; }

// Centro del canvas
float FiguraBase::centroX() const { return anchoCanvas / 2.0f; }
float FiguraBase::centroY() const { return altoCanvas / 2.0f; }

// Generar posiciones aleatorias
std::vector<PosicionDrone> FiguraBase::generarPosicionesAleatorias(
    int cantidad, float ancho, float alto) {
    
    std::vector<PosicionDrone> posiciones;
    posiciones.reserve(cantidad);
    
    static bool inicializado = false;
    if (!inicializado) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        inicializado = true;
    }
    
    for (int i = 0; i < cantidad; ++i) {
        float x = static_cast<float>(std::rand()) / RAND_MAX * ancho;
        float y = static_cast<float>(std::rand()) / RAND_MAX * alto;
        posiciones.emplace_back(x, y, "#FFFFFF");
    }
    
    return posiciones;
}

// Crear barra vertical
std::vector<PosicionDrone> FiguraBase::crearBarraVertical(
    float x, float yInicio, float yFin, float grosor, const std::string& color) {
    
    std::vector<PosicionDrone> posiciones;
    float paso = 3.0f;
    
    for (float gx = -grosor/2; gx <= grosor/2; gx += paso) {
        for (float y = yInicio; y <= yFin; y += paso) {
            posiciones.emplace_back(x + gx, y, color);
        }
    }
    
    return posiciones;
}

// Crear barra horizontal
std::vector<PosicionDrone> FiguraBase::crearBarraHorizontal(
    float xInicio, float xFin, float y, float grosor, const std::string& color) {
    
    std::vector<PosicionDrone> posiciones;
    float paso = 3.0f;
    
    for (float gy = -grosor/2; gy <= grosor/2; gy += paso) {
        for (float x = xInicio; x <= xFin; x += paso) {
            posiciones.emplace_back(x, y + gy, color);
        }
    }
    
    return posiciones;
}

// Crear barra diagonal
std::vector<PosicionDrone> FiguraBase::crearBarraDiagonal(
    float x1, float y1, float x2, float y2, float grosor, const std::string& color) {
    
    std::vector<PosicionDrone> posiciones;
    
    float dx = x2 - x1;
    float dy = y2 - y1;
    float longitud = std::sqrt(dx * dx + dy * dy);
    int pasos = static_cast<int>(longitud / 3.0f);
    
    // Vector perpendicular normalizado
    float perpX = -dy / longitud;
    float perpY = dx / longitud;
    
    for (int i = 0; i <= pasos; ++i) {
        float t = static_cast<float>(i) / pasos;
        float baseX = x1 + dx * t;
        float baseY = y1 + dy * t;
        
        for (float g = -grosor/2; g <= grosor/2; g += 3.0f) {
            posiciones.emplace_back(baseX + perpX * g, baseY + perpY * g, color);
        }
    }
    
    return posiciones;
}

// Crear círculo
std::vector<PosicionDrone> FiguraBase::crearCirculo(
    float centroX, float centroY, float radio, int puntos, const std::string& color) {
    
    std::vector<PosicionDrone> posiciones;
    posiciones.reserve(puntos);
    
    for (int i = 0; i < puntos; ++i) {
        float angulo = (2.0f * M_PI * i) / puntos;
        float x = centroX + radio * std::cos(angulo);
        float y = centroY + radio * std::sin(angulo);
        posiciones.emplace_back(x, y, color);
    }
    
    return posiciones;
}

// Crear arco
std::vector<PosicionDrone> FiguraBase::crearArco(
    float centroX, float centroY, float radio,
    float anguloInicio, float anguloFin, int puntos, const std::string& color) {
    
    std::vector<PosicionDrone> posiciones;
    posiciones.reserve(puntos);
    
    float rangoAngulo = anguloFin - anguloInicio;
    
    for (int i = 0; i < puntos; ++i) {
        float t = static_cast<float>(i) / (puntos - 1);
        float angulo = anguloInicio + rangoAngulo * t;
        float x = centroX + radio * std::cos(angulo);
        float y = centroY + radio * std::sin(angulo);
        posiciones.emplace_back(x, y, color);
    }
    
    return posiciones;
}
