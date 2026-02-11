// Panel de código C++ - Simulador de Drones Candelaria 2026
import React, { useState } from 'react';
import { Code, Download, FileCode, ChevronDown, ChevronRight, Copy, Check } from 'lucide-react';

interface ArchivosCpp {
  nombre: string;
  contenido: string;
  descripcion: string;
}

const archivosCpp: ArchivosCpp[] = [
  {
    nombre: 'Dron.h',
    descripcion: 'Clase principal del dron con posición y color',
    contenido: `#ifndef DRON_H
#define DRON_H

#include <SFML/Graphics.hpp>
#include <cmath>

// Clase que representa un dron individual en el enjambre
class Dron {
private:
    int id;
    sf::Vector2f posicion;
    sf::Vector2f posicionObjetivo;
    sf::Color color;
    sf::Color colorObjetivo;
    float tamano;
    
public:
    // Constructor
    Dron(int id, float x, float y, sf::Color color = sf::Color::White);
    
    // Obtener propiedades
    int obtenerId() const { return id; }
    sf::Vector2f obtenerPosicion() const { return posicion; }
    sf::Vector2f obtenerPosicionObjetivo() const { return posicionObjetivo; }
    sf::Color obtenerColor() const { return color; }
    float obtenerTamano() const { return tamano; }
    
    // Establecer objetivo
    void establecerObjetivo(float x, float y);
    void establecerColorObjetivo(sf::Color nuevoColor);
    
    // Actualizar posición con interpolación
    void actualizar(float deltaTiempo, float velocidad = 0.05f);
    bool llegoAlObjetivo(float umbral = 1.0f) const;
    
    // Dibujar en la ventana
    void dibujar(sf::RenderWindow& ventana) const;
    
    // Calcular distancia a otro dron
    float distanciaA(const Dron& otro) const;
    
private:
    // Interpolación de color
    sf::Color interpolarColor(sf::Color desde, sf::Color hasta, float t) const;
};

#endif // DRON_H`,
  },
  {
    nombre: 'Dron.cpp',
    descripcion: 'Implementación de la clase Dron',
    contenido: `#include "Dron.h"

Dron::Dron(int id, float x, float y, sf::Color color)
    : id(id), posicion(x, y), posicionObjetivo(x, y), 
      color(color), colorObjetivo(color), tamano(3.0f) {}

void Dron::establecerObjetivo(float x, float y) {
    posicionObjetivo = sf::Vector2f(x, y);
}

void Dron::establecerColorObjetivo(sf::Color nuevoColor) {
    colorObjetivo = nuevoColor;
}

void Dron::actualizar(float deltaTiempo, float velocidad) {
    // Interpolación lineal para posición
    posicion.x += (posicionObjetivo.x - posicion.x) * velocidad;
    posicion.y += (posicionObjetivo.y - posicion.y) * velocidad;
    
    // Interpolación de color
    color = interpolarColor(color, colorObjetivo, velocidad);
}

bool Dron::llegoAlObjetivo(float umbral) const {
    float dx = posicionObjetivo.x - posicion.x;
    float dy = posicionObjetivo.y - posicion.y;
    return std::sqrt(dx*dx + dy*dy) < umbral;
}

void Dron::dibujar(sf::RenderWindow& ventana) const {
    // Efecto de brillo (círculo exterior)
    sf::CircleShape brillo(tamano * 4);
    brillo.setPosition(posicion.x - tamano * 4, posicion.y - tamano * 4);
    brillo.setFillColor(sf::Color(color.r, color.g, color.b, 50));
    ventana.draw(brillo);
    
    // Núcleo del dron (centro brillante)
    sf::CircleShape nucleo(tamano);
    nucleo.setPosition(posicion.x - tamano, posicion.y - tamano);
    nucleo.setFillColor(sf::Color::White);
    ventana.draw(nucleo);
    
    // Anillo de color
    sf::CircleShape anillo(tamano * 1.5f);
    anillo.setPosition(posicion.x - tamano * 1.5f, posicion.y - tamano * 1.5f);
    anillo.setFillColor(sf::Color::Transparent);
    anillo.setOutlineColor(color);
    anillo.setOutlineThickness(1.0f);
    ventana.draw(anillo);
}

float Dron::distanciaA(const Dron& otro) const {
    float dx = otro.posicion.x - posicion.x;
    float dy = otro.posicion.y - posicion.y;
    return std::sqrt(dx*dx + dy*dy);
}

sf::Color Dron::interpolarColor(sf::Color desde, sf::Color hasta, float t) const {
    return sf::Color(
        static_cast<sf::Uint8>(desde.r + (hasta.r - desde.r) * t),
        static_cast<sf::Uint8>(desde.g + (hasta.g - desde.g) * t),
        static_cast<sf::Uint8>(desde.b + (hasta.b - desde.b) * t),
        static_cast<sf::Uint8>(desde.a + (hasta.a - desde.a) * t)
    );
}`,
  },
  {
    nombre: 'GrafoProximidad.h',
    descripcion: 'Grafo de proximidad para conexiones entre drones',
    contenido: `#ifndef GRAFO_PROXIMIDAD_H
#define GRAFO_PROXIMIDAD_H

#include <vector>
#include <unordered_map>
#include <string>
#include "Dron.h"

// Estructura que representa una arista del grafo
struct Arista {
    int desde;
    int hasta;
    float distancia;
};

// Grafo de proximidad usando hash espacial para optimización
class GrafoProximidad {
private:
    float umbralProximidad;
    std::vector<Arista> aristas;
    std::unordered_map<std::string, std::vector<int>> cuadriculaEspacial;
    float tamanoCelda;
    
    // Obtener clave de celda para coordenadas
    std::string obtenerClaveCelda(float x, float y) const;
    
public:
    // Constructor con umbral de proximidad
    GrafoProximidad(float umbral = 60.0f);
    
    // Construir grafo desde posiciones de drones
    void construir(const std::vector<Dron>& drones);
    
    // Obtener todas las aristas
    const std::vector<Arista>& obtenerAristas() const { return aristas; }
    
    // Obtener cantidad de aristas
    size_t obtenerCantidadAristas() const { return aristas.size(); }
    
    // Dibujar aristas
    void dibujar(sf::RenderWindow& ventana, const std::vector<Dron>& drones) const;
    
    // Encontrar vecinos de un dron
    std::vector<int> encontrarVecinos(int idDron, const std::vector<Dron>& drones) const;
};

#endif // GRAFO_PROXIMIDAD_H`,
  },
  {
    nombre: 'GrafoProximidad.cpp',
    descripcion: 'Implementación del grafo con hash espacial',
    contenido: `#include "GrafoProximidad.h"
#include <cmath>

GrafoProximidad::GrafoProximidad(float umbral)
    : umbralProximidad(umbral), tamanoCelda(umbral) {}

std::string GrafoProximidad::obtenerClaveCelda(float x, float y) const {
    int celdaX = static_cast<int>(x / tamanoCelda);
    int celdaY = static_cast<int>(y / tamanoCelda);
    return std::to_string(celdaX) + "," + std::to_string(celdaY);
}

void GrafoProximidad::construir(const std::vector<Dron>& drones) {
    aristas.clear();
    cuadriculaEspacial.clear();
    
    // Colocar drones en cuadrícula espacial
    for (size_t i = 0; i < drones.size(); ++i) {
        sf::Vector2f pos = drones[i].obtenerPosicion();
        std::string clave = obtenerClaveCelda(pos.x, pos.y);
        cuadriculaEspacial[clave].push_back(static_cast<int>(i));
    }
    
    // Verificar cada dron contra vecinos en celdas adyacentes
    for (size_t i = 0; i < drones.size(); ++i) {
        sf::Vector2f pos = drones[i].obtenerPosicion();
        int celdaX = static_cast<int>(pos.x / tamanoCelda);
        int celdaY = static_cast<int>(pos.y / tamanoCelda);
        
        // Verificar vecindario 3x3
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                std::string clave = std::to_string(celdaX + dx) + "," + 
                                  std::to_string(celdaY + dy);
                
                auto it = cuadriculaEspacial.find(clave);
                if (it != cuadriculaEspacial.end()) {
                    for (int j : it->second) {
                        if (static_cast<int>(i) < j) {
                            float dist = drones[i].distanciaA(drones[j]);
                            if (dist <= umbralProximidad && dist > 0) {
                                aristas.push_back({
                                    static_cast<int>(i), 
                                    j, 
                                    dist
                                });
                            }
                        }
                    }
                }
            }
        }
    }
}

void GrafoProximidad::dibujar(sf::RenderWindow& ventana, 
                              const std::vector<Dron>& drones) const {
    for (const Arista& arista : aristas) {
        sf::Vector2f desde = drones[arista.desde].obtenerPosicion();
        sf::Vector2f hasta = drones[arista.hasta].obtenerPosicion();
        
        float opacidad = std::max(0.05f, 1.0f - arista.distancia / umbralProximidad);
        sf::Uint8 alfa = static_cast<sf::Uint8>(opacidad * 76);
        
        sf::Vertex linea[] = {
            sf::Vertex(desde, sf::Color(100, 200, 255, alfa)),
            sf::Vertex(hasta, sf::Color(100, 200, 255, alfa))
        };
        ventana.draw(linea, 2, sf::Lines);
    }
}

std::vector<int> GrafoProximidad::encontrarVecinos(int idDron, 
    const std::vector<Dron>& drones) const {
    std::vector<int> vecinos;
    
    for (const Arista& arista : aristas) {
        if (arista.desde == idDron) {
            vecinos.push_back(arista.hasta);
        } else if (arista.hasta == idDron) {
            vecinos.push_back(arista.desde);
        }
    }
    
    return vecinos;
}`,
  },
  {
    nombre: 'GestorEnjambre.h',
    descripcion: 'Gestor del enjambre de drones',
    contenido: `#ifndef GESTOR_ENJAMBRE_H
#define GESTOR_ENJAMBRE_H

#include <vector>
#include <string>
#include "Dron.h"
#include "GrafoProximidad.h"

// Gestor principal del enjambre de drones
class GestorEnjambre {
private:
    std::vector<Dron> drones;
    GrafoProximidad grafo;
    int cantidadDrones;
    float anchoCanvas;
    float altoCanvas;
    bool enTransicion;
    
public:
    // Constructor
    GestorEnjambre(int cantidad = 500, float ancho = 1200, float alto = 700);
    
    // Inicializar con posiciones aleatorias
    void inicializar();
    
    // Establecer formación
    void establecerFormacion(const std::string& tipoFormacion);
    
    // Actualizar todos los drones
    void actualizar(float deltaTiempo);
    
    // Dibujar todos los drones y grafo
    void dibujar(sf::RenderWindow& ventana, bool mostrarGrafo = true);
    
    // Obtener información
    int obtenerCantidadDrones() const { return cantidadDrones; }
    int obtenerCantidadAristas() const { return grafo.obtenerCantidadAristas(); }
    bool estaEnTransicion() const { return enTransicion; }
    const std::vector<Dron>& obtenerDrones() const { return drones; }
    
    // Verificar si todos llegaron al objetivo
    bool todosLlegaronAlObjetivo() const;
};

#endif // GESTOR_ENJAMBRE_H`,
  },
  {
    nombre: 'Principal.cpp',
    descripcion: 'Punto de entrada con menú interactivo SFML',
    contenido: `#include <SFML/Graphics.hpp>
#include <iostream>
#include "GestorEnjambre.h"

int main() {
    // Crear ventana
    sf::RenderWindow ventana(sf::VideoMode(1400, 800), 
                             "Candelaria 2026 - Simulador de Espectáculo de Drones");
    ventana.setFramerateLimit(60);
    
    // Inicializar enjambre
    GestorEnjambre enjambre(500, 1200, 700);
    enjambre.inicializar();
    
    // Opciones del menú
    std::vector<std::string> formaciones = {
        "PUNO_SE_RESPETA",
        "SISTEMAS_UNAP", 
        "EPIS",
        "DIABLADA",
        "VIRGEN",
        "ESTRELLAS",
        "TORRE_EIFFEL",
        "2026"
    };
    
    int indiceSeleccionado = 0;
    bool mostrarGrafo = true;
    
    // Cargar fuente
    sf::Font fuente;
    if (!fuente.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente!" << std::endl;
    }
    
    sf::Clock reloj;
    
    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
            
            if (evento.type == sf::Event::KeyPressed) {
                switch (evento.key.code) {
                    case sf::Keyboard::Up:
                        indiceSeleccionado = (indiceSeleccionado - 1 + formaciones.size()) 
                                            % formaciones.size();
                        break;
                    case sf::Keyboard::Down:
                        indiceSeleccionado = (indiceSeleccionado + 1) % formaciones.size();
                        break;
                    case sf::Keyboard::Enter:
                        enjambre.establecerFormacion(formaciones[indiceSeleccionado]);
                        break;
                    case sf::Keyboard::G:
                        mostrarGrafo = !mostrarGrafo;
                        break;
                    case sf::Keyboard::Escape:
                        ventana.close();
                        break;
                    default:
                        break;
                }
            }
            
            // Teclas numéricas 1-8 para selección rápida
            if (evento.type == sf::Event::KeyPressed) {
                int num = static_cast<int>(evento.key.code) - 
                          static_cast<int>(sf::Keyboard::Num1);
                if (num >= 0 && num < static_cast<int>(formaciones.size())) {
                    indiceSeleccionado = num;
                    enjambre.establecerFormacion(formaciones[indiceSeleccionado]);
                }
            }
        }
        
        // Actualizar
        float deltaTiempo = reloj.restart().asSeconds();
        enjambre.actualizar(deltaTiempo);
        
        // Limpiar y dibujar
        ventana.clear(sf::Color(5, 10, 20));
        enjambre.dibujar(ventana, mostrarGrafo);
        
        // Dibujar menú
        float menuX = 1210;
        for (size_t i = 0; i < formaciones.size(); ++i) {
            sf::Text texto;
            texto.setFont(fuente);
            texto.setString(std::to_string(i + 1) + ". " + formaciones[i]);
            texto.setCharacterSize(14);
            texto.setPosition(menuX, 20 + i * 25);
            
            if (static_cast<int>(i) == indiceSeleccionado) {
                texto.setFillColor(sf::Color(255, 215, 0)); // Dorado
            } else {
                texto.setFillColor(sf::Color(150, 150, 150));
            }
            ventana.draw(texto);
        }
        
        // Estadísticas
        sf::Text estadisticas;
        estadisticas.setFont(fuente);
        estadisticas.setString("Drones: " + std::to_string(enjambre.obtenerCantidadDrones()) + 
                       " | Aristas: " + std::to_string(enjambre.obtenerCantidadAristas()) +
                       " | Grafo: " + (mostrarGrafo ? "SI" : "NO"));
        estadisticas.setCharacterSize(12);
        estadisticas.setPosition(menuX, 750);
        estadisticas.setFillColor(sf::Color(100, 200, 255));
        ventana.draw(estadisticas);
        
        ventana.display();
    }
    
    return 0;
}`,
  },
];

const PanelCodigoCpp: React.FC = () => {
  const [archivoExpandido, setArchivoExpandido] = useState<string | null>(null);
  const [archivoCopiado, setArchivoCopiado] = useState<string | null>(null);

  const copiarContenido = async (contenido: string, nombreArchivo: string) => {
    await navigator.clipboard.writeText(contenido);
    setArchivoCopiado(nombreArchivo);
    setTimeout(() => setArchivoCopiado(null), 2000);
  };

  const descargarTodo = () => {
    archivosCpp.forEach(archivo => {
      const blob = new Blob([archivo.contenido], { type: 'text/plain' });
      const url = URL.createObjectURL(blob);
      const a = document.createElement('a');
      a.href = url;
      a.download = archivo.nombre;
      a.click();
      URL.revokeObjectURL(url);
    });
  };

  return (
    <div className="space-y-4">
      <div className="flex items-center justify-between">
        <h3 className="font-display text-sm uppercase tracking-wider text-muted-foreground flex items-center gap-2">
          <Code className="w-4 h-4" />
          Código C++ / SFML
        </h3>
        <button
          onClick={descargarTodo}
          className="btn-glow flex items-center gap-2 px-3 py-1.5 rounded-lg text-xs font-medium bg-primary text-primary-foreground"
        >
          <Download className="w-3 h-3" />
          Descargar Todo
        </button>
      </div>
      
      <div className="space-y-2 max-h-[400px] overflow-y-auto pr-2">
        {archivosCpp.map(archivo => (
          <div key={archivo.nombre} className="rounded-lg border border-border overflow-hidden">
            <button
              onClick={() => setArchivoExpandido(archivoExpandido === archivo.nombre ? null : archivo.nombre)}
              className="w-full px-4 py-3 flex items-center justify-between bg-card/50 hover:bg-card transition-colors"
            >
              <div className="flex items-center gap-3">
                <FileCode className="w-4 h-4 text-primary" />
                <div className="text-left">
                  <div className="font-mono text-sm text-foreground">{archivo.nombre}</div>
                  <div className="text-xs text-muted-foreground">{archivo.descripcion}</div>
                </div>
              </div>
              {archivoExpandido === archivo.nombre ? (
                <ChevronDown className="w-4 h-4 text-muted-foreground" />
              ) : (
                <ChevronRight className="w-4 h-4 text-muted-foreground" />
              )}
            </button>
            
            {archivoExpandido === archivo.nombre && (
              <div className="relative">
                <button
                  onClick={() => copiarContenido(archivo.contenido, archivo.nombre)}
                  className="absolute top-2 right-2 p-2 rounded bg-muted hover:bg-muted/80 transition-colors"
                >
                  {archivoCopiado === archivo.nombre ? (
                    <Check className="w-4 h-4 text-green-400" />
                  ) : (
                    <Copy className="w-4 h-4 text-muted-foreground" />
                  )}
                </button>
                <pre className="p-4 bg-background/50 overflow-x-auto text-xs">
                  <code className="text-muted-foreground">{archivo.contenido}</code>
                </pre>
              </div>
            )}
          </div>
        ))}
      </div>
      
      <div className="p-3 rounded-lg bg-muted/30 border border-border">
        <p className="text-xs text-muted-foreground">
          <strong className="text-foreground">Compilar:</strong> g++ -std=c++17 *.cpp -o simulador_drones -lsfml-graphics -lsfml-window -lsfml-system
        </p>
      </div>
    </div>
  );
};

export default PanelCodigoCpp;
