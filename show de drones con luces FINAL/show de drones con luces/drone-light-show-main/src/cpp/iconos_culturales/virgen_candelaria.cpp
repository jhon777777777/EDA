#include "../core/figura_base.h"
#include <cmath>

/**
 * Figura: Virgen de la Candelaria
 * Categoría: Iconos Culturales
 * 
 * Silueta estilizada de la Virgen de la Candelaria,
 * patrona de Puno, Perú
 */
class VirgenCandelaria : public FiguraBase {
public:
    VirgenCandelaria(int cantidadDrones, float anchoCanvas, float altoCanvas)
        : FiguraBase("VIRGEN", "Virgen de la Candelaria", "iconos_culturales",
                     cantidadDrones, anchoCanvas, altoCanvas) {}
    
    std::vector<PosicionDrone> generarPosiciones() override {
        std::vector<PosicionDrone> posiciones;
        
        float cx = centroX();
        float cy = centroY();
        
        // Corona/Aureola
        agregarAureola(posiciones, cx, cy);
        
        // Rostro
        agregarRostro(posiciones, cx, cy);
        
        // Manto
        agregarManto(posiciones, cx, cy);
        
        // Vela (símbolo de la Candelaria)
        agregarVela(posiciones, cx, cy);
        
        // Detalles del vestido
        agregarVestido(posiciones, cx, cy);
        
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
    void agregarAureola(std::vector<PosicionDrone>& pos, float cx, float cy) {
        float aureolaY = cy - 120;
        
        // Aureola principal (círculo de rayos)
        for (int i = 0; i < 24; ++i) {
            float angulo = (2.0f * M_PI * i) / 24;
            
            // Rayos alternados largos y cortos
            float radioBase = 40;
            float radioExterno = (i % 2 == 0) ? 55 : 45;
            
            // Rayo
            for (int j = 0; j < 8; ++j) {
                float t = static_cast<float>(j) / 7.0f;
                float radio = radioBase + (radioExterno - radioBase) * t;
                float x = cx + radio * std::cos(angulo);
                float y = aureolaY + radio * std::sin(angulo);
                pos.emplace_back(x, y, COLOR_DORADO);
            }
        }
        
        // Centro de la aureola
        auto centro = crearCirculo(cx, aureolaY, 35, 30, COLOR_AMARILLO);
        pos.insert(pos.end(), centro.begin(), centro.end());
    }
    
    void agregarRostro(std::vector<PosicionDrone>& pos, float cx, float cy) {
        float rostroY = cy - 70;
        
        // Óvalo del rostro
        float radioX = 25;
        float radioY = 30;
        
        for (int i = 0; i < 40; ++i) {
            float angulo = (2.0f * M_PI * i) / 40;
            float x = cx + radioX * std::cos(angulo);
            float y = rostroY + radioY * std::sin(angulo);
            pos.emplace_back(x, y, "#FFE4C4"); // Color piel
        }
        
        // Relleno del rostro
        for (float ry = -radioY + 5; ry < radioY - 5; ry += 8) {
            float anchoEnY = radioX * std::sqrt(1 - (ry * ry) / (radioY * radioY));
            for (float rx = -anchoEnY + 5; rx < anchoEnY - 5; rx += 8) {
                pos.emplace_back(cx + rx, rostroY + ry, "#FFE4C4");
            }
        }
        
        // Ojos
        pos.emplace_back(cx - 10, rostroY - 5, "#4A4A4A");
        pos.emplace_back(cx + 10, rostroY - 5, "#4A4A4A");
        
        // Boca (sonrisa suave)
        auto sonrisa = crearArco(cx, rostroY + 12, 10, 0.2f, M_PI - 0.2f, 8, "#D4A4A4");
        pos.insert(pos.end(), sonrisa.begin(), sonrisa.end());
    }
    
    void agregarManto(std::vector<PosicionDrone>& pos, float cx, float cy) {
        float mantoY = cy - 45;
        
        // Manto que cubre la cabeza y cae a los lados
        // Parte superior del manto
        for (int i = 0; i < 30; ++i) {
            float angulo = M_PI + (M_PI * i) / 29;
            float x = cx + 50 * std::cos(angulo);
            float y = mantoY - 30 + 25 * std::sin(angulo);
            pos.emplace_back(x, y, COLOR_CELESTE);
        }
        
        // Lados del manto cayendo
        for (float dy = 0; dy < 150; dy += 6) {
            float expansion = dy * 0.4f;
            
            // Lado izquierdo
            pos.emplace_back(cx - 50 - expansion * 0.3f, mantoY + dy, COLOR_CELESTE);
            pos.emplace_back(cx - 45 - expansion * 0.3f, mantoY + dy, COLOR_CELESTE);
            
            // Lado derecho
            pos.emplace_back(cx + 50 + expansion * 0.3f, mantoY + dy, COLOR_CELESTE);
            pos.emplace_back(cx + 45 + expansion * 0.3f, mantoY + dy, COLOR_CELESTE);
        }
        
        // Borde dorado del manto
        for (float dy = 0; dy < 150; dy += 8) {
            float expansion = dy * 0.4f;
            pos.emplace_back(cx - 52 - expansion * 0.3f, mantoY + dy, COLOR_DORADO);
            pos.emplace_back(cx + 52 + expansion * 0.3f, mantoY + dy, COLOR_DORADO);
        }
    }
    
    void agregarVela(std::vector<PosicionDrone>& pos, float cx, float cy) {
        // La vela es símbolo distintivo de la Candelaria
        float velaX = cx + 60;
        float velaY = cy - 20;
        
        // Cuerpo de la vela
        auto cuerpoVela = crearBarraVertical(velaX, velaY, velaY + 60, 8, COLOR_BLANCO);
        pos.insert(pos.end(), cuerpoVela.begin(), cuerpoVela.end());
        
        // Llama de la vela
        for (int i = 0; i < 20; ++i) {
            float t = static_cast<float>(i) / 19.0f;
            float y = velaY - 5 - t * 25;
            float anchura = 8 * (1 - t * 0.7f);
            
            pos.emplace_back(velaX - anchura * 0.5f + std::sin(t * 3) * 3, y, COLOR_NARANJA);
            pos.emplace_back(velaX + anchura * 0.5f + std::sin(t * 3) * 3, y, COLOR_AMARILLO);
        }
        
        // Punta de la llama
        for (int i = 0; i < 5; ++i) {
            pos.emplace_back(velaX, velaY - 30 - i * 3, COLOR_AMARILLO);
        }
    }
    
    void agregarVestido(std::vector<PosicionDrone>& pos, float cx, float cy) {
        float vestidoY = cy - 30;
        
        // Cuerpo del vestido
        for (float dy = 0; dy < 120; dy += 5) {
            float expansion = std::min(dy * 0.5f, 60.0f);
            float anchoBase = 40 + expansion;
            
            for (float dx = -anchoBase; dx <= anchoBase; dx += 8) {
                pos.emplace_back(cx + dx, vestidoY + dy, COLOR_CELESTE);
            }
        }
        
        // Decoraciones doradas en el vestido
        for (float dy = 20; dy < 120; dy += 30) {
            float expansion = std::min(dy * 0.5f, 60.0f);
            float anchoBase = 40 + expansion;
            
            // Línea decorativa horizontal
            for (float dx = -anchoBase + 5; dx <= anchoBase - 5; dx += 10) {
                pos.emplace_back(cx + dx, vestidoY + dy, COLOR_DORADO);
            }
        }
        
        // Base del vestido
        float baseY = vestidoY + 120;
        for (float dx = -100; dx <= 100; dx += 5) {
            pos.emplace_back(cx + dx, baseY, COLOR_DORADO);
        }
    }
};
