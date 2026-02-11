cmake_minimum_required(VERSION 3.14)
project(ShowDrones2D VERSION 1.0.0 LANGUAGES CXX)

# Configuración de C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detectar si estamos compilando con Emscripten
if(EMSCRIPTEN)
    message(STATUS "Compilando para WebAssembly con Emscripten")
    
    # Flags de Emscripten
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MODULARIZE=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORT_NAME='createModule'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ENVIRONMENT='web'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1")
    
    # Archivos fuente
    set(SOURCES
        src/cpp/core/drone.cpp
        src/cpp/core/figura_base.cpp
        src/cpp/factory/creador_figuras.cpp
        src/cpp/api/wasm_interface.cpp
    )
    
    # Crear el ejecutable (que genera .wasm y .js)
    add_executable(figuras ${SOURCES})
    
    # Configurar salida
    set_target_properties(figuras PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/src/wasm"
        SUFFIX ".js"
    )
    
else()
    message(STATUS "Compilando versión nativa para pruebas")
    
    # Versión nativa para pruebas locales
    set(SOURCES
        src/cpp/core/drone.cpp
        src/cpp/core/figura_base.cpp
        src/cpp/factory/creador_figuras.cpp
    )
    
    # Crear librería estática para pruebas
    add_library(figuras_lib STATIC ${SOURCES})
    
    # Programa de prueba
    add_executable(test_figuras tests/test_figuras.cpp)
    target_link_libraries(test_figuras figuras_lib)
    
endif()

# Incluir directorios
include_directories(${CMAKE_SOURCE_DIR}/src/cpp)

# Información de compilación
message(STATUS "")
message(STATUS "=== Show de Drones 2D - Configuración ===")
message(STATUS "Versión: ${PROJECT_VERSION}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Estándar C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "")
message(STATUS "Para compilar a WebAssembly:")
message(STATUS "  mkdir build && cd build")
message(STATUS "  emcmake cmake ..")
message(STATUS "  emmake make")
message(STATUS "")
message(STATUS "Archivos generados en: src/wasm/")
message(STATUS "=========================================")
