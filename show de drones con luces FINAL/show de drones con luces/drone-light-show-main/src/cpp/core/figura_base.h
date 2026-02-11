#ifndef FIGURA_BASE_H
#define FIGURA_BASE_H

#include <vector>
#include <string>

/**
 * Estructura que representa la posición y color de un drone en una formación
 */
struct PosicionDrone {
    float x;
    float y;
    std::string color;
    
    PosicionDrone(float x = 0, float y = 0, const std::string& color = "#FFFFFF")
        : x(x), y(y), color(color) {}
};

/**
 * Clase base abstracta para todas las figuras del show de drones
 * 
 * Todas las figuras heredan de esta clase y deben implementar
 * el método generarPosiciones() que calcula las posiciones de los drones.
 */
class FiguraBase {
protected:
    std::string id;           // Identificador único de la figura
    std::string nombre;       // Nombre para mostrar
    std::string categoria;    // Categoría (textos, iconos, simbolos)
    int cantidadDrones;       // Número de drones a usar
    float anchoCanvas;        // Ancho del área de dibujo
    float altoCanvas;         // Alto del área de dibujo
    
    // Colores predefinidos para las formaciones
    static const std::string COLOR_DORADO;
    static const std::string COLOR_CELESTE;
    static const std::string COLOR_BLANCO;
    static const std::string COLOR_ROJO;
    static const std::string COLOR_MAGENTA;
    static const std::string COLOR_AMARILLO;
    static const std::string COLOR_NARANJA;

public:
    // Constructor
    FiguraBase(const std::string& id, const std::string& nombre, 
               const std::string& categoria, int cantidadDrones,
               float anchoCanvas, float altoCanvas);
    
    // Destructor virtual para herencia correcta
    virtual ~FiguraBase() = default;
    
    // Método abstracto que cada figura debe implementar
    virtual std::vector<PosicionDrone> generarPosiciones() = 0;
    
    // Getters
    std::string obtenerId() const;
    std::string obtenerNombre() const;
    std::string obtenerCategoria() const;
    int obtenerCantidadDrones() const;
    
    // Utilidades para generar patrones
    static std::vector<PosicionDrone> generarPosicionesAleatorias(
        int cantidad, float ancho, float alto);
    
protected:
    // Helpers para crear patrones de texto
    std::vector<PosicionDrone> crearBarraVertical(
        float x, float yInicio, float yFin, float grosor, const std::string& color);
    
    std::vector<PosicionDrone> crearBarraHorizontal(
        float xInicio, float xFin, float y, float grosor, const std::string& color);
    
    std::vector<PosicionDrone> crearBarraDiagonal(
        float x1, float y1, float x2, float y2, float grosor, const std::string& color);
    
    std::vector<PosicionDrone> crearCirculo(
        float centroX, float centroY, float radio, int puntos, const std::string& color);
    
    std::vector<PosicionDrone> crearArco(
        float centroX, float centroY, float radio, 
        float anguloInicio, float anguloFin, int puntos, const std::string& color);
    
    // Centro del canvas
    float centroX() const;
    float centroY() const;
};

#endif // FIGURA_BASE_H
