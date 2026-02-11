# 📱 Agenda Telefónica Profesional en C++

Una agenda telefónica de consola elegante y profesional, desarrollada con **Lista Doblemente Enlazada**.

## 📁 Estructura del Proyecto

```
cpp-agenda/
├── main.cpp              → Punto de entrada y flujo principal
├── Contacto.h            → Estructura del contacto
├── Nodo.h                → Nodo de la lista doblemente enlazada
├── ListaContactos.h      → Declaración de la lista
├── ListaContactos.cpp    → Implementación de la lista
├── Interfaz.h            → Declaración de la interfaz
├── Interfaz.cpp          → Implementación de la interfaz
├── ArchivoAgenda.h       → Declaración del manejo de archivos
├── ArchivoAgenda.cpp     → Implementación del manejo de archivos
└── agenda.txt            → Archivo de datos (se crea automáticamente)
```

## 🚀 Compilación

### En Windows (MinGW)
```bash
g++ -o agenda main.cpp ListaContactos.cpp Interfaz.cpp ArchivoAgenda.cpp -std=c++11
```

### En Linux/Mac
```bash
g++ -o agenda main.cpp ListaContactos.cpp Interfaz.cpp ArchivoAgenda.cpp -std=c++11
```

## 💻 Ejecución

```bash
./agenda
```

## ✨ Características

- ✅ Lista doblemente enlazada con inserción ordenada alfabéticamente
- ✅ Validación de DNI (8 dígitos, sin duplicados)
- ✅ Validación de teléfonos
- ✅ Búsqueda inteligente por cualquier campo
- ✅ Interfaz visual con tablas y cuadros ASCII
- ✅ Persistencia de datos en archivo TXT
- ✅ Código modular y organizado
- ✅ Comentarios en español

## 📋 Menú Principal

```
╔══════════════════════════════════════╗
║                                      ║
║        📱 AGENDA TELEFÓNICA          ║
║                                      ║
╠══════════════════════════════════════╣
║                                      ║
║   1. ➕ Agregar contacto             ║
║   2. 📋 Ver todos los contactos     ║
║   3. 🔍 Buscar contacto              ║
║   4. ❌ Eliminar contacto            ║
║   5. 👁️  Ver detalle de contacto     ║
║   6. 🚪 Salir                        ║
║                                      ║
╚══════════════════════════════════════╝
```

## 📊 Ejemplo de Tabla

```
┌──────┬──────────┬────────────────────────┬──────────────┐
│  ID  │   DNI    │         NOMBRE         │   TELÉFONO   │
├──────┼──────────┼────────────────────────┼──────────────┤
│ 1    │ 73451268 │ García López, Juan     │ 987654321    │
│ 2    │ 71234598 │ Martínez Ruiz, María   │ 912345678    │
└──────┴──────────┴────────────────────────┴──────────────┘
```

## 👤 Estructura del Contacto

**Datos Obligatorios:**
- ID (autogenerado)
- DNI (8 dígitos)
- Nombre completo
- Teléfono

**Datos Opcionales:**
- Correo electrónico
- Dirección
- Nombre del padre
- Nombre de la madre

## 📝 Notas

- Los emojis se muestran correctamente en terminales que soporten UTF-8
- En Windows, puede que necesites configurar la consola para UTF-8:
  ```bash
  chcp 65001
  ```
- Los datos se guardan automáticamente al salir del programa
