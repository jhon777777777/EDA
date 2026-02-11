// ══════════════════════════════════════════════════════════════════
// ARCHIVOAGENDA.CPP - Implementación del Manejo de Archivos
// ══════════════════════════════════════════════════════════════════

#include "ArchivoAgenda.h"
#include <fstream>
#include <sstream>

ArchivoAgenda::ArchivoAgenda(const std::string& archivo) : nombreArchivo(archivo) {}

bool ArchivoAgenda::guardar(const ListaContactos& lista) const {
    std::ofstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        return false;
    }
    
    // Guardar el contador de ID en la primera línea
    archivo << "CONTADOR:" << lista.getContadorId() << "\n";
    
    // Guardar cada contacto
    std::vector<Contacto> contactos = lista.obtenerTodos();
    
    for (const Contacto& c : contactos) {
        archivo << c.id << SEPARADOR
                << c.dni << SEPARADOR
                << c.nombreCompleto << SEPARADOR
                << c.telefono << SEPARADOR
                << c.correo << SEPARADOR
                << c.direccion << SEPARADOR
                << c.nombrePadre << SEPARADOR
                << c.nombreMadre << "\n";
    }
    
    archivo.close();
    return true;
}

bool ArchivoAgenda::cargar(ListaContactos& lista) const {
    std::ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        return false;
    }
    
    std::string linea;
    int maxId = 0;
    
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        // Leer el contador
        if (linea.substr(0, 9) == "CONTADOR:") {
            int contador = std::stoi(linea.substr(9));
            lista.setContadorId(contador);
            continue;
        }
        
        std::stringstream ss(linea);
        std::string campo;
        Contacto contacto;
        
        // Parsear cada campo
        if (std::getline(ss, campo, SEPARADOR)) contacto.id = std::stoi(campo);
        if (std::getline(ss, campo, SEPARADOR)) contacto.dni = campo;
        if (std::getline(ss, campo, SEPARADOR)) contacto.nombreCompleto = campo;
        if (std::getline(ss, campo, SEPARADOR)) contacto.telefono = campo;
        if (std::getline(ss, campo, SEPARADOR)) contacto.correo = campo;
        if (std::getline(ss, campo, SEPARADOR)) contacto.direccion = campo;
        if (std::getline(ss, campo, SEPARADOR)) contacto.nombrePadre = campo;
        if (std::getline(ss, campo, SEPARADOR)) contacto.nombreMadre = campo;
        
        if (contacto.id > maxId) maxId = contacto.id;
        
        // Insertar sin validar (ya está validado)
        lista.agregarContacto(contacto);
    }
    
    archivo.close();
    return true;
}

bool ArchivoAgenda::existeArchivo() const {
    std::ifstream archivo(nombreArchivo);
    return archivo.good();
}
