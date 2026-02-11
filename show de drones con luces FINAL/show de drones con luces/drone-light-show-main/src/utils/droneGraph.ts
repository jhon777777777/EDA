import { Drone, DroneEdge } from '@/types/drone';

// Proximity threshold for connecting drones
const PROXIMITY_THRESHOLD = 60;

// Calculate distance between two points
export function distance(x1: number, y1: number, x2: number, y2: number): number {
  return Math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2);
}

// Build proximity graph - returns edges between nearby drones
export function buildProximityGraph(drones: Drone[], threshold: number = PROXIMITY_THRESHOLD): DroneEdge[] {
  const edges: DroneEdge[] = [];
  
  // Use spatial hashing for performance
  const cellSize = threshold;
  const grid: Map<string, number[]> = new Map();
  
  // Place drones in grid cells
  drones.forEach((drone, index) => {
    const cellX = Math.floor(drone.x / cellSize);
    const cellY = Math.floor(drone.y / cellSize);
    const key = `${cellX},${cellY}`;
    
    if (!grid.has(key)) {
      grid.set(key, []);
    }
    grid.get(key)!.push(index);
  });
  
  // Check each drone against neighbors in adjacent cells
  drones.forEach((drone, i) => {
    const cellX = Math.floor(drone.x / cellSize);
    const cellY = Math.floor(drone.y / cellSize);
    
    // Check 3x3 neighborhood
    for (let dx = -1; dx <= 1; dx++) {
      for (let dy = -1; dy <= 1; dy++) {
        const key = `${cellX + dx},${cellY + dy}`;
        const neighbors = grid.get(key);
        
        if (neighbors) {
          neighbors.forEach(j => {
            if (i < j) { // Avoid duplicate edges
              const d = distance(drone.x, drone.y, drones[j].x, drones[j].y);
              if (d <= threshold && d > 0) {
                edges.push({
                  from: i,
                  to: j,
                  distance: d,
                });
              }
            }
          });
        }
      }
    }
  });
  
  return edges;
}

// Linear interpolation
export function lerp(start: number, end: number, t: number): number {
  return start + (end - start) * t;
}

// Interpolate color (hex format)
export function lerpColor(color1: string, color2: string, t: number): string {
  const c1 = hexToRgb(color1);
  const c2 = hexToRgb(color2);
  
  if (!c1 || !c2) return color1;
  
  const r = Math.round(lerp(c1.r, c2.r, t));
  const g = Math.round(lerp(c1.g, c2.g, t));
  const b = Math.round(lerp(c1.b, c2.b, t));
  
  return rgbToHex(r, g, b);
}

function hexToRgb(hex: string): { r: number; g: number; b: number } | null {
  const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result
    ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16),
      }
    : null;
}

function rgbToHex(r: number, g: number, b: number): string {
  return '#' + [r, g, b].map(x => x.toString(16).padStart(2, '0')).join('');
}

// Ease in-out function for smooth movement
export function easeInOutCubic(t: number): number {
  return t < 0.5
    ? 4 * t * t * t
    : 1 - Math.pow(-2 * t + 2, 3) / 2;
}

// Update drone positions with interpolation
export function updateDrones(
  drones: Drone[],
  progress: number
): Drone[] {
  const easedProgress = easeInOutCubic(progress);
  
  return drones.map(drone => ({
    ...drone,
    x: lerp(drone.x, drone.targetX, easedProgress * 0.1),
    y: lerp(drone.y, drone.targetY, easedProgress * 0.1),
    color: lerpColor(drone.color, drone.targetColor, easedProgress * 0.1),
  }));
}

// Check if drones have reached their targets
export function dronesReachedTarget(drones: Drone[], threshold: number = 1): boolean {
  return drones.every(drone =>
    Math.abs(drone.x - drone.targetX) < threshold &&
    Math.abs(drone.y - drone.targetY) < threshold
  );
}

export { PROXIMITY_THRESHOLD };
