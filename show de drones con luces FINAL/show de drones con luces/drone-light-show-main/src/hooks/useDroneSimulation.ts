import { useState, useEffect, useCallback, useRef } from 'react';
import { Drone } from '@/types/drone';
import { generarFormacion, CANTIDAD_DRONES, ANCHO_CANVAS, ALTO_CANVAS } from '@/utils/formaciones';
import { lerp, lerpColor, buildProximityGraph } from '@/utils/droneGraph';

// Radio de colisión base - espacio personal de cada drone
const RADIO_COLISION_BASE = 16;
// Distancia mínima de seguridad entre drones
const DISTANCIA_SEGURIDAD_BASE = RADIO_COLISION_BASE * 2;
// Distancia al objetivo donde se reduce la colisión para permitir formación final
const UMBRAL_FORMACION_FINAL = 30;

export function useDroneSimulation(formacionInicial: string = 'ESTRELLAS') {
  const [drones, setDrones] = useState<Drone[]>([]);
  const [formacionActiva, setFormacionActiva] = useState(formacionInicial);
  const [enTransicion, setEnTransicion] = useState(false);
  const [progresoTransicion, setProgresoTransicion] = useState(100);
  const [cantidadAristas, setCantidadAristas] = useState(0);
  const [fps, setFps] = useState(60);
  const [velocidadTransicion, setVelocidadTransicion] = useState(1); // 0.5 a 3
  
  const refAnimacion = useRef<number>();
  const tiempoUltimoFrame = useRef<number>(0);
  const contadorFrames = useRef<number>(0);
  const ultimaActualizacionFps = useRef<number>(0);

  // Calcular distancia entre dos puntos
  const calcularDistancia = (x1: number, y1: number, x2: number, y2: number): number => {
    return Math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2);
  };

  // Detectar colisiones con radio dinámico basado en cercanía al objetivo
  const detectarColisiones = (
    droneActual: Drone,
    nuevaX: number,
    nuevaY: number,
    todosDrones: Drone[],
    distanciaAlObjetivo: number
  ): { colisiona: boolean; vectorEvasion: { x: number; y: number }; dronesEnConflicto: number } => {
    let vectorEvasion = { x: 0, y: 0 };
    let dronesEnConflicto = 0;
    
    // Reducir radio de colisión cuando el drone está cerca de su objetivo
    // Esto permite que las formaciones finales se completen
    const factorReduccion = distanciaAlObjetivo < UMBRAL_FORMACION_FINAL 
      ? Math.max(0.1, distanciaAlObjetivo / UMBRAL_FORMACION_FINAL)
      : 1;
    
    const distanciaSeguridad = DISTANCIA_SEGURIDAD_BASE * factorReduccion;
    
    for (const otroDrone of todosDrones) {
      if (otroDrone.id === droneActual.id) continue;
      
      const distancia = calcularDistancia(nuevaX, nuevaY, otroDrone.x, otroDrone.y);
      
      // También considerar si el otro drone está cerca de su objetivo
      const distOtroAlObjetivo = calcularDistancia(otroDrone.x, otroDrone.y, otroDrone.targetX, otroDrone.targetY);
      const factorOtro = distOtroAlObjetivo < UMBRAL_FORMACION_FINAL 
        ? Math.max(0.1, distOtroAlObjetivo / UMBRAL_FORMACION_FINAL)
        : 1;
      
      const distanciaSeguridadEfectiva = distanciaSeguridad * Math.min(1, (factorReduccion + factorOtro) / 2);
      
      if (distancia < distanciaSeguridadEfectiva && distancia > 0.1) {
        dronesEnConflicto++;
        
        const dx = nuevaX - otroDrone.x;
        const dy = nuevaY - otroDrone.y;
        const magnitud = Math.max(distancia, 0.01);
        
        const fuerzaRepulsion = (distanciaSeguridadEfectiva - distancia) / distanciaSeguridadEfectiva;
        
        vectorEvasion.x += (dx / magnitud) * fuerzaRepulsion * RADIO_COLISION_BASE * factorReduccion;
        vectorEvasion.y += (dy / magnitud) * fuerzaRepulsion * RADIO_COLISION_BASE * factorReduccion;
      }
    }
    
    return { 
      colisiona: dronesEnConflicto > 0, 
      vectorEvasion, 
      dronesEnConflicto 
    };
  };

  // Inicializar drones
  useEffect(() => {
    const posicionesIniciales = generarFormacion('RANDOM', CANTIDAD_DRONES);
    const dronesIniciales: Drone[] = posicionesIniciales.map((pos, indice) => ({
      id: indice,
      x: pos.x,
      y: pos.y,
      targetX: pos.x,
      targetY: pos.y,
      color: pos.color,
      targetColor: pos.color,
      size: 2,
    }));
    setDrones(dronesIniciales);
    
    setTimeout(() => {
      cambiarFormacion(formacionInicial);
    }, 500);
  }, []);

  const cambiarFormacion = useCallback((tipoFormacion: string) => {
    const posicionesObjetivo = generarFormacion(tipoFormacion, CANTIDAD_DRONES);
    
    setDrones(dronesAnteriores => 
      dronesAnteriores.map((drone, indice) => ({
        ...drone,
        targetX: posicionesObjetivo[indice]?.x ?? drone.x,
        targetY: posicionesObjetivo[indice]?.y ?? drone.y,
        targetColor: posicionesObjetivo[indice]?.color ?? drone.color,
      }))
    );
    
    setFormacionActiva(tipoFormacion);
    setEnTransicion(true);
    setProgresoTransicion(0);
  }, []);

  // Bucle de animación
  useEffect(() => {
    const animar = (tiempoActual: number) => {
      contadorFrames.current++;
      if (tiempoActual - ultimaActualizacionFps.current >= 1000) {
        setFps(contadorFrames.current);
        contadorFrames.current = 0;
        ultimaActualizacionFps.current = tiempoActual;
      }
      
      tiempoUltimoFrame.current = tiempoActual;
      
      setDrones(dronesAnteriores => {
        let distanciaMaxima = 0;
        let sumatoriaDistancias = 0;
        const velocidadBase = 0.008 * velocidadTransicion;
        
        // Ordenar por distancia al objetivo
        const indicesOrdenados = dronesAnteriores
          .map((drone, idx) => ({
            idx,
            distancia: calcularDistancia(drone.x, drone.y, drone.targetX, drone.targetY)
          }))
          .sort((a, b) => a.distancia - b.distancia)
          .map(item => item.idx);
        
        const dronesActualizados = [...dronesAnteriores];
        
        for (const idx of indicesOrdenados) {
          const drone = dronesActualizados[idx];
          const dx = drone.targetX - drone.x;
          const dy = drone.targetY - drone.y;
          const distAlObjetivo = Math.sqrt(dx * dx + dy * dy);
          
          distanciaMaxima = Math.max(distanciaMaxima, distAlObjetivo);
          sumatoriaDistancias += distAlObjetivo;
          
          if (distAlObjetivo > 0.3) {
            // Velocidad adaptativa: más rápido cuando está lejos, más preciso cuando está cerca
            const factorVelocidad = distAlObjetivo > 50 ? velocidadBase * 1.5 : velocidadBase;
            
            let nuevaX = lerp(drone.x, drone.targetX, factorVelocidad);
            let nuevaY = lerp(drone.y, drone.targetY, factorVelocidad);
            
            // Solo aplicar colisión si no está muy cerca del objetivo
            if (distAlObjetivo > 5) {
              const { colisiona, vectorEvasion, dronesEnConflicto } = detectarColisiones(
                drone,
                nuevaX,
                nuevaY,
                dronesActualizados,
                distAlObjetivo
              );
              
              if (colisiona) {
                nuevaX += vectorEvasion.x * 0.4;
                nuevaY += vectorEvasion.y * 0.4;
                
                nuevaX = Math.max(15, Math.min(ANCHO_CANVAS - 15, nuevaX));
                nuevaY = Math.max(15, Math.min(ALTO_CANVAS - 15, nuevaY));
                
                const verificacion = detectarColisiones(drone, nuevaX, nuevaY, dronesActualizados, distAlObjetivo);
                
                if (verificacion.colisiona && verificacion.dronesEnConflicto >= dronesEnConflicto) {
                  const factorEspera = Math.max(0.002, 0.006 / (dronesEnConflicto + 1)) * velocidadTransicion;
                  nuevaX = drone.x + dx * factorEspera;
                  nuevaY = drone.y + dy * factorEspera;
                  
                  const angulo = Math.atan2(dy, dx) + Math.PI / 2;
                  nuevaX += Math.cos(angulo) * 0.2;
                  nuevaY += Math.sin(angulo) * 0.2;
                }
              }
            }
            
            dronesActualizados[idx] = {
              ...drone,
              x: nuevaX,
              y: nuevaY,
              color: lerpColor(drone.color, drone.targetColor, factorVelocidad),
            };
          } else {
            // Snap al objetivo cuando está muy cerca
            dronesActualizados[idx] = {
              ...drone,
              x: drone.targetX,
              y: drone.targetY,
              color: drone.targetColor,
            };
          }
        }
        
        // Calcular progreso basado en promedio de distancias
        const distanciaPromedio = sumatoriaDistancias / dronesAnteriores.length;
        const progreso = Math.max(0, Math.min(100, 100 - (distanciaPromedio / 3)));
        setProgresoTransicion(progreso);
        
        // Verificar si todos llegaron
        const todosLlegaron = distanciaMaxima < 1;
        if (todosLlegaron && enTransicion) {
          setEnTransicion(false);
          setProgresoTransicion(100);
        }
        
        return dronesActualizados;
      });
      
      if (contadorFrames.current % 15 === 0) {
        setDrones(dronesAnteriores => {
          const aristas = buildProximityGraph(dronesAnteriores);
          setCantidadAristas(aristas.length);
          return dronesAnteriores;
        });
      }
      
      refAnimacion.current = requestAnimationFrame(animar);
    };
    
    refAnimacion.current = requestAnimationFrame(animar);
    
    return () => {
      if (refAnimacion.current) {
        cancelAnimationFrame(refAnimacion.current);
      }
    };
  }, [enTransicion, velocidadTransicion]);

  return {
    drones,
    activeFormation: formacionActiva,
    isTransitioning: enTransicion,
    transitionProgress: progresoTransicion,
    edgeCount: cantidadAristas,
    fps,
    changeFormation: cambiarFormacion,
    droneCount: CANTIDAD_DRONES,
    canvasWidth: ANCHO_CANVAS,
    canvasHeight: ALTO_CANVAS,
    velocidadTransicion,
    setVelocidadTransicion,
  };
}
