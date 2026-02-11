import React, { useRef, useEffect, useCallback, useState } from 'react';
import { Drone, DroneEdge } from '@/types/drone';
import { buildProximityGraph, PROXIMITY_THRESHOLD } from '@/utils/droneGraph';
import { ZoomIn, ZoomOut, RotateCcw } from 'lucide-react';

interface DroneCanvasProps {
  drones: Drone[];
  showGraph: boolean;
  width: number;
  height: number;
}

const DroneCanvas: React.FC<DroneCanvasProps> = ({ drones, showGraph, width, height }) => {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const edgesRef = useRef<DroneEdge[]>([]);
  const [zoom, setZoom] = useState(1);
  const [panOffset, setPanOffset] = useState({ x: 0, y: 0 });
  const [isDragging, setIsDragging] = useState(false);
  const lastMousePos = useRef({ x: 0, y: 0 });

  const handleZoomIn = () => setZoom(prev => Math.min(prev * 1.3, 5));
  const handleZoomOut = () => setZoom(prev => Math.max(prev / 1.3, 0.5));
  const handleReset = () => {
    setZoom(1);
    setPanOffset({ x: 0, y: 0 });
  };

  const handleMouseDown = (e: React.MouseEvent) => {
    setIsDragging(true);
    lastMousePos.current = { x: e.clientX, y: e.clientY };
  };

  const handleMouseMove = (e: React.MouseEvent) => {
    if (!isDragging) return;
    const dx = e.clientX - lastMousePos.current.x;
    const dy = e.clientY - lastMousePos.current.y;
    setPanOffset(prev => ({ x: prev.x + dx, y: prev.y + dy }));
    lastMousePos.current = { x: e.clientX, y: e.clientY };
  };

  const handleMouseUp = () => setIsDragging(false);

  const handleWheel = (e: React.WheelEvent) => {
    e.preventDefault();
    if (e.deltaY < 0) {
      setZoom(prev => Math.min(prev * 1.1, 5));
    } else {
      setZoom(prev => Math.max(prev / 1.1, 0.5));
    }
  };

  const drawDrone = useCallback((
    ctx: CanvasRenderingContext2D,
    drone: Drone,
    scale: number
  ) => {
    const { x, y, color, size } = drone;
    const scaledSize = size * Math.max(1, scale * 0.7);
    
    // Outer glow
    const gradient = ctx.createRadialGradient(x, y, 0, x, y, scaledSize * 4);
    gradient.addColorStop(0, color);
    gradient.addColorStop(0.3, color + '80');
    gradient.addColorStop(0.6, color + '30');
    gradient.addColorStop(1, 'transparent');
    
    ctx.beginPath();
    ctx.arc(x, y, scaledSize * 4, 0, Math.PI * 2);
    ctx.fillStyle = gradient;
    ctx.fill();
    
    // Core bright spot
    ctx.beginPath();
    ctx.arc(x, y, scaledSize, 0, Math.PI * 2);
    ctx.fillStyle = '#FFFFFF';
    ctx.fill();
    
    // Colored ring
    ctx.beginPath();
    ctx.arc(x, y, scaledSize * 1.5, 0, Math.PI * 2);
    ctx.strokeStyle = color;
    ctx.lineWidth = 1;
    ctx.stroke();
  }, []);

  const drawEdge = useCallback((
    ctx: CanvasRenderingContext2D,
    edge: DroneEdge,
    drones: Drone[]
  ) => {
    const from = drones[edge.from];
    const to = drones[edge.to];
    
    if (!from || !to) return;
    
    const opacity = Math.max(0.05, 1 - edge.distance / PROXIMITY_THRESHOLD);
    
    ctx.beginPath();
    ctx.moveTo(from.x, from.y);
    ctx.lineTo(to.x, to.y);
    ctx.strokeStyle = `rgba(100, 200, 255, ${opacity * 0.3})`;
    ctx.lineWidth = 0.5;
    ctx.stroke();
  }, []);

  const render = useCallback(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    const ctx = canvas.getContext('2d');
    if (!ctx) return;
    
    // Clear with dark background
    ctx.fillStyle = 'rgba(5, 10, 20, 1)';
    ctx.fillRect(0, 0, width, height);
    
    // Add subtle star field
    ctx.fillStyle = 'rgba(255, 255, 255, 0.3)';
    for (let i = 0; i < 100; i++) {
      const x = (i * 137.5) % width;
      const y = (i * 79.3) % height;
      const size = 0.5 + Math.sin(i) * 0.5;
      ctx.beginPath();
      ctx.arc(x, y, size, 0, Math.PI * 2);
      ctx.fill();
    }
    
    // Apply zoom and pan transformations
    ctx.save();
    ctx.translate(width / 2 + panOffset.x, height / 2 + panOffset.y);
    ctx.scale(zoom, zoom);
    ctx.translate(-width / 2, -height / 2);
    
    // Draw proximity graph edges
    if (showGraph) {
      edgesRef.current = buildProximityGraph(drones);
      edgesRef.current.forEach(edge => drawEdge(ctx, edge, drones));
    }
    
    // Draw drones
    drones.forEach(drone => drawDrone(ctx, drone, zoom));
    
    ctx.restore();
  }, [drones, showGraph, width, height, zoom, panOffset, drawDrone, drawEdge]);

  useEffect(() => {
    render();
  }, [render]);

  return (
    <div className="relative">
      <canvas
        ref={canvasRef}
        width={width}
        height={height}
        className="rounded-xl cursor-grab active:cursor-grabbing"
        style={{ 
          background: 'linear-gradient(180deg, #030810 0%, #0a1525 50%, #0f1a30 100%)',
        }}
        onMouseDown={handleMouseDown}
        onMouseMove={handleMouseMove}
        onMouseUp={handleMouseUp}
        onMouseLeave={handleMouseUp}
        onWheel={handleWheel}
      />
      
      {/* Zoom Controls */}
      <div className="absolute bottom-4 right-4 flex flex-col gap-2">
        <button
          onClick={handleZoomIn}
          className="p-2 bg-background/80 backdrop-blur-sm border border-border rounded-lg hover:bg-muted transition-colors"
          title="Acercar"
        >
          <ZoomIn className="w-5 h-5 text-foreground" />
        </button>
        <button
          onClick={handleZoomOut}
          className="p-2 bg-background/80 backdrop-blur-sm border border-border rounded-lg hover:bg-muted transition-colors"
          title="Alejar"
        >
          <ZoomOut className="w-5 h-5 text-foreground" />
        </button>
        <button
          onClick={handleReset}
          className="p-2 bg-background/80 backdrop-blur-sm border border-border rounded-lg hover:bg-muted transition-colors"
          title="Restablecer"
        >
          <RotateCcw className="w-5 h-5 text-foreground" />
        </button>
      </div>
      
      {/* Zoom indicator */}
      <div className="absolute bottom-4 left-4 px-3 py-1.5 bg-background/80 backdrop-blur-sm border border-border rounded-lg text-xs text-muted-foreground">
        Zoom: {Math.round(zoom * 100)}%
      </div>
    </div>
  );
};

export default DroneCanvas;