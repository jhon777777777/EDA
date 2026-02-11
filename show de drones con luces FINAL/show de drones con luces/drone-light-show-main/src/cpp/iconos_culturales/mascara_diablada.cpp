#include "../core/figura_base.h"
#include <cmath>

/**
 * Figura: Máscara de Diablada
 * Categoría: Iconos Culturales
 * 
 * Representación estilizada de la máscara tradicional
 * de la danza Diablada de Puno
 */
class MascaraDiablada : public FiguraBase {
public:
    MascaraDiablada(int cantidadDrones, float anchoCanvas, float altoCanvas)
        : FiguraBase("DIABLADA", "Máscara Diablada", "iconos_culturales",
                     cantidadDrones, anchoCanvas, altoCanvas) {}
    
    std::vector<PosicionDrone> generarPosiciones() override {
        std::vector<PosicionDrone> posiciones;
        
        float cx = centroX();
        float cy = centroY();
        
        // Contorno de la máscara (forma ovalada)
        agregarContornoMascara(posiciones, cx, cy);
        
        // Cuernos (elemento distintivo de la Diablada)
        agregarCuernos(posiciones, cx, cy);
        
        // Ojos estilizados
        agregarOjos(posiciones, cx, cy);
        
        // Nariz decorativa
        agregarNariz(posiciones, cx, cy);
        
        // Boca con colmillos
        agregarBoca(posiciones, cx, cy);
        
        // Decoraciones faciales
        agregarDecoraciones(posiciones, cx, cy);
        
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
    void agregarContornoMascara(std::vector<PosicionDrone>& pos, float cx, float cy) {
        // Óvalo principal de la máscara
        float radioX = 100.0f;
        float radioY = 130.0f;
        int puntos = 80;
        
        for (int i = 0; i < puntos; ++i) {
            float angulo = (2.0f * M_PI * i) / puntos;
            float x = cx + radioX * std::cos(angulo);
            float y = cy + radioY * std::sin(angulo);
            pos.emplace_back(x, y, COLOR_ROJO);
        }
        
        // Segundo contorno interior
        for (int i = 0; i < puntos / 2; ++i) {
            float angulo = (2.0f * M_PI * i) / (puntos / 2);
            float x = cx + (radioX - 15) * std::cos(angulo);
            float y = cy + (radioY - 15) * std::sin(angulo);
            pos.emplace_back(x, y, COLOR_NARANJA);
        }
    }
    
    void agregarCuernos(std::vector<PosicionDrone>& pos, float cx, float cy) {
        // Cuerno izquierdo
        float baseIzqX = cx - 70;
        float baseIzqY = cy - 100;
        
        for (int i = 0; i < 25; ++i) {
            float t = static_cast<float>(i) / 24.0f;
            // Curva del cuerno izquierdo hacia arriba y afuera
            float x = baseIzqX - 40 * t - 20 * std::sin(t * M_PI);
            float y = baseIzqY - 80 * t;
            pos.emplace_back(x, y, COLOR_DORADO);
        }
        
        // Punta del cuerno izquierdo
        for (int i = 0; i < 8; ++i) {
            float angulo = (2.0f * M_PI * i) / 8;
            pos.emplace_back(baseIzqX - 60, baseIzqY - 80 + 5 * std::cos(angulo), COLOR_AMARILLO);
        }
        
        // Cuerno derecho (simétrico)
        float baseDerX = cx + 70;
        float baseDerY = cy - 100;
        
        for (int i = 0; i < 25; ++i) {
            float t = static_cast<float>(i) / 24.0f;
            float x = baseDerX + 40 * t + 20 * std::sin(t * M_PI);
            float y = baseDerY - 80 * t;
            pos.emplace_back(x, y, COLOR_DORADO);
        }
        
        // Punta del cuerno derecho
        for (int i = 0; i < 8; ++i) {
            float angulo = (2.0f * M_PI * i) / 8;
            pos.emplace_back(baseDerX + 60, baseDerY - 80 + 5 * std::cos(angulo), COLOR_AMARILLO);
        }
    }
    
    void agregarOjos(std::vector<PosicionDrone>& pos, float cx, float cy) {
        // Ojo izquierdo - forma almendrada
        float ojoIzqX = cx - 40;
        float ojoY = cy - 30;
        
        // Contorno del ojo
        for (int i = 0; i < 20; ++i) {
            float angulo = (2.0f * M_PI * i) / 20;
            float x = ojoIzqX + 25 * std::cos(angulo);
            float y = ojoY + 15 * std::sin(angulo);
            pos.emplace_back(x, y, COLOR_BLANCO);
        }
        
        // Pupila
        auto pupilaIzq = crearCirculo(ojoIzqX, ojoY, 8, 12, COLOR_ROJO);
        pos.insert(pos.end(), pupilaIzq.begin(), pupilaIzq.end());
        
        // Ojo derecho
        float ojoDerX = cx + 40;
        
        for (int i = 0; i < 20; ++i) {
            float angulo = (2.0f * M_PI * i) / 20;
            float x = ojoDerX + 25 * std::cos(angulo);
            float y = ojoY + 15 * std::sin(angulo);
            pos.emplace_back(x, y, COLOR_BLANCO);
        }
        
        auto pupilaDer = crearCirculo(ojoDerX, ojoY, 8, 12, COLOR_ROJO);
        pos.insert(pos.end(), pupilaDer.begin(), pupilaDer.end());
        
        // Cejas decorativas
        auto cejaIzq = crearArco(ojoIzqX, ojoY - 20, 30, -M_PI * 0.8f, -M_PI * 0.2f, 15, COLOR_DORADO);
        pos.insert(pos.end(), cejaIzq.begin(), cejaIzq.end());
        
        auto cejaDer = crearArco(ojoDerX, ojoY - 20, 30, -M_PI * 0.8f, -M_PI * 0.2f, 15, COLOR_DORADO);
        pos.insert(pos.end(), cejaDer.begin(), cejaDer.end());
    }
    
    void agregarNariz(std::vector<PosicionDrone>& pos, float cx, float cy) {
        // Nariz estilizada triangular
        float narizY = cy + 10;
        
        auto lado1 = crearBarraDiagonal(cx - 15, narizY - 20, cx, narizY + 20, 6, COLOR_NARANJA);
        pos.insert(pos.end(), lado1.begin(), lado1.end());
        
        auto lado2 = crearBarraDiagonal(cx + 15, narizY - 20, cx, narizY + 20, 6, COLOR_NARANJA);
        pos.insert(pos.end(), lado2.begin(), lado2.end());
        
        // Fosas nasales
        pos.emplace_back(cx - 8, narizY + 15, COLOR_ROJO);
        pos.emplace_back(cx + 8, narizY + 15, COLOR_ROJO);
    }
    
    void agregarBoca(std::vector<PosicionDrone>& pos, float cx, float cy) {
        float bocaY = cy + 60;
        
        // Labios
        auto labioSup = crearArco(cx, bocaY - 10, 50, 0, M_PI, 20, COLOR_ROJO);
        pos.insert(pos.end(), labioSup.begin(), labioSup.end());
        
        auto labioInf = crearArco(cx, bocaY + 10, 45, M_PI, 2 * M_PI, 20, COLOR_ROJO);
        pos.insert(pos.end(), labioInf.begin(), labioInf.end());
        
        // Colmillos
        for (int i = 0; i < 3; ++i) {
            float colmilloX = cx - 30 + i * 30;
            auto colmillo = crearBarraVertical(colmilloX, bocaY, bocaY + 20, 5, COLOR_BLANCO);
            pos.insert(pos.end(), colmillo.begin(), colmillo.end());
        }
    }
    
    void agregarDecoraciones(std::vector<PosicionDrone>& pos, float cx, float cy) {
        // Decoraciones laterales (mejillas)
        for (int lado = -1; lado <= 1; lado += 2) {
            float decorX = cx + lado * 80;
            float decorY = cy + 20;
            
            // Espirales decorativas
            for (int i = 0; i < 15; ++i) {
                float t = static_cast<float>(i) / 14.0f;
                float radio = 10 + t * 15;
                float angulo = t * 3 * M_PI;
                float x = decorX + radio * std::cos(angulo) * 0.5f;
                float y = decorY + radio * std::sin(angulo) * 0.5f;
                pos.emplace_back(x, y, COLOR_DORADO);
            }
        }
        
        // Corona decorativa en la frente
        float coronaY = cy - 70;
        for (int i = 0; i < 7; ++i) {
            float x = cx - 60 + i * 20;
            float y = coronaY + (i % 2 == 0 ? 0 : -10);
            pos.emplace_back(x, y, COLOR_DORADO);
        }
    }
};
