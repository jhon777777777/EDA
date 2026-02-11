#include "../core/figura_base.h"

/**
 * Figura: PUNO SE RESPETA
 * Categoría: Textos
 * 
 * Texto emblemático que representa el orgullo puneño
 */
class PunoSeRespeta : public FiguraBase {
public:
    PunoSeRespeta(int cantidadDrones, float anchoCanvas, float altoCanvas)
        : FiguraBase("PUNO_SE_RESPETA", "Puno Se Respeta", "textos",
                     cantidadDrones, anchoCanvas, altoCanvas) {}
    
    std::vector<PosicionDrone> generarPosiciones() override {
        std::vector<PosicionDrone> posiciones;
        
        float grosor = 12.0f;
        float alturaLetra = 60.0f;
        float anchoLetra = 40.0f;
        float espacioLetra = 10.0f;
        
        // Línea 1: "PUNO"
        float y1 = centroY() - 50;
        float xInicio1 = centroX() - 110;
        
        // P
        agregarLetraP(posiciones, xInicio1, y1, grosor, alturaLetra, anchoLetra);
        xInicio1 += anchoLetra + espacioLetra;
        
        // U
        agregarLetraU(posiciones, xInicio1, y1, grosor, alturaLetra, anchoLetra);
        xInicio1 += anchoLetra + espacioLetra;
        
        // N
        agregarLetraN(posiciones, xInicio1, y1, grosor, alturaLetra, anchoLetra);
        xInicio1 += anchoLetra + espacioLetra;
        
        // O
        agregarLetraO(posiciones, xInicio1, y1, grosor, alturaLetra, anchoLetra);
        
        // Línea 2: "SE RESPETA"
        float y2 = centroY() + 50;
        float xInicio2 = centroX() - 250;
        
        // S
        agregarLetraS(posiciones, xInicio2, y2, grosor, alturaLetra * 0.8f, anchoLetra * 0.8f);
        xInicio2 += anchoLetra * 0.8f + espacioLetra;
        
        // E
        agregarLetraE(posiciones, xInicio2, y2, grosor, alturaLetra * 0.8f, anchoLetra * 0.8f);
        xInicio2 += anchoLetra * 0.8f + espacioLetra * 2;
        
        // R
        agregarLetraR(posiciones, xInicio2, y2, grosor, alturaLetra * 0.8f, anchoLetra * 0.8f);
        xInicio2 += anchoLetra * 0.8f + espacioLetra;
        
        // E
        agregarLetraE(posiciones, xInicio2, y2, grosor, alturaLetra * 0.8f, anchoLetra * 0.8f);
        xInicio2 += anchoLetra * 0.8f + espacioLetra;
        
        // S
        agregarLetraS(posiciones, xInicio2, y2, grosor, alturaLetra * 0.8f, anchoLetra * 0.8f);
        xInicio2 += anchoLetra * 0.8f + espacioLetra;
        
        // P
        agregarLetraP(posiciones, xInicio2, y2, grosor, alturaLetra * 0.8f, anchoLetra * 0.8f);
        xInicio2 += anchoLetra * 0.8f + espacioLetra;
        
        // E
        agregarLetraE(posiciones, xInicio2, y2, grosor, alturaLetra * 0.8f, anchoLetra * 0.8f);
        xInicio2 += anchoLetra * 0.8f + espacioLetra;
        
        // T
        agregarLetraT(posiciones, xInicio2, y2, grosor, alturaLetra * 0.8f, anchoLetra * 0.8f);
        xInicio2 += anchoLetra * 0.8f + espacioLetra;
        
        // A
        agregarLetraA(posiciones, xInicio2, y2, grosor, alturaLetra * 0.8f, anchoLetra * 0.8f);
        
        // Rellenar con posiciones aleatorias si faltan drones
        while (static_cast<int>(posiciones.size()) < cantidadDrones) {
            auto aleatorias = generarPosicionesAleatorias(1, anchoCanvas, altoCanvas);
            posiciones.push_back(aleatorias[0]);
        }
        
        // Limitar al número exacto de drones
        if (static_cast<int>(posiciones.size()) > cantidadDrones) {
            posiciones.resize(cantidadDrones);
        }
        
        return posiciones;
    }

private:
    void agregarLetraP(std::vector<PosicionDrone>& pos, float x, float y, 
                       float grosor, float altura, float ancho) {
        auto barra = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), barra.begin(), barra.end());
        
        auto top = crearBarraHorizontal(x, x + ancho * 0.7f, y - altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto mid = crearBarraHorizontal(x, x + ancho * 0.7f, y, grosor, COLOR_DORADO);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        auto der = crearBarraVertical(x + ancho * 0.7f, y - altura/2, y, grosor, COLOR_DORADO);
        pos.insert(pos.end(), der.begin(), der.end());
    }
    
    void agregarLetraU(std::vector<PosicionDrone>& pos, float x, float y,
                       float grosor, float altura, float ancho) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraVertical(x + ancho, y - altura/2, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarLetraN(std::vector<PosicionDrone>& pos, float x, float y,
                       float grosor, float altura, float ancho) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraVertical(x + ancho, y - altura/2, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto diag = crearBarraDiagonal(x, y - altura/2, x + ancho, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), diag.begin(), diag.end());
    }
    
    void agregarLetraO(std::vector<PosicionDrone>& pos, float x, float y,
                       float grosor, float altura, float ancho) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraVertical(x + ancho, y - altura/2, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_DORADO);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarLetraS(std::vector<PosicionDrone>& pos, float x, float y,
                       float grosor, float altura, float ancho) {
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto mid = crearBarraHorizontal(x, x + ancho, y, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), bot.begin(), bot.end());
        
        auto izqSup = crearBarraVertical(x, y - altura/2, y, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), izqSup.begin(), izqSup.end());
        
        auto derInf = crearBarraVertical(x + ancho, y, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), derInf.begin(), derInf.end());
    }
    
    void agregarLetraE(std::vector<PosicionDrone>& pos, float x, float y,
                       float grosor, float altura, float ancho) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto mid = crearBarraHorizontal(x, x + ancho * 0.7f, y, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarLetraR(std::vector<PosicionDrone>& pos, float x, float y,
                       float grosor, float altura, float ancho) {
        agregarLetraP(pos, x, y, grosor, altura, ancho);
        
        auto diag = crearBarraDiagonal(x + ancho * 0.3f, y, x + ancho, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), diag.begin(), diag.end());
    }
    
    void agregarLetraT(std::vector<PosicionDrone>& pos, float x, float y,
                       float grosor, float altura, float ancho) {
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto vert = crearBarraVertical(x + ancho/2, y - altura/2, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), vert.begin(), vert.end());
    }
    
    void agregarLetraA(std::vector<PosicionDrone>& pos, float x, float y,
                       float grosor, float altura, float ancho) {
        auto izq = crearBarraDiagonal(x, y + altura/2, x + ancho/2, y - altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraDiagonal(x + ancho/2, y - altura/2, x + ancho, y + altura/2, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto mid = crearBarraHorizontal(x + ancho * 0.15f, x + ancho * 0.85f, y + altura * 0.1f, grosor, COLOR_CELESTE);
        pos.insert(pos.end(), mid.begin(), mid.end());
    }
};
