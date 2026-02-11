// ══════════════════════════════════════════════════════════════════
// ARCHIVOAGENDA.H - Declaración del Manejo de Archivos
// ══════════════════════════════════════════════════════════════════

#ifndef ARCHIVO_AGENDA_H
#define ARCHIVO_AGENDA_H

#include "ListaContactos.h"
#include <string>

class ArchivoAgenda {
private:
    std::string nombreArchivo;
    const char SEPARADOR = '|';
    
public:
    ArchivoAgenda(const std::string& archivo = "agenda.txt");
    
    // Operaciones de archivo
    bool guardar(const ListaContactos& lista) const;
    bool cargar(ListaContactos& lista) const;
    bool existeArchivo() const;
};

#endif
