#include "../factory/creador_figuras.h"
#include "../core/drone.h"
#include <emscripten/bind.h>
#include <vector>
#include <memory>

/**
 * Interfaz WebAssembly para comunicación con la web
 * 
 * Funciones expuestas:
 * - seleccionarFigura(id): Selecciona una figura por su ID
 * - actualizarAnimacion(deltaTime): Actualiza posiciones de drones
 * - obtenerPosicionDrone(indice): Obtiene x, y, color de un drone
 * - obtenerCantidadDrones(): Retorna el número de drones
 */

// Estado global del simulador
namespace {
    std::vector<Drone> drones;
    std::unique_ptr<FiguraBase> figuraActual;
    std::vector<PosicionDrone> posicionesObjetivo;
    
    int cantidadDrones = 500;
    float anchoCanvas = 900.0f;
    float altoCanvas = 600.0f;
    float velocidadTransicion = 0.012f;
    
    bool enTransicion = false;
    float progresoTransicion = 100.0f;
}

/**
 * Inicializar el sistema de drones
 */
void inicializarSimulador(int numDrones, float ancho, float alto) {
    cantidadDrones = numDrones;
    anchoCanvas = ancho;
    altoCanvas = alto;
    
    // Crear drones en posiciones aleatorias
    drones.clear();
    drones.reserve(cantidadDrones);
    
    auto posicionesIniciales = FiguraBase::generarPosicionesAleatorias(
        cantidadDrones, anchoCanvas, altoCanvas);
    
    for (int i = 0; i < cantidadDrones; ++i) {
        drones.emplace_back(
            i,
            posicionesIniciales[i].x,
            posicionesIniciales[i].y,
            posicionesIniciales[i].color
        );
    }
}

/**
 * Seleccionar una figura por su ID
 * Retorna true si la figura existe
 */
bool seleccionarFigura(const std::string& idFigura) {
    auto& creador = CreadorFiguras::obtenerInstancia();
    
    if (!creador.existeFigura(idFigura)) {
        return false;
    }
    
    figuraActual = creador.crearFigura(idFigura, cantidadDrones, anchoCanvas, altoCanvas);
    
    if (figuraActual) {
        posicionesObjetivo = figuraActual->generarPosiciones();
        
        // Asignar objetivos a los drones
        for (int i = 0; i < cantidadDrones && i < static_cast<int>(posicionesObjetivo.size()); ++i) {
            drones[i].establecerObjetivo(
                posicionesObjetivo[i].x,
                posicionesObjetivo[i].y
            );
            drones[i].establecerColorObjetivo(posicionesObjetivo[i].color);
        }
        
        enTransicion = true;
        progresoTransicion = 0.0f;
        return true;
    }
    
    return false;
}

/**
 * Actualizar la animación (llamado cada frame)
 * deltaTime en segundos
 */
void actualizarAnimacion(float deltaTime) {
    if (drones.empty()) return;
    
    float distanciaMaxima = 0.0f;
    
    for (auto& drone : drones) {
        drone.actualizarPosicion(velocidadTransicion);
        drone.actualizarColor(velocidadTransicion);
        
        float dist = drone.calcularDistanciaAlObjetivo();
        if (dist > distanciaMaxima) {
            distanciaMaxima = dist;
        }
    }
    
    // Calcular progreso de transición
    if (distanciaMaxima < 1.0f) {
        progresoTransicion = 100.0f;
        enTransicion = false;
    } else {
        progresoTransicion = std::max(0.0f, 100.0f - (distanciaMaxima / 5.0f));
    }
}

/**
 * Obtener posición X de un drone
 */
float obtenerDroneX(int indice) {
    if (indice >= 0 && indice < static_cast<int>(drones.size())) {
        return drones[indice].obtenerX();
    }
    return 0.0f;
}

/**
 * Obtener posición Y de un drone
 */
float obtenerDroneY(int indice) {
    if (indice >= 0 && indice < static_cast<int>(drones.size())) {
        return drones[indice].obtenerY();
    }
    return 0.0f;
}

/**
 * Obtener color de un drone (como string hex)
 */
std::string obtenerDroneColor(int indice) {
    if (indice >= 0 && indice < static_cast<int>(drones.size())) {
        return drones[indice].obtenerColor();
    }
    return "#FFFFFF";
}

/**
 * Obtener cantidad de drones activos
 */
int obtenerCantidadDrones() {
    return static_cast<int>(drones.size());
}

/**
 * Verificar si está en transición
 */
bool estaEnTransicion() {
    return enTransicion;
}

/**
 * Obtener progreso de transición (0-100)
 */
float obtenerProgresoTransicion() {
    return progresoTransicion;
}

/**
 * Obtener lista de figuras disponibles
 */
std::vector<std::string> obtenerFigurasDisponibles() {
    return CreadorFiguras::obtenerInstancia().obtenerFigurasDisponibles();
}

/**
 * Establecer velocidad de transición
 */
void establecerVelocidad(float velocidad) {
    velocidadTransicion = velocidad;
}

// Bindings para Emscripten
EMSCRIPTEN_BINDINGS(simulador_drones) {
    emscripten::function("inicializarSimulador", &inicializarSimulador);
    emscripten::function("seleccionarFigura", &seleccionarFigura);
    emscripten::function("actualizarAnimacion", &actualizarAnimacion);
    emscripten::function("obtenerDroneX", &obtenerDroneX);
    emscripten::function("obtenerDroneY", &obtenerDroneY);
    emscripten::function("obtenerDroneColor", &obtenerDroneColor);
    emscripten::function("obtenerCantidadDrones", &obtenerCantidadDrones);
    emscripten::function("estaEnTransicion", &estaEnTransicion);
    emscripten::function("obtenerProgresoTransicion", &obtenerProgresoTransicion);
    emscripten::function("obtenerFigurasDisponibles", &obtenerFigurasDisponibles);
    emscripten::function("establecerVelocidad", &establecerVelocidad);
    
    emscripten::register_vector<std::string>("VectorString");
}
