export interface Punto {
  x: number;
  y: number;
  clase: number; // 0: Rojo (A), 1: Azul (B), -1: Sin clasificar
}

export interface VecinoConDistancia {
  punto: Punto;
  distancia: number;
}

export function calcularDistanciaEuclidiana(p1: { x: number; y: number }, p2: { x: number; y: number }): number {
  return Math.sqrt((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2);
}

export function obtenerVecinos(puntos: Punto[], puntoNuevo: { x: number; y: number }, k: number): VecinoConDistancia[] {
  const conDistancia: VecinoConDistancia[] = puntos.map((p) => ({
    punto: p,
    distancia: calcularDistanciaEuclidiana(p, puntoNuevo),
  }));

  conDistancia.sort((a, b) => a.distancia - b.distancia);

  return conDistancia.slice(0, k);
}

export function clasificar(puntos: Punto[], puntoNuevo: { x: number; y: number }, k: number): { clase: number; vecinos: VecinoConDistancia[] } {
  const vecinos = obtenerVecinos(puntos, puntoNuevo, k);

  let votosRojo = 0;
  let votosAzul = 0;

  for (const v of vecinos) {
    if (v.punto.clase === 0) votosRojo++;
    else if (v.punto.clase === 1) votosAzul++;
  }

  return {
    clase: votosRojo >= votosAzul ? 0 : 1,
    vecinos,
  };
}
