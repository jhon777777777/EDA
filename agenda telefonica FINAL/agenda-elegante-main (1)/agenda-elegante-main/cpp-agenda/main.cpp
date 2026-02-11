// ================================================================
//  AGENDA TELEFONICA PROFESIONAL EN C++
//  Desarrollado con Lista Doblemente Enlazada
// ================================================================

#include <iostream>
#include "ListaContactos.h"
#include "Interfaz.h"
#include "ArchivoAgenda.h"

using namespace std;

// ================================================================
// FUNCIONES DEL MENU
// ================================================================

void agregarContacto(ListaContactos& lista, Interfaz& ui) {
    ui.limpiarPantalla();
    ui.mostrarEncabezado("AGREGAR NUEVO CONTACTO");
    
    Contacto nuevoContacto;
    
    // Datos obligatorios
    cout << "  DATOS OBLIGATORIOS\n";
    cout << "  ---------------------\n\n";
    
    // DNI con validacion
    string dni;
    do {
        dni = ui.leerTexto("DNI (8 digitos)");
        if (!lista.esDniValido(dni)) {
            ui.mostrarError("El DNI debe tener exactamente 8 digitos numericos.");
        } else if (lista.existeDni(dni)) {
            ui.mostrarError("Ya existe un contacto con ese DNI.");
            dni = "";
        }
    } while (dni.empty() || !lista.esDniValido(dni) || lista.existeDni(dni));
    nuevoContacto.dni = dni;
    
    nuevoContacto.nombreCompleto = ui.leerTexto("Nombre completo");
    
    // Telefono con validacion
    string telefono;
    do {
        telefono = ui.leerTexto("Telefono (minimo 9 digitos)");
        if (!lista.esTelefonoValido(telefono)) {
            ui.mostrarError("Telefono invalido. Use solo numeros, espacios, guiones o +.");
        }
    } while (!lista.esTelefonoValido(telefono));
    nuevoContacto.telefono = telefono;
    
    // Datos opcionales
    cout << "\n  DATOS OPCIONALES (presione ENTER para omitir)\n";
    cout << "  -----------------------------------------------\n\n";
    
    nuevoContacto.correo = ui.leerTextoOpcional("Correo electronico");
    nuevoContacto.direccion = ui.leerTextoOpcional("Direccion");
    nuevoContacto.nombrePadre = ui.leerTextoOpcional("Nombre del padre");
    nuevoContacto.nombreMadre = ui.leerTextoOpcional("Nombre de la madre");
    
    // Agregar a la lista
    if (lista.agregarContacto(nuevoContacto)) {
        ui.mostrarExito("Contacto agregado exitosamente con ID: " + to_string(nuevoContacto.id));
    } else {
        ui.mostrarError("No se pudo agregar el contacto.");
    }
    
    ui.pausar();
}

void verContactos(ListaContactos& lista, Interfaz& ui) {
    ui.limpiarPantalla();
    ui.mostrarEncabezado("LISTA DE CONTACTOS");
    
    vector<Contacto> contactos = lista.obtenerTodos();
    ui.mostrarTablaContactos(contactos);
    
    ui.pausar();
}

void buscarContacto(ListaContactos& lista, Interfaz& ui) {
    ui.limpiarPantalla();
    ui.mostrarEncabezado("BUSCAR CONTACTO");
    
    cout << "  Puede buscar por: nombre, DNI, telefono, correo,\n";
    cout << "  direccion, nombre del padre o madre.\n\n";
    
    string busqueda = ui.leerTexto("Ingrese texto a buscar");
    
    vector<Contacto> resultados = lista.buscarPorTexto(busqueda);
    
    if (resultados.empty()) {
        ui.mostrarMensaje("No se encontraron contactos con: \"" + busqueda + "\"");
    } else {
        cout << "\n  Se encontraron " << resultados.size() << " resultado(s):\n";
        ui.mostrarTablaContactos(resultados);
    }
    
    ui.pausar();
}

void eliminarContacto(ListaContactos& lista, Interfaz& ui) {
    ui.limpiarPantalla();
    ui.mostrarEncabezado("ELIMINAR CONTACTO");
    
    if (lista.estaVacia()) {
        ui.mostrarMensaje("No hay contactos en la agenda.");
        ui.pausar();
        return;
    }
    
    string dni = ui.leerTexto("Ingrese el DNI del contacto a eliminar");
    
    Contacto* contacto = lista.buscarPorDni(dni);
    
    if (contacto == nullptr) {
        ui.mostrarError("No se encontro ningun contacto con DNI: " + dni);
    } else {
        ui.mostrarDetalleContacto(*contacto);
        
        if (ui.confirmar("Esta seguro de eliminar este contacto?")) {
            if (lista.eliminarContacto(dni)) {
                ui.mostrarExito("Contacto eliminado correctamente.");
            } else {
                ui.mostrarError("No se pudo eliminar el contacto.");
            }
        } else {
            ui.mostrarMensaje("Operacion cancelada.");
        }
    }
    
    ui.pausar();
}

void verDetalleContacto(ListaContactos& lista, Interfaz& ui) {
    ui.limpiarPantalla();
    ui.mostrarEncabezado("VER DETALLE DE CONTACTO");
    
    if (lista.estaVacia()) {
        ui.mostrarMensaje("No hay contactos en la agenda.");
        ui.pausar();
        return;
    }
    
    string dni = ui.leerTexto("Ingrese el DNI del contacto");
    
    Contacto* contacto = lista.buscarPorDni(dni);
    
    if (contacto == nullptr) {
        ui.mostrarError("No se encontro ningun contacto con DNI: " + dni);
    } else {
        ui.mostrarDetalleContacto(*contacto);
    }
    
    ui.pausar();
}

// ================================================================
// FUNCION PRINCIPAL
// ================================================================

int main() {
    ListaContactos agenda;
    Interfaz ui;
    ArchivoAgenda archivo("agenda.txt");
    
    // Cargar datos existentes
    if (archivo.existeArchivo()) {
        if (archivo.cargar(agenda)) {
            cout << "\n  [OK] Datos cargados desde agenda.txt\n";
        }
    } else {
        cout << "\n  [i] Se creara un nuevo archivo agenda.txt\n";
    }
    
    int opcion;
    
    do {
        ui.limpiarPantalla();
        ui.mostrarMenuPrincipal();
        opcion = ui.leerOpcion(1, 6);
        
        switch (opcion) {
            case 1:
                agregarContacto(agenda, ui);
                break;
            case 2:
                verContactos(agenda, ui);
                break;
            case 3:
                buscarContacto(agenda, ui);
                break;
            case 4:
                eliminarContacto(agenda, ui);
                break;
            case 5:
                verDetalleContacto(agenda, ui);
                break;
            case 6:
                // Guardar antes de salir
                if (archivo.guardar(agenda)) {
                    ui.mostrarExito("Datos guardados correctamente.");
                } else {
                    ui.mostrarError("No se pudieron guardar los datos.");
                }
                cout << "\n  Hasta pronto!\n\n";
                break;
        }
        
    } while (opcion != 6);
    
    return 0;
}
