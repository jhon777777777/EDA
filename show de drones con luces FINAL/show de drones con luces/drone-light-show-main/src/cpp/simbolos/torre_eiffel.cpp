#include "../core/figura_base.h"
#include <cmath>

/**
 * Figura: Torre Eiffel
 * Categoría: Símbolos
 * 
 * Silueta estilizada de la Torre Eiffel
 */
class TorreEiffel : public FiguraBase {
public:
    TorreEiffel(int cantidadDrones, float anchoCanvas, float altoCanvas)
        : FiguraBase("TORRE_EIFFEL", "Torre Eiffel", "simbolos",
                     cantidadDrones, anchoCanvas, altoCanvas) {}
    
    std::vector<PosicionDrone> generarPosiciones() override {
        std::vector<PosicionDrone> posiciones;
        
        float cx = centroX();
        float baseY = centroY() + 150;
        
        // Base de la torre (patas)
        agregarBase(posiciones, cx, baseY);
        
        // Primer nivel (arco)
        agregarPrimerNivel(posiciones, cx, baseY);
        
        // Segundo nivel
        agregarSegundoNivel(posiciones, cx, baseY);
        
        // Tercer nivel y cúspide
        agregarCuspide(posiciones, cx, baseY);
        
        // Detalles estructurales
        agregarDetalles(posiciones, cx, baseY);
        
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
    void agregarBase(std::vector<PosicionDrone>& pos, float cx, float baseY) {
        // Pata izquierda
        float pataIzqX = cx - 100;
        for (int i = 0; i < 40; ++i) {
            float t = static_cast<float>(i) / 39.0f;
            float x = pataIzqX + t * 40; // Se acerca al centro
            float y = baseY - t * 80;
            pos.emplace_back(x, y, COLOR_DORADO);
            pos.emplace_back(x + 5, y, COLOR_DORADO);
        }
        
        // Pata derecha
        float pataDerX = cx + 100;
        for (int i = 0; i < 40; ++i) {
            float t = static_cast<float>(i) / 39.0f;
            float x = pataDerX - t * 40;
            float y = baseY - t * 80;
            pos.emplace_back(x, y, COLOR_DORADO);
            pos.emplace_back(x - 5, y, COLOR_DORADO);
        }
        
        // Arco de la base
        auto arco = crearArco(cx, baseY - 20, 60, M_PI, 2 * M_PI, 30, COLOR_DORADO);
        pos.insert(pos.end(), arco.begin(), arco.end());
    }
    
    void agregarPrimerNivel(std::vector<PosicionDrone>& pos, float cx, float baseY) {
        float nivel1Y = baseY - 80;
        
        // Plataforma del primer nivel
        auto plataforma = crearBarraHorizontal(cx - 55, cx + 55, nivel1Y, 8, COLOR_AMARILLO);
        pos.insert(pos.end(), plataforma.begin(), plataforma.end());
        
        // Estructura convergente hacia el segundo nivel
        // Lado izquierdo
        for (int i = 0; i < 30; ++i) {
            float t = static_cast<float>(i) / 29.0f;
            float x = cx - 55 + t * 20;
            float y = nivel1Y - t * 60;
            pos.emplace_back(x, y, COLOR_DORADO);
        }
        
        // Lado derecho
        for (int i = 0; i < 30; ++i) {
            float t = static_cast<float>(i) / 29.0f;
            float x = cx + 55 - t * 20;
            float y = nivel1Y - t * 60;
            pos.emplace_back(x, y, COLOR_DORADO);
        }
    }
    
    void agregarSegundoNivel(std::vector<PosicionDrone>& pos, float cx, float baseY) {
        float nivel2Y = baseY - 140;
        
        // Plataforma del segundo nivel
        auto plataforma = crearBarraHorizontal(cx - 35, cx + 35, nivel2Y, 6, COLOR_AMARILLO);
        pos.insert(pos.end(), plataforma.begin(), plataforma.end());
        
        // Estructura hacia la cúspide
        // Lado izquierdo
        for (int i = 0; i < 35; ++i) {
            float t = static_cast<float>(i) / 34.0f;
            float x = cx - 35 + t * 30;
            float y = nivel2Y - t * 80;
            pos.emplace_back(x, y, COLOR_DORADO);
        }
        
        // Lado derecho
        for (int i = 0; i < 35; ++i) {
            float t = static_cast<float>(i) / 34.0f;
            float x = cx + 35 - t * 30;
            float y = nivel2Y - t * 80;
            pos.emplace_back(x, y, COLOR_DORADO);
        }
    }
    
    void agregarCuspide(std::vector<PosicionDrone>& pos, float cx, float baseY) {
        float nivel3Y = baseY - 220;
        
        // Plataforma pequeña
        auto plataforma = crearBarraHorizontal(cx - 8, cx + 8, nivel3Y, 4, COLOR_AMARILLO);
        pos.insert(pos.end(), plataforma.begin(), plataforma.end());
        
        // Aguja final
        for (int i = 0; i < 25; ++i) {
            float t = static_cast<float>(i) / 24.0f;
            float y = nivel3Y - t * 50;
            pos.emplace_back(cx, y, COLOR_BLANCO);
            if (i < 15) {
                pos.emplace_back(cx - 2, y, COLOR_DORADO);
                pos.emplace_back(cx + 2, y, COLOR_DORADO);
            }
        }
        
        // Luz en la punta
        auto luz = crearCirculo(cx, baseY - 270, 5, 10, COLOR_AMARILLO);
        pos.insert(pos.end(), luz.begin(), luz.end());
    }
    
    void agregarDetalles(std::vector<PosicionDrone>& pos, float cx, float baseY) {
        // Cruces estructurales entre niveles
        
        // Entre base y nivel 1
        float y1 = baseY - 40;
        for (int i = -1; i <= 1; i += 2) {
            float x1 = cx + i * 30;
            float x2 = cx + i * 50;
            
            // Cruz en X
            for (int j = 0; j < 10; ++j) {
                float t = static_cast<float>(j) / 9.0f;
                pos.emplace_back(x1 + (x2 - x1) * t, y1 - 15 + 30 * t, COLOR_CELESTE);
                pos.emplace_back(x1 + (x2 - x1) * t, y1 + 15 - 30 * t, COLOR_CELESTE);
            }
        }
        
        // Entre nivel 1 y 2
        float y2 = baseY - 110;
        for (int i = -1; i <= 1; i += 2) {
            float x1 = cx + i * 20;
            float x2 = cx + i * 40;
            
            for (int j = 0; j < 8; ++j) {
                float t = static_cast<float>(j) / 7.0f;
                pos.emplace_back(x1 + (x2 - x1) * t, y2 - 10 + 20 * t, COLOR_CELESTE);
                pos.emplace_back(x1 + (x2 - x1) * t, y2 + 10 - 20 * t, COLOR_CELESTE);
            }
        }
        
        // Luces decorativas
        std::vector<float> alturasLuces = {baseY - 60, baseY - 100, baseY - 160, baseY - 200};
        for (float alturaLuz : alturasLuces) {
            pos.emplace_back(cx, alturaLuz, COLOR_AMARILLO);
        }
    }
};
