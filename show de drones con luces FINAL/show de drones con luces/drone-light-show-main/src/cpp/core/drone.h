#ifndef DRONE_H
#define DRONE_H

#include <string>

/**
 * Clase Drone - Representa un drone individual en el show de luces 2D
 * 
 * Cada drone tiene una posición actual (x, y) y una posición objetivo.
 * El drone se mueve suavemente hacia su objetivo mediante interpolación.
 * Solo coordenadas 2D - no hay eje Z ni profundidad.
 */
class Drone {
private:
    int id;
    
    // Posición actual del drone
    float x;
    float y;
    
    // Posición objetivo hacia donde se mueve
    float objetivoX;
    float objetivoY;
    
    // Color del drone (formato hexadecimal)
    std::string color;
    std::string colorObjetivo;
    
    // Tamaño visual del drone
    float tamano;

public:
    // Constructor
    Drone(int id, float x, float y, const std::string& color = "#FFFFFF", float tamano = 2.0f);
    
    // Getters
    int obtenerId() const;
    float obtenerX() const;
    float obtenerY() const;
    float obtenerObjetivoX() const;
    float obtenerObjetivoY() const;
    std::string obtenerColor() const;
    std::string obtenerColorObjetivo() const;
    float obtenerTamano() const;
    
    // Setters
    void establecerPosicion(float x, float y);
    void establecerObjetivo(float x, float y);
    void establecerColor(const std::string& color);
    void establecerColorObjetivo(const std::string& color);
    void establecerTamano(float tamano);
    
    // Movimiento
    void actualizarPosicion(float velocidad);
    float calcularDistanciaAlObjetivo() const;
    bool haLlegadoAlObjetivo(float umbral = 0.5f) const;
    
    // Interpolación de color
    void actualizarColor(float velocidad);
    
    // Utilidades
    static float interpolar(float inicio, float fin, float t);
    static std::string interpolarColor(const std::string& color1, const std::string& color2, float t);
};

#endif // DRONE_H
