#include "creador_figuras.h"

// Incluir todas las figuras
#include "../textos/puno_se_respeta.cpp"
#include "../textos/sistemas_unap.cpp"
#include "../textos/epis.cpp"
#include "../textos/candelaria_2026.cpp"
#include "../iconos_culturales/mascara_diablada.cpp"
#include "../iconos_culturales/virgen_candelaria.cpp"
#include "../simbolos/estrellas.cpp"
#include "../simbolos/torre_eiffel.cpp"

/**
 * Implementación del patrón Factory para crear figuras
 */

CreadorFiguras& CreadorFiguras::obtenerInstancia() {
    static CreadorFiguras instancia;
    return instancia;
}

CreadorFiguras::CreadorFiguras() {
    registrarFiguras();
}

void CreadorFiguras::registrarFiguras() {
    // Textos
    registrar<PunoSeRespeta>("PUNO_SE_RESPETA");
    registrar<SistemasUnap>("SISTEMAS_UNAP");
    registrar<Epis>("EPIS");
    registrar<Candelaria2026>("CANDELARIA_2026");
    
    // Iconos culturales
    registrar<MascaraDiablada>("DIABLADA");
    registrar<VirgenCandelaria>("VIRGEN");
    
    // Símbolos
    registrar<Estrellas>("ESTRELLAS");
    registrar<TorreEiffel>("TORRE_EIFFEL");
}

std::unique_ptr<FiguraBase> CreadorFiguras::crearFigura(
    const std::string& idFigura,
    int cantidadDrones,
    float anchoCanvas,
    float altoCanvas
) {
    auto it = creadores.find(idFigura);
    if (it != creadores.end()) {
        return it->second(cantidadDrones, anchoCanvas, altoCanvas);
    }
    
    // Si no existe, crear posiciones aleatorias
    // Esto no debería pasar en producción
    return nullptr;
}

std::vector<std::string> CreadorFiguras::obtenerFigurasDisponibles() const {
    std::vector<std::string> figuras;
    figuras.reserve(creadores.size());
    
    for (const auto& par : creadores) {
        figuras.push_back(par.first);
    }
    
    return figuras;
}

bool CreadorFiguras::existeFigura(const std::string& idFigura) const {
    return creadores.find(idFigura) != creadores.end();
}
