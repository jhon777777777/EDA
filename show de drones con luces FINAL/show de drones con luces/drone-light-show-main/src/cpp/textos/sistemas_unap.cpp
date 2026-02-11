#include "../core/figura_base.h"

/**
 * Figura: SISTEMAS UNAP
 * Categoría: Textos
 * 
 * Representa la carrera de Ingeniería de Sistemas de la UNAP
 */
class SistemasUnap : public FiguraBase {
public:
    SistemasUnap(int cantidadDrones, float anchoCanvas, float altoCanvas)
        : FiguraBase("SISTEMAS_UNAP", "Sistemas UNAP", "textos",
                     cantidadDrones, anchoCanvas, altoCanvas) {}
    
    std::vector<PosicionDrone> generarPosiciones() override {
        std::vector<PosicionDrone> posiciones;
        
        float grosor = 10.0f;
        float alturaLetra = 50.0f;
        float anchoLetra = 35.0f;
        float espacioLetra = 8.0f;
        
        // Línea 1: "SISTEMAS"
        float y1 = centroY() - 45;
        std::string texto1 = "SISTEMAS";
        float anchoTotal1 = texto1.length() * (anchoLetra + espacioLetra);
        float xInicio1 = centroX() - anchoTotal1 / 2;
        
        for (char c : texto1) {
            agregarLetra(posiciones, c, xInicio1, y1, grosor, alturaLetra, anchoLetra, COLOR_CELESTE);
            xInicio1 += anchoLetra + espacioLetra;
        }
        
        // Línea 2: "UNAP"
        float y2 = centroY() + 45;
        std::string texto2 = "UNAP";
        float anchoTotal2 = texto2.length() * (anchoLetra + espacioLetra);
        float xInicio2 = centroX() - anchoTotal2 / 2;
        
        for (char c : texto2) {
            agregarLetra(posiciones, c, xInicio2, y2, grosor, alturaLetra, anchoLetra, COLOR_DORADO);
            xInicio2 += anchoLetra + espacioLetra;
        }
        
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
    void agregarLetra(std::vector<PosicionDrone>& pos, char letra, float x, float y,
                      float grosor, float altura, float ancho, const std::string& color) {
        switch (letra) {
            case 'S': agregarS(pos, x, y, grosor, altura, ancho, color); break;
            case 'I': agregarI(pos, x, y, grosor, altura, ancho, color); break;
            case 'T': agregarT(pos, x, y, grosor, altura, ancho, color); break;
            case 'E': agregarE(pos, x, y, grosor, altura, ancho, color); break;
            case 'M': agregarM(pos, x, y, grosor, altura, ancho, color); break;
            case 'A': agregarA(pos, x, y, grosor, altura, ancho, color); break;
            case 'U': agregarU(pos, x, y, grosor, altura, ancho, color); break;
            case 'N': agregarN(pos, x, y, grosor, altura, ancho, color); break;
            case 'P': agregarP(pos, x, y, grosor, altura, ancho, color); break;
        }
    }
    
    void agregarS(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, color);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto mid = crearBarraHorizontal(x, x + ancho, y, grosor, color);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), bot.begin(), bot.end());
        
        auto izqSup = crearBarraVertical(x, y - altura/2, y, grosor, color);
        pos.insert(pos.end(), izqSup.begin(), izqSup.end());
        
        auto derInf = crearBarraVertical(x + ancho, y, y + altura/2, grosor, color);
        pos.insert(pos.end(), derInf.begin(), derInf.end());
    }
    
    void agregarI(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, color);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), bot.begin(), bot.end());
        
        auto vert = crearBarraVertical(x + ancho/2, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), vert.begin(), vert.end());
    }
    
    void agregarT(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, color);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto vert = crearBarraVertical(x + ancho/2, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), vert.begin(), vert.end());
    }
    
    void agregarE(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, color);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto mid = crearBarraHorizontal(x, x + ancho * 0.7f, y, grosor, color);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarM(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraVertical(x + ancho, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto diagIzq = crearBarraDiagonal(x, y - altura/2, x + ancho/2, y, grosor, color);
        pos.insert(pos.end(), diagIzq.begin(), diagIzq.end());
        
        auto diagDer = crearBarraDiagonal(x + ancho/2, y, x + ancho, y - altura/2, grosor, color);
        pos.insert(pos.end(), diagDer.begin(), diagDer.end());
    }
    
    void agregarA(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraDiagonal(x, y + altura/2, x + ancho/2, y - altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraDiagonal(x + ancho/2, y - altura/2, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto mid = crearBarraHorizontal(x + ancho * 0.15f, x + ancho * 0.85f, y + altura * 0.1f, grosor, color);
        pos.insert(pos.end(), mid.begin(), mid.end());
    }
    
    void agregarU(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraVertical(x + ancho, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarN(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraVertical(x + ancho, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto diag = crearBarraDiagonal(x, y - altura/2, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), diag.begin(), diag.end());
    }
    
    void agregarP(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto top = crearBarraHorizontal(x, x + ancho * 0.7f, y - altura/2, grosor, color);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto mid = crearBarraHorizontal(x, x + ancho * 0.7f, y, grosor, color);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        auto der = crearBarraVertical(x + ancho * 0.7f, y - altura/2, y, grosor, color);
        pos.insert(pos.end(), der.begin(), der.end());
    }
};
