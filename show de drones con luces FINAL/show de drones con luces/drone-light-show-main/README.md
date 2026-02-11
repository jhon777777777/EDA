# Show de Drones 2D - Candelaria 2026

Simulador visual de espectáculo de drones para la Festividad de la Virgen de la Candelaria 2026.

## Arquitectura

El proyecto utiliza una arquitectura híbrida:

- **Frontend (React/TypeScript)**: Solo se encarga de la visualización
- **Backend (C++/WebAssembly)**: Toda la lógica de drones, formaciones y animaciones

### Estructura del Código C++

```
src/cpp/
├── core/                    # Clases base
│   ├── drone.h/cpp         # Clase Drone individual
│   └── figura_base.h/cpp   # Clase base para figuras
│
├── textos/                  # Formaciones de texto
│   ├── puno_se_respeta.cpp
│   ├── sistemas_unap.cpp
│   ├── epis.cpp
│   └── candelaria_2026.cpp
│
├── iconos_culturales/       # Iconos representativos
│   ├── mascara_diablada.cpp
│   └── virgen_candelaria.cpp
│
├── simbolos/                # Símbolos y formas
│   ├── estrellas.cpp
│   └── torre_eiffel.cpp
│
├── factory/                 # Patrón Factory
│   ├── creador_figuras.h
│   └── creador_figuras.cpp
│
└── api/                     # Interfaz WebAssembly
    └── wasm_interface.cpp
```

## Compilación a WebAssembly

### Requisitos

- [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)
- CMake 3.14 o superior

### Pasos

```bash
# 1. Activar Emscripten
source /ruta/a/emsdk/emsdk_env.sh

# 2. Crear directorio de build
mkdir build && cd build

# 3. Configurar con CMake
emcmake cmake ..

# 4. Compilar
emmake make

# Los archivos se generan en src/wasm/
#   - figuras.js
#   - figuras.wasm
```

## API WebAssembly

### Funciones disponibles

```javascript
// Inicializar el simulador
Module.inicializarSimulador(500, 900, 600); // drones, ancho, alto

// Seleccionar una figura
Module.seleccionarFigura("ESTRELLAS");

// Actualizar animación (llamar cada frame)
Module.actualizarAnimacion(deltaTime);

// Obtener posición de un drone
const x = Module.obtenerDroneX(indice);
const y = Module.obtenerDroneY(indice);
const color = Module.obtenerDroneColor(indice);

// Estado de la transición
const enTransicion = Module.estaEnTransicion();
const progreso = Module.obtenerProgresoTransicion();
```

### Figuras disponibles

| ID | Categoría | Descripción |
|----|-----------|-------------|
| PUNO_SE_RESPETA | Textos | Texto emblemático |
| SISTEMAS_UNAP | Textos | Ingeniería de Sistemas |
| EPIS | Textos | Escuela Profesional |
| CANDELARIA_2026 | Textos | Año conmemorativo |
| DIABLADA | Iconos | Máscara tradicional |
| VIRGEN | Iconos | Virgen de la Candelaria |
| ESTRELLAS | Símbolos | Constelación de estrellas |
| TORRE_EIFFEL | Símbolos | Monumento icónico |

## Uso en React

```tsx
import { useEffect, useRef } from 'react';

function DroneCanvas() {
  const moduleRef = useRef(null);
  
  useEffect(() => {
    // Cargar el módulo WASM
    createModule().then(module => {
      moduleRef.current = module;
      module.inicializarSimulador(500, 900, 600);
      module.seleccionarFigura("ESTRELLAS");
    });
  }, []);
  
  // En el loop de animación
  const animate = () => {
    if (moduleRef.current) {
      moduleRef.current.actualizarAnimacion(0.016);
      
      // Dibujar drones
      const count = moduleRef.current.obtenerCantidadDrones();
      for (let i = 0; i < count; i++) {
        const x = moduleRef.current.obtenerDroneX(i);
        const y = moduleRef.current.obtenerDroneY(i);
        const color = moduleRef.current.obtenerDroneColor(i);
        // ... dibujar en canvas
      }
    }
  };
}
```

## Agregar nuevas figuras

1. Crear archivo en la categoría correspondiente:
   ```cpp
   // src/cpp/textos/mi_figura.cpp
   #include "../core/figura_base.h"
   
   class MiFigura : public FiguraBase {
   public:
       MiFigura(int cantidad, float ancho, float alto)
           : FiguraBase("MI_FIGURA", "Mi Figura", "textos", cantidad, ancho, alto) {}
       
       std::vector<PosicionDrone> generarPosiciones() override {
           // Implementar lógica
       }
   };
   ```

2. Registrar en el factory (`creador_figuras.cpp`):
   ```cpp
   #include "../textos/mi_figura.cpp"
   
   void CreadorFiguras::registrarFiguras() {
       // ...
       registrar<MiFigura>("MI_FIGURA");
   }
   ```

3. Recompilar a WebAssembly

## Desarrollo Web

```bash
# Instalar dependencias
npm install

# Iniciar servidor de desarrollo
npm run dev
```

## Licencia

Proyecto desarrollado para la Festividad de la Virgen de la Candelaria, Puno - Perú 2026.
