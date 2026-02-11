#include "../core/figura_base.h"
#include <cmath>

/**
 * Figura: Estrellas
 * Categoría: Símbolos
 * 
 * Constelación de estrellas de 5 puntas con puntas afiladas
 */
class Estrellas : public FiguraBase {
public:
    Estrellas(int cantidadDrones, float anchoCanvas, float altoCanvas)
        : FiguraBase("ESTRELLAS", "Estrellas", "simbolos",
                     cantidadDrones, anchoCanvas, altoCanvas) {}
    
    std::vector<PosicionDrone> generarPosiciones() override {
        std::vector<PosicionDrone> posiciones;
        
        // Estrella central grande
        agregarEstrella(posiciones, centroX(), centroY(), 80, COLOR_DORADO);
        
        // Estrellas secundarias
        agregarEstrella(posiciones, centroX() - 180, centroY() - 80, 50, COLOR_CELESTE);
        agregarEstrella(posiciones, centroX() + 180, centroY() - 80, 50, COLOR_CELESTE);
        agregarEstrella(posiciones, centroX() - 150, centroY() + 100, 45, COLOR_MAGENTA);
        agregarEstrella(posiciones, centroX() + 150, centroY() + 100, 45, COLOR_MAGENTA);
        
        // Estrellas pequeñas decorativas
        agregarEstrella(posiciones, centroX() - 250, centroY(), 30, COLOR_BLANCO);
        agregarEstrella(posiciones, centroX() + 250, centroY(), 30, COLOR_BLANCO);
        agregarEstrella(posiciones, centroX(), centroY() - 150, 35, COLOR_AMARILLO);
        agregarEstrella(posiciones, centroX(), centroY() + 150, 35, COLOR_AMARILLO);
        
        // Estrellas diminutas de fondo
        agregarEstrellasDecoFondo(posiciones);
        
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
    void agregarEstrella(std::vector<PosicionDrone>& pos, float cx, float cy, 
                         float radio, const std::string& color) {
        // Estrella de 5 puntas con puntas afiladas
        int numPuntas = 5;
        float radioInterno = radio * 0.4f;
        
        // Calcular vértices de la estrella
        std::vector<std::pair<float, float>> vertices;
        for (int i = 0; i < numPuntas * 2; ++i) {
            float angulo = (M_PI / 2) + (M_PI * i) / numPuntas; // Empezar desde arriba
            float r = (i % 2 == 0) ? radio : radioInterno;
            float x = cx + r * std::cos(angulo);
            float y = cy - r * std::sin(angulo); // Invertir Y para que apunte arriba
            vertices.push_back({x, y});
        }
        
        // Dibujar líneas entre vértices
        for (int i = 0; i < numPuntas * 2; ++i) {
            int siguiente = (i + 1) % (numPuntas * 2);
            
            float x1 = vertices[i].first;
            float y1 = vertices[i].second;
            float x2 = vertices[siguiente].first;
            float y2 = vertices[siguiente].second;
            
            // Interpolar puntos entre vértices
            float dx = x2 - x1;
            float dy = y2 - y1;
            float longitud = std::sqrt(dx * dx + dy * dy);
            int pasos = static_cast<int>(longitud / 3.0f);
            
            for (int j = 0; j <= pasos; ++j) {
                float t = static_cast<float>(j) / pasos;
                float x = x1 + dx * t;
                float y = y1 + dy * t;
                pos.emplace_back(x, y, color);
            }
        }
        
        // Rellenar el centro de la estrella
        float radioRelleno = radioInterno * 0.8f;
        for (float ry = -radioRelleno; ry <= radioRelleno; ry += 4) {
            for (float rx = -radioRelleno; rx <= radioRelleno; rx += 4) {
                if (rx * rx + ry * ry <= radioRelleno * radioRelleno) {
                    pos.emplace_back(cx + rx, cy + ry, color);
                }
            }
        }
        
        // Centro brillante
        auto centro = crearCirculo(cx, cy, 5, 8, COLOR_BLANCO);
        pos.insert(pos.end(), centro.begin(), centro.end());
    }
    
    void agregarEstrellasDecoFondo(std::vector<PosicionDrone>& pos) {
        // Posiciones predefinidas para estrellas pequeñas de fondo
        std::vector<std::tuple<float, float, float>> estrellasFondo = {
            {centroX() - 300, centroY() - 120, 15},
            {centroX() + 300, centroY() - 120, 15},
            {centroX() - 280, centroY() + 80, 12},
            {centroX() + 280, centroY() + 80, 12},
            {centroX() - 100, centroY() - 180, 18},
            {centroX() + 100, centroY() - 180, 18},
            {centroX() - 320, centroY() - 50, 10},
            {centroX() + 320, centroY() - 50, 10},
            {centroX() - 200, centroY() + 160, 14},
            {centroX() + 200, centroY() + 160, 14},
        };
        
        for (const auto& estrella : estrellasFondo) {
            float ex = std::get<0>(estrella);
            float ey = std::get<1>(estrella);
            float eRadio = std::get<2>(estrella);
            
            agregarEstrellaPequena(pos, ex, ey, eRadio, COLOR_BLANCO);
        }
    }
    
    void agregarEstrellaPequena(std::vector<PosicionDrone>& pos, float cx, float cy,
                                 float radio, const std::string& color) {
        // Estrella simple de 4 puntas para decoración
        int numPuntas = 4;
        float radioInterno = radio * 0.3f;
        
        for (int i = 0; i < numPuntas * 2; ++i) {
            float angulo = (M_PI / 4) + (M_PI * i) / numPuntas;
            float r = (i % 2 == 0) ? radio : radioInterno;
            float x = cx + r * std::cos(angulo);
            float y = cy + r * std::sin(angulo);
            pos.emplace_back(x, y, color);
        }
        
        // Centro
        pos.emplace_back(cx, cy, color);
    }
};
