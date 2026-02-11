#include "../core/figura_base.h"

/**
 * Figura: CANDELARIA 2026
 * Categoría: Textos
 * 
 * Texto conmemorativo de la festividad 2026
 */
class Candelaria2026 : public FiguraBase {
public:
    Candelaria2026(int cantidadDrones, float anchoCanvas, float altoCanvas)
        : FiguraBase("CANDELARIA_2026", "Candelaria 2026", "textos",
                     cantidadDrones, anchoCanvas, altoCanvas) {}
    
    std::vector<PosicionDrone> generarPosiciones() override {
        std::vector<PosicionDrone> posiciones;
        
        // Parámetros para "CANDELARIA"
        float grosorTexto = 8.0f;
        float alturaTexto = 35.0f;
        float anchoTexto = 25.0f;
        float espacioTexto = 6.0f;
        
        std::string texto = "CANDELARIA";
        float anchoTotalTexto = texto.length() * (anchoTexto + espacioTexto);
        float xTexto = centroX() - anchoTotalTexto / 2;
        float yTexto = centroY() - 80;
        
        for (char c : texto) {
            agregarLetra(posiciones, c, xTexto, yTexto, grosorTexto, alturaTexto, anchoTexto, COLOR_DORADO);
            xTexto += anchoTexto + espacioTexto;
        }
        
        // Parámetros para "2026" más grande
        float grosorNumero = 14.0f;
        float alturaNumero = 100.0f;
        float anchoNumero = 60.0f;
        float espacioNumero = 20.0f;
        
        float anchoTotalNumero = 4 * anchoNumero + 3 * espacioNumero;
        float xNumero = centroX() - anchoTotalNumero / 2;
        float yNumero = centroY() + 40;
        
        // 2
        agregarNumero2(posiciones, xNumero, yNumero, grosorNumero, alturaNumero, anchoNumero);
        xNumero += anchoNumero + espacioNumero;
        
        // 0
        agregarNumero0(posiciones, xNumero, yNumero, grosorNumero, alturaNumero, anchoNumero);
        xNumero += anchoNumero + espacioNumero;
        
        // 2
        agregarNumero2(posiciones, xNumero, yNumero, grosorNumero, alturaNumero, anchoNumero);
        xNumero += anchoNumero + espacioNumero;
        
        // 6
        agregarNumero6(posiciones, xNumero, yNumero, grosorNumero, alturaNumero, anchoNumero);
        
        // Agregar estrellas decorativas
        agregarEstrellasDecorativas(posiciones);
        
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
            case 'C': agregarC(pos, x, y, grosor, altura, ancho, color); break;
            case 'A': agregarA(pos, x, y, grosor, altura, ancho, color); break;
            case 'N': agregarN(pos, x, y, grosor, altura, ancho, color); break;
            case 'D': agregarD(pos, x, y, grosor, altura, ancho, color); break;
            case 'E': agregarE(pos, x, y, grosor, altura, ancho, color); break;
            case 'L': agregarL(pos, x, y, grosor, altura, ancho, color); break;
            case 'R': agregarR(pos, x, y, grosor, altura, ancho, color); break;
            case 'I': agregarI(pos, x, y, grosor, altura, ancho, color); break;
        }
    }
    
    void agregarC(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, color);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarA(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraDiagonal(x, y + altura/2, x + ancho/2, y - altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraDiagonal(x + ancho/2, y - altura/2, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto mid = crearBarraHorizontal(x + ancho * 0.2f, x + ancho * 0.8f, y + altura * 0.1f, grosor, color);
        pos.insert(pos.end(), mid.begin(), mid.end());
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
    
    void agregarD(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto top = crearBarraHorizontal(x, x + ancho * 0.7f, y - altura/2, grosor, color);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho * 0.7f, y + altura/2, grosor, color);
        pos.insert(pos.end(), bot.begin(), bot.end());
        
        auto der = crearBarraVertical(x + ancho * 0.7f, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), der.begin(), der.end());
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
    
    void agregarL(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarR(std::vector<PosicionDrone>& pos, float x, float y,
                  float grosor, float altura, float ancho, const std::string& color) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, color);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto top = crearBarraHorizontal(x, x + ancho * 0.7f, y - altura/2, grosor, color);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto mid = crearBarraHorizontal(x, x + ancho * 0.7f, y, grosor, color);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        auto derSup = crearBarraVertical(x + ancho * 0.7f, y - altura/2, y, grosor, color);
        pos.insert(pos.end(), derSup.begin(), derSup.end());
        
        auto diag = crearBarraDiagonal(x + ancho * 0.3f, y, x + ancho, y + altura/2, grosor, color);
        pos.insert(pos.end(), diag.begin(), diag.end());
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
    
    void agregarNumero2(std::vector<PosicionDrone>& pos, float x, float y,
                        float grosor, float altura, float ancho) {
        // Curva superior (aproximada con arco)
        auto curva = crearArco(x + ancho/2, y - altura/4, ancho/2, -M_PI, 0, 20, COLOR_MAGENTA);
        pos.insert(pos.end(), curva.begin(), curva.end());
        
        // Diagonal
        auto diag = crearBarraDiagonal(x + ancho, y - altura/4, x, y + altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), diag.begin(), diag.end());
        
        // Base horizontal
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarNumero0(std::vector<PosicionDrone>& pos, float x, float y,
                        float grosor, float altura, float ancho) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto der = crearBarraVertical(x + ancho, y - altura/2, y + altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), der.begin(), der.end());
        
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), bot.begin(), bot.end());
    }
    
    void agregarNumero6(std::vector<PosicionDrone>& pos, float x, float y,
                        float grosor, float altura, float ancho) {
        auto izq = crearBarraVertical(x, y - altura/2, y + altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), izq.begin(), izq.end());
        
        auto top = crearBarraHorizontal(x, x + ancho, y - altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), top.begin(), top.end());
        
        auto mid = crearBarraHorizontal(x, x + ancho, y, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), mid.begin(), mid.end());
        
        auto bot = crearBarraHorizontal(x, x + ancho, y + altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), bot.begin(), bot.end());
        
        auto derInf = crearBarraVertical(x + ancho, y, y + altura/2, grosor, COLOR_MAGENTA);
        pos.insert(pos.end(), derInf.begin(), derInf.end());
    }
    
    void agregarEstrellasDecorativas(std::vector<PosicionDrone>& pos) {
        // Estrellas en las esquinas
        float radio = 15.0f;
        std::vector<std::pair<float, float>> posicionesEstrellas = {
            {centroX() - 300, centroY() - 100},
            {centroX() + 300, centroY() - 100},
            {centroX() - 250, centroY() + 120},
            {centroX() + 250, centroY() + 120}
        };
        
        for (const auto& posEstrella : posicionesEstrellas) {
            auto estrella = crearCirculo(posEstrella.first, posEstrella.second, radio, 10, COLOR_DORADO);
            pos.insert(pos.end(), estrella.begin(), estrella.end());
        }
    }
};
