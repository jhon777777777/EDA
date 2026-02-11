// ══════════════════════════════════════════════════════════════════
// NODO.H - Nodo de la Lista Doblemente Enlazada
// ══════════════════════════════════════════════════════════════════

#ifndef NODO_H
#define NODO_H

#include "Contacto.h"

struct Nodo {
    Contacto contacto;
    Nodo* siguiente;
    Nodo* anterior;
    
    Nodo(Contacto c) : contacto(c), siguiente(nullptr), anterior(nullptr) {}
};

#endif
