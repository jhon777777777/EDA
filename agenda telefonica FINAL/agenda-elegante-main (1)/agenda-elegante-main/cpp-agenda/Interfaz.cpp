// ================================================================
// INTERFAZ.CPP - Implementacion de la Interfaz de Usuario
// ================================================================

#include "Interfaz.h"
#include <iostream>
#include <iomanip>
#include <limits>

#ifdef _WIN32
    #include <cstdlib>
    #define LIMPIAR "cls"
#else
    #define LIMPIAR "clear"
#endif

using namespace std;

// ================================================================
// UTILIDADES DE FORMATO
// ================================================================

string Interfaz::centrar(const string& texto, int ancho) const {
    int espacios = (ancho - texto.length()) / 2;
    if (espacios < 0) espacios = 0;
    return string(espacios, ' ') + texto;
}

string Interfaz::recortar(const string& texto, int maxLen) const {
    if (texto.length() <= maxLen) return texto;
    return texto.substr(0, maxLen - 2) + "..";
}

// ================================================================
// PANTALLA
// ================================================================

void Interfaz::limpiarPantalla() const {
    system(LIMPIAR);
}

void Interfaz::pausar() const {
    cout << "\n  Presione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ================================================================
// MENUS
// ================================================================

void Interfaz::mostrarMenuPrincipal() const {
    cout << "\n";
    cout << "  +======================================+\n";
    cout << "  |                                      |\n";
    cout << "  |        AGENDA TELEFONICA             |\n";
    cout << "  |                                      |\n";
    cout << "  +======================================+\n";
    cout << "  |                                      |\n";
    cout << "  |   1. Agregar contacto                |\n";
    cout << "  |   2. Ver todos los contactos         |\n";
    cout << "  |   3. Buscar contacto                 |\n";
    cout << "  |   4. Eliminar contacto               |\n";
    cout << "  |   5. Ver detalle de contacto         |\n";
    cout << "  |   6. Salir                           |\n";
    cout << "  |                                      |\n";
    cout << "  +======================================+\n";
    cout << "\n  >> Seleccione una opcion: ";
}

void Interfaz::mostrarEncabezado(const string& titulo) const {
    int ancho = 40;
    cout << "\n";
    cout << "  +" << string(ancho, '=') << "+\n";
    cout << "  |" << centrar(titulo, ancho) << "|\n";
    cout << "  +" << string(ancho, '=') << "+\n\n";
}

// ================================================================
// MENSAJES
// ================================================================

void Interfaz::mostrarMensaje(const string& mensaje) const {
    cout << "\n  [i] " << mensaje << "\n";
}

void Interfaz::mostrarError(const string& error) const {
    cout << "\n  [X] ERROR: " << error << "\n";
}

void Interfaz::mostrarExito(const string& exito) const {
    cout << "\n  [OK] " << exito << "\n";
}

// ================================================================
// TABLAS
// ================================================================

void Interfaz::mostrarTablaContactos(const vector<Contacto>& contactos) const {
    if (contactos.empty()) {
        mostrarMensaje("No hay contactos para mostrar.");
        return;
    }
    
    cout << "\n";
    cout << "  +------+----------+------------------------+--------------+\n";
    cout << "  |  ID  |   DNI    |         NOMBRE         |   TELEFONO   |\n";
    cout << "  +------+----------+------------------------+--------------+\n";
    
    for (const Contacto& c : contactos) {
        cout << "  | " << setw(4) << left << c.id << " | ";
        cout << setw(8) << left << recortar(c.dni, 8) << " | ";
        cout << setw(22) << left << recortar(c.nombreCompleto, 22) << " | ";
        cout << setw(12) << left << recortar(c.telefono, 12) << " |\n";
    }
    
    cout << "  +------+----------+------------------------+--------------+\n";
    cout << "\n  Total de contactos: " << contactos.size() << "\n";
}

void Interfaz::mostrarDetalleContacto(const Contacto& contacto) const {
    cout << "\n";
    cout << "  +============================================+\n";
    cout << "  |           DETALLE DEL CONTACTO            |\n";
    cout << "  +============================================+\n";
    cout << "  |  ID:          " << setw(28) << left << contacto.id << " |\n";
    cout << "  |  DNI:         " << setw(28) << left << contacto.dni << " |\n";
    cout << "  |  Nombre:      " << setw(28) << left << recortar(contacto.nombreCompleto, 28) << " |\n";
    cout << "  |  Telefono:    " << setw(28) << left << contacto.telefono << " |\n";
    cout << "  +--------------------------------------------+\n";
    cout << "  |  Correo:      " << setw(28) << left << (contacto.correo.empty() ? "No registrado" : contacto.correo) << " |\n";
    cout << "  |  Direccion:   " << setw(28) << left << (contacto.direccion.empty() ? "No registrada" : recortar(contacto.direccion, 28)) << " |\n";
    cout << "  |  Padre:       " << setw(28) << left << (contacto.nombrePadre.empty() ? "No registrado" : recortar(contacto.nombrePadre, 28)) << " |\n";
    cout << "  |  Madre:       " << setw(28) << left << (contacto.nombreMadre.empty() ? "No registrada" : recortar(contacto.nombreMadre, 28)) << " |\n";
    cout << "  +============================================+\n";
}

// ================================================================
// ENTRADA DE DATOS
// ================================================================

string Interfaz::leerTexto(const string& prompt) const {
    string texto;
    do {
        cout << "  " << prompt << ": ";
        getline(cin, texto);
        if (texto.empty()) {
            mostrarError("Este campo es obligatorio.");
        }
    } while (texto.empty());
    return texto;
}

string Interfaz::leerTextoOpcional(const string& prompt) const {
    string texto;
    cout << "  " << prompt << " (opcional): ";
    getline(cin, texto);
    return texto;
}

int Interfaz::leerOpcion(int min, int max) const {
    int opcion;
    while (!(cin >> opcion) || opcion < min || opcion > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [X] Opcion invalida. Intente de nuevo: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return opcion;
}

bool Interfaz::confirmar(const string& mensaje) const {
    char respuesta;
    cout << "  " << mensaje << " (S/N): ";
    cin >> respuesta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return (respuesta == 'S' || respuesta == 's');
}
