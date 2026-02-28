# KNN en C++ - Guía de Compilación

## Archivos C++
| Archivo | Descripción |
|---------|-------------|
| `Punto.h` | Structs: Punto y VecinoConDistancia |
| `KNN.h` | Declaraciones de funciones del algoritmo |
| `KNN.cpp` | Implementación: distancia, vecinos, clasificación |
| `Visualizador.h` | Funciones de conversión coordenadas ↔ píxeles |
| `main.cpp` | Programa principal con menú interactivo |

## Compilar y ejecutar

```bash
g++ -o knn main.cpp KNN.cpp -std=c++17
./knn
```

## Equivalencia con la versión web

| C++ | Web (TypeScript) |
|-----|-------------------|
| `Punto.h` | `src/lib/knn.ts` (interfaces) |
| `KNN.h / KNN.cpp` | `src/lib/knn.ts` (funciones) |
| `Visualizador.h` | `src/components/KNNCanvas.tsx` |
| `main.cpp` | `src/pages/Index.tsx` + `src/components/ControlPanel.tsx` |
