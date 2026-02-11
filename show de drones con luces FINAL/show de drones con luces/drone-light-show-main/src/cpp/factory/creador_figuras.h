#ifndef CREADOR_FIGURAS_H
#define CREADOR_FIGURAS_H

#include "../core/figura_base.h"
#include <memory>
#include <string>
#include <map>
#include <functional>

/**
 * Factory para crear figuras
 * 
 * Recibe un identificador desde la web y crea la figura correspondiente.
 * La web no conoce ni crea figuras directamente, solo indica cuál usar.
 */
class CreadorFiguras {
public:
    // Singleton para acceso global
    static CreadorFiguras& obtenerInstancia();
    
    // Crear una figura por su identificador
    std::unique_ptr<FiguraBase> crearFigura(
        const std::string& idFigura,
        int cantidadDrones,
        float anchoCanvas,
        float altoCanvas
    );
    
    // Obtener lista de figuras disponibles
    std::vector<std::string> obtenerFigurasDisponibles() const;
    
    // Verificar si existe una figura
    bool existeFigura(const std::string& idFigura) const;

private:
    // Constructor privado (singleton)
    CreadorFiguras();
    
    // Mapa de creadores de figuras
    using CreadorFunc = std::function<std::unique_ptr<FiguraBase>(int, float, float)>;
    std::map<std::string, CreadorFunc> creadores;
    
    // Registrar todas las figuras disponibles
    void registrarFiguras();
    
    // Template para registrar una figura
    template<typename T>
    void registrar(const std::string& id) {
        creadores[id] = [](int cantidad, float ancho, float alto) {
            return std::make_unique<T>(cantidad, ancho, alto);
        };
    }
};

#endif // CREADOR_FIGURAS_H
