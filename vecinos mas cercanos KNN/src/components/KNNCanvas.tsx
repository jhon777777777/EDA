import { useRef, useEffect, useCallback, useState } from "react";
import type { Punto, VecinoConDistancia } from "@/lib/knn";

interface Props {
  puntos: Punto[];
  testPoint: { x: number; y: number } | null;
  resultado: { clase: number; vecinos: VecinoConDistancia[] } | null;
  onAddPoint: (x: number, y: number, clase: number) => void;
  onSetTestPoint: (x: number, y: number) => void;
  mode: "train" | "test";
}

const PADDING = 40;

export default function KNNCanvas({ puntos, testPoint, resultado, onAddPoint, onSetTestPoint, mode }: Props) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const containerRef = useRef<HTMLDivElement>(null);
  const [size, setSize] = useState({ w: 700, h: 500 });

  // Responsive sizing
  useEffect(() => {
    const container = containerRef.current;
    if (!container) return;
    const obs = new ResizeObserver((entries) => {
      const { width, height } = entries[0].contentRect;
      setSize({ w: Math.floor(width), h: Math.floor(height) });
    });
    obs.observe(container);
    return () => obs.disconnect();
  }, []);

  const centerX = size.w / 2;
  const centerY = size.h / 2;

  // Convert math coords to canvas pixels
  const toCanvas = useCallback(
    (mx: number, my: number): [number, number] => {
      const scale = Math.min((size.w - PADDING * 2) / 20, (size.h - PADDING * 2) / 20);
      return [centerX + mx * scale, centerY - my * scale];
    },
    [size, centerX, centerY]
  );

  // Convert canvas pixels to math coords
  const toMath = useCallback(
    (cx: number, cy: number): [number, number] => {
      const scale = Math.min((size.w - PADDING * 2) / 20, (size.h - PADDING * 2) / 20);
      return [(cx - centerX) / scale, (centerY - cy) / scale];
    },
    [size, centerX, centerY]
  );

  // Draw everything
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    const ctx = canvas.getContext("2d");
    if (!ctx) return;

    canvas.width = size.w * window.devicePixelRatio;
    canvas.height = size.h * window.devicePixelRatio;
    ctx.scale(window.devicePixelRatio, window.devicePixelRatio);

    // Background
    ctx.fillStyle = "hsl(220, 20%, 6%)";
    ctx.fillRect(0, 0, size.w, size.h);

    const scale = Math.min((size.w - PADDING * 2) / 20, (size.h - PADDING * 2) / 20);

    // Grid lines
    ctx.strokeStyle = "hsl(220, 15%, 14%)";
    ctx.lineWidth = 1;
    for (let i = -10; i <= 10; i++) {
      if (i === 0) continue;
      const [gx] = toCanvas(i, 0);
      const [, gy] = toCanvas(0, i);
      ctx.beginPath();
      ctx.moveTo(gx, PADDING);
      ctx.lineTo(gx, size.h - PADDING);
      ctx.stroke();
      ctx.beginPath();
      ctx.moveTo(PADDING, gy);
      ctx.lineTo(size.w - PADDING, gy);
      ctx.stroke();
    }

    // Axes
    ctx.strokeStyle = "hsl(210, 15%, 40%)";
    ctx.lineWidth = 2;
    // X axis
    ctx.beginPath();
    ctx.moveTo(PADDING, centerY);
    ctx.lineTo(size.w - PADDING, centerY);
    ctx.stroke();
    // Y axis
    ctx.beginPath();
    ctx.moveTo(centerX, PADDING);
    ctx.lineTo(centerX, size.h - PADDING);
    ctx.stroke();

    // Axis labels
    ctx.fillStyle = "hsl(210, 15%, 45%)";
    ctx.font = "11px 'JetBrains Mono', monospace";
    ctx.textAlign = "center";
    ctx.textBaseline = "top";
    for (let i = -10; i <= 10; i++) {
      if (i === 0) continue;
      const [lx] = toCanvas(i, 0);
      const [, ly] = toCanvas(0, i);
      if (lx > PADDING + 10 && lx < size.w - PADDING - 10) {
        ctx.fillText(String(i), lx, centerY + 6);
      }
      ctx.textAlign = "right";
      ctx.textBaseline = "middle";
      if (ly > PADDING + 10 && ly < size.h - PADDING - 10) {
        ctx.fillText(String(i), centerX - 8, ly);
      }
      ctx.textAlign = "center";
      ctx.textBaseline = "top";
    }

    // Origin label
    ctx.fillStyle = "hsl(210, 15%, 45%)";
    ctx.textAlign = "right";
    ctx.textBaseline = "top";
    ctx.fillText("0", centerX - 6, centerY + 6);

    // Neighbor lines
    if (testPoint && resultado) {
      for (const v of resultado.vecinos) {
        const [x1, y1] = toCanvas(testPoint.x, testPoint.y);
        const [x2, y2] = toCanvas(v.punto.x, v.punto.y);
        ctx.strokeStyle = "hsla(45, 90%, 65%, 0.5)";
        ctx.lineWidth = 1.5;
        ctx.setLineDash([6, 4]);
        ctx.beginPath();
        ctx.moveTo(x1, y1);
        ctx.lineTo(x2, y2);
        ctx.stroke();
        ctx.setLineDash([]);

        // Distance label
        const mx = (x1 + x2) / 2;
        const my = (y1 + y2) / 2;
        ctx.fillStyle = "hsla(45, 90%, 65%, 0.8)";
        ctx.font = "10px 'JetBrains Mono', monospace";
        ctx.textAlign = "center";
        ctx.textBaseline = "bottom";
        ctx.fillText(`d=${v.distancia.toFixed(2)}`, mx, my - 4);
      }
    }

    // Training points
    for (const p of puntos) {
      const [px, py] = toCanvas(p.x, p.y);
      const color = p.clase === 0 ? "hsl(0, 85%, 60%)" : "hsl(210, 90%, 60%)";
      const glow = p.clase === 0 ? "hsla(0, 85%, 60%, 0.3)" : "hsla(210, 90%, 60%, 0.3)";

      // Glow
      ctx.beginPath();
      ctx.arc(px, py, 12, 0, Math.PI * 2);
      ctx.fillStyle = glow;
      ctx.fill();

      // Point
      ctx.beginPath();
      ctx.arc(px, py, 6, 0, Math.PI * 2);
      ctx.fillStyle = color;
      ctx.fill();
      ctx.strokeStyle = "hsla(0, 0%, 100%, 0.3)";
      ctx.lineWidth = 1;
      ctx.stroke();
    }

    // Test point
    if (testPoint) {
      const [tx, ty] = toCanvas(testPoint.x, testPoint.y);
      const classified = resultado !== null;
      const color = classified
        ? resultado.clase === 0
          ? "hsl(0, 85%, 60%)"
          : "hsl(210, 90%, 60%)"
        : "hsl(45, 95%, 65%)";

      // Glow ring
      ctx.beginPath();
      ctx.arc(tx, ty, 16, 0, Math.PI * 2);
      ctx.strokeStyle = color;
      ctx.lineWidth = 2;
      ctx.setLineDash([4, 3]);
      ctx.stroke();
      ctx.setLineDash([]);

      // Diamond shape
      ctx.beginPath();
      ctx.moveTo(tx, ty - 8);
      ctx.lineTo(tx + 8, ty);
      ctx.lineTo(tx, ty + 8);
      ctx.lineTo(tx - 8, ty);
      ctx.closePath();
      ctx.fillStyle = color;
      ctx.fill();
      ctx.strokeStyle = "hsla(0, 0%, 100%, 0.5)";
      ctx.lineWidth = 1;
      ctx.stroke();

      // Coords label
      ctx.fillStyle = "hsl(210, 20%, 80%)";
      ctx.font = "10px 'JetBrains Mono', monospace";
      ctx.textAlign = "left";
      ctx.textBaseline = "bottom";
      ctx.fillText(`(${testPoint.x.toFixed(1)}, ${testPoint.y.toFixed(1)})`, tx + 14, ty - 4);
    }
  }, [size, puntos, testPoint, resultado, toCanvas, centerX, centerY]);

  const handleClick = (e: React.MouseEvent<HTMLCanvasElement>) => {
    const rect = canvasRef.current!.getBoundingClientRect();
    const cx = e.clientX - rect.left;
    const cy = e.clientY - rect.top;
    const [mx, my] = toMath(cx, cy);

    if (mode === "test") {
      onSetTestPoint(parseFloat(mx.toFixed(2)), parseFloat(my.toFixed(2)));
    } else {
      // Left click = class 0 (red), handled here
      onAddPoint(parseFloat(mx.toFixed(2)), parseFloat(my.toFixed(2)), 0);
    }
  };

  const handleContextMenu = (e: React.MouseEvent<HTMLCanvasElement>) => {
    e.preventDefault();
    if (mode !== "train") return;
    const rect = canvasRef.current!.getBoundingClientRect();
    const cx = e.clientX - rect.left;
    const cy = e.clientY - rect.top;
    const [mx, my] = toMath(cx, cy);
    onAddPoint(parseFloat(mx.toFixed(2)), parseFloat(my.toFixed(2)), 1);
  };

  return (
    <div ref={containerRef} className="w-full h-full min-h-[500px] rounded-lg overflow-hidden border border-border">
      <canvas
        ref={canvasRef}
        width={size.w}
        height={size.h}
        style={{ width: size.w, height: size.h, cursor: "crosshair" }}
        onClick={handleClick}
        onContextMenu={handleContextMenu}
      />
    </div>
  );
}
