// Utilidades para generar formaciones de drones - Candelaria 2026

const ANCHO_CANVAS = 1200;
const ALTO_CANVAS = 700;
const CANTIDAD_DRONES = 500;

// Colores para las formaciones
const COLORES = {
  dorado: '#FFD700',
  cian: '#00FFFF',
  magenta: '#FF00FF',
  rojo: '#FF3333',
  verde: '#00FF66',
  azul: '#3366FF',
  blanco: '#FFFFFF',
  naranja: '#FF6600',
  purpura: '#9933FF',
  rosa: '#FF66B2',
  rojoOscuro: '#CC0000',
  plata: '#C0C0C0',
  azulClaro: '#66CCFF',
};

// Generar texto con estilo limpio (barras rectas como EPIS)
function generarPuntosTexto(texto: string, espaciadoLetras: number = 20): { x: number; y: number }[] {
  const puntos: { x: number; y: number }[] = [];
  const anchoCaracter = 60;
  const altoCaracter = 100;
  const grosorTrazo = 14;
  
  const anchoTotal = texto.length * (anchoCaracter + espaciadoLetras) - espaciadoLetras;
  const inicioX = (ANCHO_CANVAS - anchoTotal) / 2;
  const inicioY = (ALTO_CANVAS - altoCaracter) / 2;
  
  // Función auxiliar para dibujar barra vertical
  const barraVertical = (bx: number, by: number, altura: number) => {
    for (let y = 0; y <= altura; y += 3) {
      for (let t = 0; t < grosorTrazo; t += 3) {
        puntos.push({ x: bx + t, y: by + y });
      }
    }
  };
  
  // Función auxiliar para dibujar barra horizontal
  const barraHorizontal = (bx: number, by: number, ancho: number) => {
    for (let x = 0; x <= ancho; x += 3) {
      for (let t = 0; t < grosorTrazo; t += 3) {
        puntos.push({ x: bx + x, y: by + t });
      }
    }
  };
  
  // Función auxiliar para dibujar curva
  const curva = (cx: number, cy: number, radio: number, inicio: number, fin: number) => {
    for (let a = inicio; a <= fin; a += 0.08) {
      for (let t = 0; t < grosorTrazo; t += 3) {
        puntos.push({ 
          x: cx + (radio - t) * Math.cos(a), 
          y: cy + (radio - t) * Math.sin(a) 
        });
      }
    }
  };
  
  // Definición de letras con trazos limpios
  const dibujarLetra: { [key: string]: (bx: number, by: number, w: number, h: number) => void } = {
    'A': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h / 2, w);
    },
    'B': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraHorizontal(bx, by, w * 0.8);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w * 0.8);
      barraHorizontal(bx, by + h - grosorTrazo, w * 0.8);
      curva(bx + w * 0.65, by + h * 0.25, h * 0.25, -Math.PI / 2, Math.PI / 2);
      curva(bx + w * 0.7, by + h * 0.75, h * 0.25, -Math.PI / 2, Math.PI / 2);
    },
    'C': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    'D': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraHorizontal(bx, by, w * 0.7);
      barraHorizontal(bx, by + h - grosorTrazo, w * 0.7);
      curva(bx + w * 0.5, by + h / 2, h / 2, -Math.PI / 2, Math.PI / 2);
    },
    'E': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w * 0.75);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    'F': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w * 0.7);
    },
    'G': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h - grosorTrazo, w);
      barraHorizontal(bx + w / 2, by + h / 2, w / 2);
      barraVertical(bx + w - grosorTrazo, by + h / 2, h / 2);
    },
    'H': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w);
    },
    'I': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx + w / 2 - grosorTrazo / 2, by, h);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    'J': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx + w - grosorTrazo, by, h * 0.75);
      barraHorizontal(bx, by + h - grosorTrazo, w - grosorTrazo);
      barraVertical(bx, by + h * 0.6, h * 0.4);
    },
    'K': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      for (let i = 0; i <= 1; i += 0.03) {
        for (let t = 0; t < grosorTrazo; t += 3) {
          puntos.push({ x: bx + grosorTrazo + i * (w - grosorTrazo), y: by + h / 2 - i * h / 2 + t });
          puntos.push({ x: bx + grosorTrazo + i * (w - grosorTrazo), y: by + h / 2 + i * h / 2 - t });
        }
      }
    },
    'L': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    'M': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      for (let i = 0; i <= 1; i += 0.03) {
        for (let t = 0; t < grosorTrazo; t += 3) {
          puntos.push({ x: bx + grosorTrazo + i * (w / 2 - grosorTrazo), y: by + i * h / 3 + t });
          puntos.push({ x: bx + w / 2 + i * (w / 2 - grosorTrazo), y: by + h / 3 - i * h / 3 + t });
        }
      }
    },
    'N': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      for (let i = 0; i <= 1; i += 0.025) {
        for (let t = 0; t < grosorTrazo; t += 3) {
          puntos.push({ x: bx + grosorTrazo + i * (w - grosorTrazo * 2), y: by + i * h + t });
        }
      }
    },
    'O': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    'P': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h / 2, w * 0.8);
      barraVertical(bx + w - grosorTrazo, by, h / 2);
    },
    'Q': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h - grosorTrazo, w);
      for (let i = 0; i <= 1; i += 0.05) {
        for (let t = 0; t < grosorTrazo / 2; t += 3) {
          puntos.push({ x: bx + w * 0.5 + i * w * 0.5, y: by + h * 0.7 + i * h * 0.3 });
        }
      }
    },
    'R': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h / 2, w * 0.8);
      barraVertical(bx + w - grosorTrazo, by, h / 2);
      for (let i = 0; i <= 1; i += 0.03) {
        for (let t = 0; t < grosorTrazo; t += 3) {
          puntos.push({ x: bx + grosorTrazo + i * (w - grosorTrazo), y: by + h / 2 + i * h / 2 - t });
        }
      }
    },
    'S': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx, by, h / 2);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w);
      barraVertical(bx + w - grosorTrazo, by + h / 2, h / 2);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    'T': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx + w / 2 - grosorTrazo / 2, by, h);
    },
    'U': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    'V': (bx, by, w, h) => {
      for (let i = 0; i <= 1; i += 0.025) {
        for (let t = 0; t < grosorTrazo; t += 3) {
          puntos.push({ x: bx + i * w / 2, y: by + i * h + t });
          puntos.push({ x: bx + w - i * w / 2, y: by + i * h + t });
        }
      }
    },
    'W': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraVertical(bx + w / 2 - grosorTrazo / 2, by + h / 3, h * 2 / 3);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    'X': (bx, by, w, h) => {
      for (let i = 0; i <= 1; i += 0.025) {
        for (let t = 0; t < grosorTrazo; t += 3) {
          puntos.push({ x: bx + i * w, y: by + i * h });
          puntos.push({ x: bx + w - i * w, y: by + i * h });
        }
      }
    },
    'Y': (bx, by, w, h) => {
      for (let i = 0; i <= 1; i += 0.03) {
        for (let t = 0; t < grosorTrazo; t += 3) {
          puntos.push({ x: bx + i * w / 2, y: by + i * h / 2 + t });
          puntos.push({ x: bx + w - i * w / 2, y: by + i * h / 2 + t });
        }
      }
      barraVertical(bx + w / 2 - grosorTrazo / 2, by + h / 2, h / 2);
    },
    'Z': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      for (let i = 0; i <= 1; i += 0.025) {
        for (let t = 0; t < grosorTrazo; t += 3) {
          puntos.push({ x: bx + w - i * w, y: by + i * h });
        }
      }
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    '0': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    '1': (bx, by, w, h) => {
      barraVertical(bx + w / 2 - grosorTrazo / 2, by, h);
      barraHorizontal(bx, by + h - grosorTrazo, w);
      for (let i = 0; i <= 1; i += 0.05) {
        for (let t = 0; t < grosorTrazo; t += 3) {
          puntos.push({ x: bx + w * 0.15 + i * (w / 2 - w * 0.15), y: by + (1 - i) * h * 0.2 + t });
        }
      }
    },
    '2': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx + w - grosorTrazo, by, h / 2);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w);
      barraVertical(bx, by + h / 2, h / 2);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    '3': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraHorizontal(bx + w / 4, by + h / 2 - grosorTrazo / 2, w * 3 / 4);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    '4': (bx, by, w, h) => {
      barraVertical(bx, by, h / 2);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w);
      barraVertical(bx + w - grosorTrazo, by, h);
    },
    '5': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx, by, h / 2);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w);
      barraVertical(bx + w - grosorTrazo, by + h / 2, h / 2);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    '6': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx, by, h);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w);
      barraVertical(bx + w - grosorTrazo, by + h / 2, h / 2);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    '7': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx + w - grosorTrazo, by, h);
    },
    '8': (bx, by, w, h) => {
      barraVertical(bx, by, h);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraHorizontal(bx, by, w);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    '9': (bx, by, w, h) => {
      barraHorizontal(bx, by, w);
      barraVertical(bx, by, h / 2);
      barraHorizontal(bx, by + h / 2 - grosorTrazo / 2, w);
      barraVertical(bx + w - grosorTrazo, by, h);
      barraHorizontal(bx, by + h - grosorTrazo, w);
    },
    ' ': () => {},
  };
  
  texto.split('').forEach((caracter, indice) => {
    const baseX = inicioX + indice * (anchoCaracter + espaciadoLetras);
    const dibujar = dibujarLetra[caracter.toUpperCase()];
    if (dibujar) {
      dibujar(baseX, inicioY, anchoCaracter, altoCaracter);
    }
  });
  
  return puntos;
}

// Distribuir puntos para alcanzar la cantidad de drones
function distribuirPuntos(
  puntosBase: { x: number; y: number; color: string }[],
  cantidadObjetivo: number
): { x: number; y: number; color: string }[] {
  if (puntosBase.length === 0) {
    const resultado: { x: number; y: number; color: string }[] = [];
    const columnas = Math.ceil(Math.sqrt(cantidadObjetivo * ANCHO_CANVAS / ALTO_CANVAS));
    const filas = Math.ceil(cantidadObjetivo / columnas);
    for (let i = 0; i < cantidadObjetivo; i++) {
      const col = i % columnas;
      const fila = Math.floor(i / columnas);
      resultado.push({
        x: 50 + (col / columnas) * (ANCHO_CANVAS - 100),
        y: 50 + (fila / filas) * (ALTO_CANVAS - 100),
        color: COLORES.blanco,
      });
    }
    return resultado;
  }
  
  if (puntosBase.length >= cantidadObjetivo) {
    const paso = puntosBase.length / cantidadObjetivo;
    const resultado: { x: number; y: number; color: string }[] = [];
    for (let i = 0; i < cantidadObjetivo; i++) {
      resultado.push(puntosBase[Math.floor(i * paso)]);
    }
    return resultado;
  }
  
  const resultado: { x: number; y: number; color: string }[] = [...puntosBase];
  let indice = 0;
  while (resultado.length < cantidadObjetivo) {
    const base = puntosBase[indice % puntosBase.length];
    const angulo = (resultado.length * 137.5) * Math.PI / 180;
    const radio = 1 + (resultado.length % 3) * 0.8;
    resultado.push({
      x: base.x + Math.cos(angulo) * radio,
      y: base.y + Math.sin(angulo) * radio,
      color: base.color,
    });
    indice++;
  }
  
  return resultado.slice(0, cantidadObjetivo);
}

// Generar estrellas de 5 puntas con esquinas afiladas
function generarPatronEstrellas(): { x: number; y: number; color: string }[] {
  const puntos: { x: number; y: number; color: string }[] = [];
  
  const configuraciones = [
    { cx: ANCHO_CANVAS / 2, cy: ALTO_CANVAS / 2, tamano: 160, color: COLORES.dorado },
    { cx: 200, cy: 160, tamano: 80, color: COLORES.cian },
    { cx: ANCHO_CANVAS - 200, cy: 160, tamano: 80, color: COLORES.magenta },
    { cx: 200, cy: ALTO_CANVAS - 160, tamano: 80, color: COLORES.blanco },
    { cx: ANCHO_CANVAS - 200, cy: ALTO_CANVAS - 160, tamano: 80, color: COLORES.naranja },
  ];
  
  configuraciones.forEach(({ cx, cy, tamano, color }) => {
    const radioExterno = tamano;
    const radioInterno = tamano * 0.38;
    const numPuntas = 5;
    
    // Generar vértices de la estrella
    const vertices: { x: number; y: number }[] = [];
    for (let i = 0; i < numPuntas * 2; i++) {
      const angulo = (i * Math.PI) / numPuntas - Math.PI / 2;
      const radio = i % 2 === 0 ? radioExterno : radioInterno;
      vertices.push({
        x: cx + radio * Math.cos(angulo),
        y: cy + radio * Math.sin(angulo),
      });
    }
    
    // Rellenar la estrella con puntos
    for (let i = 0; i < vertices.length; i++) {
      const v1 = vertices[i];
      const v2 = vertices[(i + 1) % vertices.length];
      
      // Líneas desde el centro
      for (let t = 0; t <= 1; t += 0.03) {
        const px = cx + t * (v1.x - cx);
        const py = cy + t * (v1.y - cy);
        for (let w = -3; w <= 3; w += 3) {
          puntos.push({ x: px + w, y: py, color });
        }
      }
      
      // Bordes
      for (let t = 0; t <= 1; t += 0.02) {
        const px = v1.x + t * (v2.x - v1.x);
        const py = v1.y + t * (v2.y - v1.y);
        for (let w = -4; w <= 4; w += 4) {
          puntos.push({ x: px + w, y: py + w * 0.3, color });
        }
      }
    }
    
    // Centro brillante
    for (let r = 0; r < radioInterno * 0.6; r += 5) {
      for (let a = 0; a < Math.PI * 2; a += 0.2) {
        puntos.push({ x: cx + r * Math.cos(a), y: cy + r * Math.sin(a), color });
      }
    }
  });
  
  return puntos;
}

// Generar máscara de Diablada
function generarPatronDiablada(): { x: number; y: number; color: string }[] {
  const puntos: { x: number; y: number; color: string }[] = [];
  const cx = ANCHO_CANVAS / 2;
  const cy = ALTO_CANVAS / 2 + 40;
  
  // Cuernos grandes
  for (let lado = -1; lado <= 1; lado += 2) {
    for (let t = 0; t <= 1; t += 0.008) {
      const anguloCuerno = lado * (0.2 + t * 1.8);
      const largoCuerno = t * 200;
      const baseX = cx + lado * 80;
      const baseY = cy - 120;
      
      const curvaX = Math.sin(anguloCuerno) * largoCuerno + Math.sin(t * Math.PI) * lado * 50;
      const curvaY = -Math.cos(anguloCuerno * 0.6) * largoCuerno * 0.8;
      
      const cuernoX = baseX + curvaX;
      const cuernoY = baseY + curvaY;
      
      const grosor = 20 * (1 - t * 0.7);
      for (let w = -grosor; w <= grosor; w += 4) {
        puntos.push({
          x: cuernoX + w * 0.5,
          y: cuernoY + w * 0.3,
          color: t < 0.3 ? COLORES.rojo : (t < 0.7 ? COLORES.dorado : COLORES.naranja),
        });
      }
    }
    
    // Rizos secundarios
    for (let t = 0; t <= 0.8; t += 0.012) {
      const baseX = cx + lado * 160;
      const baseY = cy - 180;
      const angulo = lado * (1 + t * 2);
      const largo = t * 80;
      
      const hx = baseX + Math.sin(angulo) * largo;
      const hy = baseY - Math.cos(angulo) * largo * 0.5;
      
      for (let w = -8; w <= 8; w += 4) {
        puntos.push({ x: hx + w, y: hy, color: COLORES.dorado });
      }
    }
  }
  
  // Rostro
  for (let angulo = 0; angulo < Math.PI * 2; angulo += 0.02) {
    const radioRostro = 130;
    const variacion = Math.sin(angulo * 8) * 8;
    const r = radioRostro + variacion;
    
    for (let anillo = 0.3; anillo <= 1; anillo += 0.05) {
      const px = cx + r * anillo * Math.cos(angulo);
      const py = cy + r * anillo * 0.9 * Math.sin(angulo);
      puntos.push({
        x: px,
        y: py,
        color: anillo > 0.9 ? COLORES.dorado : (anillo > 0.7 ? COLORES.rojoOscuro : COLORES.rojo),
      });
    }
  }
  
  // Ojos
  for (let lado = -1; lado <= 1; lado += 2) {
    const ojoCx = cx + lado * 50;
    const ojoCy = cy - 20;
    
    for (let anillo = 0; anillo < 25; anillo += 3) {
      for (let angulo = 0; angulo < Math.PI * 2; angulo += 0.2) {
        puntos.push({
          x: ojoCx + anillo * Math.cos(angulo) * 1.3,
          y: ojoCy + anillo * Math.sin(angulo),
          color: anillo < 12 ? COLORES.cian : COLORES.blanco,
        });
      }
    }
    
    for (let anillo = 0; anillo < 8; anillo += 3) {
      for (let angulo = 0; angulo < Math.PI * 2; angulo += 0.3) {
        puntos.push({
          x: ojoCx + anillo * Math.cos(angulo),
          y: ojoCy + anillo * Math.sin(angulo),
          color: COLORES.azulClaro,
        });
      }
    }
  }
  
  // Nariz
  for (let y = 10; y < 60; y += 5) {
    const anchoNariz = 8 + (y / 60) * 15;
    for (let x = -anchoNariz; x <= anchoNariz; x += 5) {
      puntos.push({ x: cx + x, y: cy + y, color: COLORES.naranja });
    }
  }
  
  // Boca con colmillos
  for (let x = -70; x <= 70; x += 5) {
    const curva = Math.sin((x + 70) / 140 * Math.PI) * 20;
    for (let t = 0; t < 15; t += 5) {
      puntos.push({
        x: cx + x,
        y: cy + 85 + curva + t,
        color: t < 5 ? COLORES.blanco : COLORES.rojoOscuro,
      });
    }
  }
  
  // Colmillos grandes
  for (let lado = -1; lado <= 1; lado += 2) {
    for (let y = 0; y < 50; y += 4) {
      const anchoColmillo = 12 - y * 0.2;
      for (let x = -anchoColmillo; x <= anchoColmillo; x += 4) {
        puntos.push({ x: cx + lado * 30 + x, y: cy + 95 + y, color: COLORES.blanco });
      }
    }
  }
  
  // Colmillos laterales
  for (let lado = -1; lado <= 1; lado += 2) {
    for (let y = 0; y < 30; y += 5) {
      const anchoColmillo = 6 - y * 0.15;
      for (let x = -anchoColmillo; x <= anchoColmillo; x += 4) {
        puntos.push({ x: cx + lado * 60 + x, y: cy + 100 + y, color: COLORES.blanco });
      }
    }
  }
  
  // Corona decorativa
  for (let i = 0; i < 9; i++) {
    const angulo = -Math.PI / 2 + (i - 4) * 0.2;
    const altura = i % 2 === 0 ? 35 : 20;
    for (let r = 0; r < altura; r += 5) {
      puntos.push({
        x: cx + (125 + r) * Math.cos(angulo),
        y: cy - 80 + (125 + r) * Math.sin(angulo) * 0.4,
        color: i % 2 === 0 ? COLORES.dorado : COLORES.magenta,
      });
    }
  }
  
  // Puntos decorativos en mejillas
  for (let lado = -1; lado <= 1; lado += 2) {
    for (let fila = 0; fila < 4; fila++) {
      for (let i = 0; i < 3; i++) {
        const dx = cx + lado * (95 + i * 10);
        const dy = cy + 10 + fila * 18;
        for (let r = 0; r < 5; r += 2) {
          for (let a = 0; a < Math.PI * 2; a += 0.5) {
            puntos.push({
              x: dx + r * Math.cos(a),
              y: dy + r * Math.sin(a),
              color: fila % 2 === 0 ? COLORES.dorado : COLORES.cian,
            });
          }
        }
      }
    }
  }
  
  return puntos;
}

// Generar patrón de la Virgen de la Candelaria
function generarPatronVirgen(): { x: number; y: number; color: string }[] {
  const puntos: { x: number; y: number; color: string }[] = [];
  const cx = ANCHO_CANVAS / 2;
  const cy = ALTO_CANVAS / 2;
  
  // Aureola radiante
  for (let rayo = 0; rayo < 32; rayo++) {
    const angulo = (rayo / 32) * Math.PI * 2 - Math.PI / 2;
    for (let r = 50; r < 110; r += 4) {
      if (rayo % 2 === 0 || r < 80) {
        puntos.push({
          x: cx + r * Math.cos(angulo),
          y: cy - 160 + r * Math.sin(angulo) * 0.5,
          color: COLORES.dorado,
        });
      }
    }
  }
  
  // Cabeza
  for (let anillo = 0; anillo <= 1; anillo += 0.08) {
    for (let angulo = 0; angulo < Math.PI * 2; angulo += 0.1) {
      puntos.push({
        x: cx + 30 * anillo * Math.cos(angulo),
        y: cy - 160 + 35 * anillo * Math.sin(angulo),
        color: anillo < 0.6 ? COLORES.rosa : COLORES.blanco,
      });
    }
  }
  
  // Corona
  for (let i = 0; i < 9; i++) {
    const coronaX = cx - 35 + i * 8.75;
    const altura = i % 2 === 0 ? 30 : 18;
    for (let y = 0; y < altura; y += 4) {
      puntos.push({ x: coronaX, y: cy - 200 - y, color: COLORES.dorado });
    }
  }
  
  // Manto
  for (let y = 0; y < 280; y += 5) {
    const anchoManto = 50 + y * 0.65;
    const onda = Math.sin(y * 0.04) * 8;
    
    for (let x = -anchoManto; x <= anchoManto; x += 7) {
      const profundidad = Math.abs(x) / anchoManto;
      let color = COLORES.azul;
      if (y < 60) color = COLORES.cian;
      else if (profundidad > 0.75) color = COLORES.cian;
      
      puntos.push({
        x: cx + x + onda * (1 - profundidad),
        y: cy - 110 + y,
        color,
      });
    }
  }
  
  // Niño Jesús
  for (let anillo = 0; anillo <= 1; anillo += 0.12) {
    for (let angulo = 0; angulo < Math.PI * 2; angulo += 0.15) {
      puntos.push({
        x: cx - 45 + 18 * anillo * Math.cos(angulo),
        y: cy - 10 + 22 * anillo * Math.sin(angulo),
        color: COLORES.rosa,
      });
    }
  }
  
  // Vela
  for (let y = 0; y < 90; y += 5) {
    for (let x = -5; x <= 5; x += 5) {
      puntos.push({ x: cx + 95 + x, y: cy - 30 + y, color: COLORES.blanco });
    }
  }
  
  // Llama
  for (let y = 0; y < 35; y += 4) {
    const anchoLlama = 10 - y * 0.25;
    for (let x = -anchoLlama; x <= anchoLlama; x += 5) {
      puntos.push({
        x: cx + 95 + x,
        y: cy - 35 - y,
        color: y < 18 ? COLORES.naranja : COLORES.dorado,
      });
    }
  }
  
  return puntos;
}

// Generar patrón de la Torre Eiffel
function generarPatronTorreEiffel(): { x: number; y: number; color: string }[] {
  const puntos: { x: number; y: number; color: string }[] = [];
  const cx = ANCHO_CANVAS / 2;
  const baseY = ALTO_CANVAS - 40;
  const altura = 550;
  
  // Estructura principal
  for (let y = 0; y < altura; y += 5) {
    const t = y / altura;
    const ancho = 160 * (1 - t * 0.92);
    
    for (let grosor = -10; grosor <= 10; grosor += 5) {
      puntos.push({ x: cx - ancho + grosor, y: baseY - y, color: COLORES.dorado });
      puntos.push({ x: cx + ancho + grosor, y: baseY - y, color: COLORES.dorado });
    }
    
    if (y % 25 < 5) {
      for (let x = -ancho + 15; x < ancho - 15; x += 10) {
        puntos.push({ x: cx + x, y: baseY - y, color: COLORES.naranja });
      }
    }
  }
  
  // Plataformas de observación
  const nivelesPlataforma = [0.22, 0.48, 0.75];
  nivelesPlataforma.forEach((nivel, idx) => {
    const plataformaY = baseY - altura * nivel;
    const anchoPlataforma = 160 * (1 - nivel * 0.92) + 30;
    
    for (let x = -anchoPlataforma; x <= anchoPlataforma; x += 8) {
      for (let t = 0; t < 4; t++) {
        puntos.push({
          x: cx + x,
          y: plataformaY + t * 4,
          color: idx === 1 ? COLORES.cian : COLORES.naranja,
        });
      }
    }
  });
  
  // Antena superior
  for (let y = 0; y < 45; y += 4) {
    for (let x = -3; x <= 3; x += 3) {
      puntos.push({ x: cx + x, y: baseY - altura - y, color: COLORES.cian });
    }
  }
  
  // Luz en la cima
  for (let anillo = 0; anillo < 4; anillo++) {
    for (let angulo = 0; angulo < Math.PI * 2; angulo += 0.25) {
      puntos.push({
        x: cx + (6 + anillo * 4) * Math.cos(angulo),
        y: baseY - altura - 45 + (6 + anillo * 4) * Math.sin(angulo),
        color: COLORES.blanco,
      });
    }
  }
  
  // Arcos de la base
  for (let lado = -1; lado <= 1; lado += 2) {
    for (let angulo = 0; angulo < Math.PI; angulo += 0.06) {
      const radioArco = 55;
      for (let t = 0; t < 6; t += 3) {
        puntos.push({
          x: cx + lado * 80 + (radioArco - t) * Math.cos(angulo),
          y: baseY - 25 - (radioArco - t) * Math.sin(angulo) * 0.7,
          color: COLORES.dorado,
        });
      }
    }
  }
  
  return puntos;
}

// Generar patrón CANDELARIA 2026
function generarPatronCandelaria2026(): { x: number; y: number; color: string }[] {
  const puntos: { x: number; y: number; color: string }[] = [];
  
  // "CANDELARIA" arriba
  const textoSuperior = generarPuntosTexto('CANDELARIA', 8);
  const escalaSuperior = 0.5;
  const desplazamientoY_Superior = -110;
  textoSuperior.forEach(p => {
    const escaladoX = ANCHO_CANVAS / 2 + (p.x - ANCHO_CANVAS / 2) * escalaSuperior;
    const escaladoY = ALTO_CANVAS / 2 + (p.y - ALTO_CANVAS / 2) * escalaSuperior + desplazamientoY_Superior;
    puntos.push({ x: escaladoX, y: escaladoY, color: COLORES.cian });
  });
  
  // "2026" abajo, más grande
  const textoInferior = generarPuntosTexto('2026', 35);
  const escalaInferior = 0.85;
  const desplazamientoY_Inferior = 80;
  textoInferior.forEach(p => {
    const escaladoX = ANCHO_CANVAS / 2 + (p.x - ANCHO_CANVAS / 2) * escalaInferior;
    const escaladoY = ALTO_CANVAS / 2 + (p.y - ALTO_CANVAS / 2) * escalaInferior + desplazamientoY_Inferior;
    puntos.push({ x: escaladoX, y: escaladoY, color: COLORES.dorado });
  });
  
  // Estrellas decorativas en las esquinas
  const posicionesEstrellas = [
    { x: 150, y: 120 },
    { x: ANCHO_CANVAS - 150, y: 120 },
    { x: 150, y: ALTO_CANVAS - 120 },
    { x: ANCHO_CANVAS - 150, y: ALTO_CANVAS - 120 },
  ];
  
  posicionesEstrellas.forEach(({ x: sx, y: sy }) => {
    for (let i = 0; i < 5; i++) {
      const angulo = (i * Math.PI * 2) / 5 - Math.PI / 2;
      const radioExterno = 25;
      const radioInterno = 10;
      
      for (let t = 0; t <= 1; t += 0.1) {
        puntos.push({
          x: sx + radioExterno * Math.cos(angulo) * t,
          y: sy + radioExterno * Math.sin(angulo) * t,
          color: COLORES.magenta,
        });
      }
      
      const siguienteAngulo = ((i + 0.5) * Math.PI * 2) / 5 - Math.PI / 2;
      for (let t = 0; t <= 1; t += 0.1) {
        puntos.push({
          x: sx + radioInterno * Math.cos(siguienteAngulo) * t,
          y: sy + radioInterno * Math.sin(siguienteAngulo) * t,
          color: COLORES.magenta,
        });
      }
    }
  });
  
  return puntos;
}

// Generador principal de formaciones
export function generarFormacion(
  tipoFormacion: string,
  cantidadDrones: number = CANTIDAD_DRONES
): { x: number; y: number; color: string }[] {
  let puntosBase: { x: number; y: number; color: string }[] = [];
  
  switch (tipoFormacion) {
    case 'PUNO_SE_RESPETA':
      puntosBase = generarPuntosTexto('PUNO SE RESPETA', 15).map(p => ({
        ...p,
        color: COLORES.dorado,
      }));
      break;
      
    case 'SISTEMAS_UNAP':
      puntosBase = generarPuntosTexto('SISTEMAS UNAP', 15).map(p => ({
        ...p,
        color: COLORES.cian,
      }));
      break;
      
    case 'EPIS':
      puntosBase = generarPuntosTexto('EPIS', 40).map(p => ({
        ...p,
        color: COLORES.magenta,
      }));
      break;
      
    case 'DIABLADA':
      puntosBase = generarPatronDiablada();
      break;
      
    case 'VIRGEN':
      puntosBase = generarPatronVirgen();
      break;
      
    case 'ESTRELLAS':
      puntosBase = generarPatronEstrellas();
      break;
      
    case 'TORRE_EIFFEL':
      puntosBase = generarPatronTorreEiffel();
      break;
      
    case '2026':
      puntosBase = generarPatronCandelaria2026();
      break;
      
    default:
      for (let i = 0; i < cantidadDrones; i++) {
        const columnas = Math.ceil(Math.sqrt(cantidadDrones));
        const fila = Math.floor(i / columnas);
        const col = i % columnas;
        puntosBase.push({
          x: 100 + (col / columnas) * (ANCHO_CANVAS - 200),
          y: 100 + (fila / Math.ceil(cantidadDrones / columnas)) * (ALTO_CANVAS - 200),
          color: COLORES.blanco,
        });
      }
  }
  
  return distribuirPuntos(puntosBase, cantidadDrones);
}

export { COLORES, ANCHO_CANVAS, ALTO_CANVAS, CANTIDAD_DRONES };
