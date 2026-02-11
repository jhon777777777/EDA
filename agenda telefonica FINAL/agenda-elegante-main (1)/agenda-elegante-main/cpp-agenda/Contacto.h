// ══════════════════════════════════════════════════════════════════
// CONTACTO.H - Estructura del Contacto
// ══════════════════════════════════════════════════════════════════

#ifndef CONTACTO_H
#define CONTACTO_H

#include <string>

struct Contacto {
    int id;
    std::string dni;
    std::string nombreCompleto;
    std::string telefono;
    
    // Datos opcionales
    std::string correo;
    std::string direccion;
    std::string nombrePadre;
    std::string nombreMadre;
    
    // Constructor por defecto
    Contacto() : id(0), dni(""), nombreCompleto(""), telefono(""),
                 correo(""), direccion(""), nombrePadre(""), nombreMadre("") {}
    
    // Constructor con datos obligatorios
    Contacto(int _id, std::string _dni, std::string _nombre, std::string _tel)
        : id(_id), dni(_dni), nombreCompleto(_nombre), telefono(_tel),
          correo(""), direccion(""), nombrePadre(""), nombreMadre("") {}
};

#endif
