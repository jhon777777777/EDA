export interface Drone {
  id: number;
  x: number;
  y: number;
  targetX: number;
  targetY: number;
  color: string;
  targetColor: string;
  size: number;
}

export interface DroneEdge {
  from: number;
  to: number;
  distance: number;
}

export interface Formation {
  id: string;
  name: string;
  nameEs: string;
  icon: string;
  positions: { x: number; y: number; color: string }[];
}

export type FormationType = 
  | 'PUNO_SE_RESPETA'
  | 'SISTEMAS_UNAP'
  | 'EPIS'
  | 'DIABLADA'
  | 'VIRGEN'
  | 'ESTRELLAS'
  | 'TORRE_EIFFEL'
  | '2026';
