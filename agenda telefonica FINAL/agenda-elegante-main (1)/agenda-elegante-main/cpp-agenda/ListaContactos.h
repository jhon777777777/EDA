// ══════════════════════════════════════════════════════════════════
// LISTACONTACTOS.H - Declaración de la Lista Doblemente Enlazada
// ══════════════════════════════════════════════════════════════════

#ifndef LISTA_CONTACTOS_H
#define LISTA_CONTACTOS_H

#include "Nodo.h"
#include <vector>
#include <string>

class ListaContactos {
private:
    Nodo* cabeza;
    Nodo* cola;
    int contadorId;
    
    // Convierte string a minúsculas para comparaciones
    std::string aMinusculas(const std::string& texto) const;

public:
    ListaContactos();
    ~ListaContactos();
    
    // Operaciones principales
    bool agregarContacto(Contacto& contacto);
    bool eliminarContacto(const std::string& dni);
    Contacto* buscarPorDni(const std::string& dni) const;
    
    // Búsqueda inteligente por cualquier campo
    std::vector<Contacto> buscarPorTexto(const std::string& texto) const;
    
    // Obtener todos los contactos
    std::vector<Contacto> obtenerTodos() const;
    
    // Validaciones
    bool existeDni(const std::string& dni) const;
    bool esTelefonoValido(const std::string& telefono) const;
    bool esDniValido(const std::string& dni) const;
    
    // Utilidades
    int getCantidad() const;
    bool estaVacia() const;
    void setContadorId(int id);
    int getContadorId() const;
};

#endif
