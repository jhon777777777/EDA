// ══════════════════════════════════════════════════════════════════
// INTERFAZ.H - Declaración de la Interfaz de Usuario
// ══════════════════════════════════════════════════════════════════

#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "ListaContactos.h"
#include <string>
#include <vector>

class Interfaz {
private:
    // Utilidades de formato
    std::string centrar(const std::string& texto, int ancho) const;
    std::string recortar(const std::string& texto, int maxLen) const;
    
public:
    // Pantalla
    void limpiarPantalla() const;
    void pausar() const;
    
    // Menús
    void mostrarMenuPrincipal() const;
    void mostrarEncabezado(const std::string& titulo) const;
    
    // Mensajes
    void mostrarMensaje(const std::string& mensaje) const;
    void mostrarError(const std::string& error) const;
    void mostrarExito(const std::string& exito) const;
    
    // Tablas
    void mostrarTablaContactos(const std::vector<Contacto>& contactos) const;
    void mostrarDetalleContacto(const Contacto& contacto) const;
    
    // Entrada de datos
    std::string leerTexto(const std::string& prompt) const;
    std::string leerTextoOpcional(const std::string& prompt) const;
    int leerOpcion(int min, int max) const;
    bool confirmar(const std::string& mensaje) const;
};

#endif
