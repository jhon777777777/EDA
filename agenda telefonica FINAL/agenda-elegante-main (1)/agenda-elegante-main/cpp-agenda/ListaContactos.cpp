// ══════════════════════════════════════════════════════════════════
// LISTACONTACTOS.CPP - Implementación de la Lista Doblemente Enlazada
// ══════════════════════════════════════════════════════════════════

#include "ListaContactos.h"
#include <algorithm>
#include <cctype>

ListaContactos::ListaContactos() : cabeza(nullptr), cola(nullptr), contadorId(1) {}

ListaContactos::~ListaContactos() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

std::string ListaContactos::aMinusculas(const std::string& texto) const {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
    return resultado;
}

bool ListaContactos::agregarContacto(Contacto& contacto) {
    // Validar DNI duplicado
    if (existeDni(contacto.dni)) {
        return false;
    }
    
    // Validar teléfono
    if (!esTelefonoValido(contacto.telefono)) {
        return false;
    }
    
    // Asignar ID automático
    contacto.id = contadorId++;
    
    Nodo* nuevoNodo = new Nodo(contacto);
    
    // Lista vacía
    if (cabeza == nullptr) {
        cabeza = cola = nuevoNodo;
        return true;
    }
    
    // Inserción ordenada por nombre
    std::string nombreNuevo = aMinusculas(contacto.nombreCompleto);
    
    // Insertar al inicio
    if (aMinusculas(cabeza->contacto.nombreCompleto) > nombreNuevo) {
        nuevoNodo->siguiente = cabeza;
        cabeza->anterior = nuevoNodo;
        cabeza = nuevoNodo;
        return true;
    }
    
    // Buscar posición correcta
    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr && 
           aMinusculas(actual->siguiente->contacto.nombreCompleto) < nombreNuevo) {
        actual = actual->siguiente;
    }
    
    // Insertar después de actual
    nuevoNodo->siguiente = actual->siguiente;
    nuevoNodo->anterior = actual;
    
    if (actual->siguiente != nullptr) {
        actual->siguiente->anterior = nuevoNodo;
    } else {
        cola = nuevoNodo;
    }
    
    actual->siguiente = nuevoNodo;
    return true;
}

bool ListaContactos::eliminarContacto(const std::string& dni) {
    Nodo* actual = cabeza;
    
    while (actual != nullptr) {
        if (actual->contacto.dni == dni) {
            // Único nodo
            if (actual == cabeza && actual == cola) {
                cabeza = cola = nullptr;
            }
            // Primer nodo
            else if (actual == cabeza) {
                cabeza = cabeza->siguiente;
                cabeza->anterior = nullptr;
            }
            // Último nodo
            else if (actual == cola) {
                cola = cola->anterior;
                cola->siguiente = nullptr;
            }
            // Nodo intermedio
            else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            
            delete actual;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

Contacto* ListaContactos::buscarPorDni(const std::string& dni) const {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->contacto.dni == dni) {
            return &(actual->contacto);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

std::vector<Contacto> ListaContactos::buscarPorTexto(const std::string& texto) const {
    std::vector<Contacto> resultados;
    std::string busqueda = aMinusculas(texto);
    
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Contacto& c = actual->contacto;
        
        // Buscar en todos los campos
        if (aMinusculas(c.nombreCompleto).find(busqueda) != std::string::npos ||
            aMinusculas(c.dni).find(busqueda) != std::string::npos ||
            aMinusculas(c.telefono).find(busqueda) != std::string::npos ||
            aMinusculas(c.correo).find(busqueda) != std::string::npos ||
            aMinusculas(c.direccion).find(busqueda) != std::string::npos ||
            aMinusculas(c.nombrePadre).find(busqueda) != std::string::npos ||
            aMinusculas(c.nombreMadre).find(busqueda) != std::string::npos) {
            resultados.push_back(c);
        }
        
        actual = actual->siguiente;
    }
    
    return resultados;
}

std::vector<Contacto> ListaContactos::obtenerTodos() const {
    std::vector<Contacto> todos;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        todos.push_back(actual->contacto);
        actual = actual->siguiente;
    }
    return todos;
}

bool ListaContactos::existeDni(const std::string& dni) const {
    return buscarPorDni(dni) != nullptr;
}

bool ListaContactos::esTelefonoValido(const std::string& telefono) const {
    if (telefono.length() < 9 || telefono.length() > 15) {
        return false;
    }
    for (char c : telefono) {
        if (!isdigit(c) && c != '+' && c != ' ' && c != '-') {
            return false;
        }
    }
    return true;
}

bool ListaContactos::esDniValido(const std::string& dni) const {
    if (dni.length() != 8) return false;
    for (char c : dni) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int ListaContactos::getCantidad() const {
    int cantidad = 0;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

bool ListaContactos::estaVacia() const {
    return cabeza == nullptr;
}

void ListaContactos::setContadorId(int id) {
    contadorId = id;
}

int ListaContactos::getContadorId() const {
    return contadorId;
}
