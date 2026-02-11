#include "../core/figura_base.h"

/**
 * Figura: EPIS
 * Categoría: Textos
 * 
 * Escuela Profesional de Ingeniería de Sistemas
 */
class Epis : public FiguraBase {
public:
    Epis(int cantidadDrones, float anchoCanvas, float altoCanvas)
        : FiguraBase("EPIS", "EPIS", "textos",
                     cantidadDrones, anchoCanvas, altoCanvas) {}
    
    std::vector<PosicionDrone> generarPosiciones() override {
        std::vector<PosicionDrone> posiciones;
        
        float grosor = 16.0f;
        float alturaLetra = 120.0f;
        float anchoLetra = 70.0f;
        float espacioLetra = 25.0f;
        
        // Calcular posición inicial centrada para "EPIS"
        float anchoTotal = 4 * anchoLetra + 3 * espacioLetra;
        float xInicio = centroX() - anchoTotal / 2;
        float y = centroY();
        
        // E
        agregarE(posiciones, xInicio, y, grosor, alturaLetra, anchoLetra);
        xInicio += anchoLetra + espacioLetra;
        
        // P
        agregarP(posiciones, xInicio, y, grosor, alturaLetra, anchoLetra);
        xInicio += anchoLetra + espacioLetra;
        
        // I
        agregarI(posiciones, xInicio, y, grosor, alturaLetra, anchoLetra);
        xInicio += anchoLetra + espacioLetra;
        
        // S
        agregarS(posiciones, xInicio, y, grosor, alturaLetra, anchoLetra);
        
        // Rellenar con posiciones aleatorias si faltan
        while (static_cast<int>(posiciones.size()) < cantidadDrones) {
            auto aleatorias = generarPosicionesAleatorias(1, anchoCanvas, altoCanvas);
            posiciones.push_back(aleatorias[0]);
        }
        
        if (static_cast<int>(posiciones.size()) > cantidadDrones) {
            posiciones.resize(cantidadDrones);
        }
        
        return posiciones;
    }

private:
    void agregarE(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho) {
        // Barra vertical izquierda
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        // Barra horizontal superior
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), top.begin(), top.end());
        
        // Barra horizontal media
        auto mid = crearBarraHorizontal(x, x + ancho * 0.75f, y, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        // Barra horizontal inferior
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarP(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho) {
        // Barra vertical izquierda
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        // Barra horizontal superior
        auto top = crearBarraHorizontal(x, x + ancho * 0.8f, y - altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), top.begin(), top.end());
        
        // Barra horizontal media
        auto mid = crearBarraHorizontal(x, x + ancho * 0.8f, y - altura * 0.05f, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        // Barra vertical derecha (solo parte superior)
        auto der = crearBarraVertical(x + ancho * 0.8f, y - altura/2, y - altura * 0.05f, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), der.begin(), der.end());
    }
    
    void agregarI(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho) {
        // Barra horizontal superior
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), top.begin(), top.end());
        
        // Barra horizontal inferior
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), bot.begin(), bot.end());
        
        // Barra vertical central
        auto vert = crearBarraVertical(x + ancho/2, y - altura/2, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), vert.begin(), vert.end());
    }
    
    void agregarS(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho) {
        // Barra horizontal superior
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), top.begin(), top.end());
        
        // Barra horizontal media
        auto mid = crearBarraHorizontal(x, x + ancho, y, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        // Barra horizontal inferior
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), bot.begin(), bot.end());
        
        // Barra vertical izquierda superior
        auto izqSup = crearBarraVertical(x, y - altura/2, y, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), izqSup.begin(), izqSup.end());
        
        // Barra vertical derecha inferior
        auto derInf = crearBarraVertical(x + ancho, y, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), derInf.begin(), derInf.end());
    }
};
