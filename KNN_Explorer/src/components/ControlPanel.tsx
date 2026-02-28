import { useState } from "react";
import type { Punto, VecinoConDistancia } from "@/lib/knn";

interface Props {
  mode: "train" | "test";
  setMode: (m: "train" | "test") => void;
  k: number;
  setK: (k: number) => void;
  puntos: Punto[];
  resultado: { clase: number; vecinos: VecinoConDistancia[] } | null;
  testPoint: { x: number; y: number } | null;
  onClear: () => void;
  onAddPoint: (x: number, y: number, clase: number) => void;
  onSetTestPoint: (x: number, y: number) => void;
}

export default function ControlPanel({ mode, setMode, k, setK, puntos, resultado, testPoint, onClear, onAddPoint, onSetTestPoint }: Props) {
  const rojos = puntos.filter((p) => p.clase === 0).length;
  const azules = puntos.filter((p) => p.clase === 1).length;

  const [inputX, setInputX] = useState("");
  const [inputY, setInputY] = useState("");
  const [inputClase, setInputClase] = useState<0 | 1>(0);

  const handleManualAdd = () => {
    const x = parseFloat(inputX);
    const y = parseFloat(inputY);
    if (isNaN(x) || isNaN(y)) return;
    if (mode === "test") {
      onSetTestPoint(x, y);
    } else {
      onAddPoint(x, y, inputClase);
    }
    setInputX("");
    setInputY("");
  };

  return (
    <div className="flex flex-col gap-4 p-5 bg-card rounded-lg border border-border h-full">
      <h2 className="text-lg font-semibold font-mono tracking-tight text-foreground">
        KNN Visualizador
      </h2>

      {/* Mode toggle */}
      <div className="flex flex-col gap-2">
        <span className="text-xs font-mono text-muted-foreground uppercase tracking-wider">Modo</span>
        <div className="flex gap-2">
          <button
            onClick={() => setMode("train")}
            className={`flex-1 px-3 py-2 rounded-md text-sm font-mono transition-colors ${
              mode === "train"
                ? "bg-primary text-primary-foreground"
                : "bg-secondary text-secondary-foreground hover:bg-secondary/80"
            }`}
          >
            Entrenar
          </button>
          <button
            onClick={() => setMode("test")}
            disabled={puntos.length < 1}
            className={`flex-1 px-3 py-2 rounded-md text-sm font-mono transition-colors disabled:opacity-40 ${
              mode === "test"
                ? "bg-primary text-primary-foreground"
                : "bg-secondary text-secondary-foreground hover:bg-secondary/80"
            }`}
          >
            Clasificar
          </button>
        </div>
      </div>

      {/* K slider */}
      <div className="flex flex-col gap-2">
        <span className="text-xs font-mono text-muted-foreground uppercase tracking-wider">
          K = {k}
        </span>
        <input
          type="range"
          min={1}
          max={Math.max(puntos.length, 1)}
          value={k}
          onChange={(e) => setK(parseInt(e.target.value))}
          className="w-full accent-primary"
        />
      </div>

      {/* Manual input */}
      <div className="flex flex-col gap-2">
        <span className="text-xs font-mono text-muted-foreground uppercase tracking-wider">
          Insertar punto manual
        </span>
        <div className="flex gap-2">
          <input
            type="number"
            step="0.1"
            placeholder="X"
            value={inputX}
            onChange={(e) => setInputX(e.target.value)}
            className="flex-1 px-2 py-1.5 rounded-md text-sm font-mono bg-muted text-foreground border border-border focus:outline-none focus:ring-1 focus:ring-primary"
          />
          <input
            type="number"
            step="0.1"
            placeholder="Y"
            value={inputY}
            onChange={(e) => setInputY(e.target.value)}
            className="flex-1 px-2 py-1.5 rounded-md text-sm font-mono bg-muted text-foreground border border-border focus:outline-none focus:ring-1 focus:ring-primary"
          />
        </div>
        {mode === "train" && (
          <div className="flex gap-2">
            <button
              onClick={() => setInputClase(0)}
              className={`flex-1 px-2 py-1.5 rounded-md text-xs font-mono transition-colors ${
                inputClase === 0
                  ? "bg-class-red/20 text-class-red border border-class-red/50"
                  : "bg-muted text-muted-foreground border border-border"
              }`}
            >
              ● Clase A (Rojo)
            </button>
            <button
              onClick={() => setInputClase(1)}
              className={`flex-1 px-2 py-1.5 rounded-md text-xs font-mono transition-colors ${
                inputClase === 1
                  ? "bg-class-blue/20 text-class-blue border border-class-blue/50"
                  : "bg-muted text-muted-foreground border border-border"
              }`}
            >
              ● Clase B (Azul)
            </button>
          </div>
        )}
        <button
          onClick={handleManualAdd}
          disabled={inputX === "" || inputY === ""}
          className="px-3 py-1.5 rounded-md text-sm font-mono bg-primary text-primary-foreground hover:bg-primary/90 transition-colors disabled:opacity-40"
        >
          {mode === "test" ? "Clasificar punto" : "Agregar punto"}
        </button>
      </div>

      {/* Instructions */}
      <div className="flex flex-col gap-1.5 p-3 rounded-md bg-muted">
        <span className="text-xs font-mono text-muted-foreground uppercase tracking-wider">Instrucciones</span>
        {mode === "train" ? (
          <>
            <p className="text-xs text-secondary-foreground">
              <span className="inline-block w-2.5 h-2.5 rounded-full bg-class-red mr-1.5 align-middle" />
              Clic izquierdo → Clase A (Rojo)
            </p>
            <p className="text-xs text-secondary-foreground">
              <span className="inline-block w-2.5 h-2.5 rounded-full bg-class-blue mr-1.5 align-middle" />
              Clic derecho → Clase B (Azul)
            </p>
            <p className="text-xs text-secondary-foreground mt-1">
              O usa los campos de arriba para digitar coordenadas
            </p>
          </>
        ) : (
          <>
            <p className="text-xs text-secondary-foreground">
              <span className="inline-block w-2.5 h-2.5 rounded-sm bg-test-point mr-1.5 align-middle rotate-45" />
              Clic → Colocar punto de prueba
            </p>
            <p className="text-xs text-secondary-foreground mt-1">
              O digita las coordenadas arriba
            </p>
          </>
        )}
      </div>

      {/* Stats */}
      <div className="flex flex-col gap-1.5">
        <span className="text-xs font-mono text-muted-foreground uppercase tracking-wider">Datos</span>
        <div className="grid grid-cols-2 gap-2">
          <div className="flex items-center gap-2 p-2 rounded-md bg-muted">
            <span className="w-3 h-3 rounded-full bg-class-red" />
            <span className="text-sm font-mono text-foreground">{rojos}</span>
          </div>
          <div className="flex items-center gap-2 p-2 rounded-md bg-muted">
            <span className="w-3 h-3 rounded-full bg-class-blue" />
            <span className="text-sm font-mono text-foreground">{azules}</span>
          </div>
        </div>
      </div>

      {/* Result */}
      {resultado && testPoint && (
        <div className="flex flex-col gap-1.5 p-3 rounded-md border border-neighbor-line/30 bg-muted">
          <span className="text-xs font-mono text-neighbor-line uppercase tracking-wider">Resultado</span>
          <p className="text-sm text-foreground">
            Punto ({testPoint.x.toFixed(1)}, {testPoint.y.toFixed(1)}) →{" "}
            <span className={resultado.clase === 0 ? "text-class-red font-semibold" : "text-class-blue font-semibold"}>
              {resultado.clase === 0 ? "Clase A (Rojo)" : "Clase B (Azul)"}
            </span>
          </p>
          <div className="flex flex-col gap-0.5 mt-1">
            <span className="text-[10px] font-mono text-muted-foreground">Vecinos (k={k}):</span>
            {resultado.vecinos.map((v, i) => (
              <span key={i} className="text-[11px] font-mono text-secondary-foreground">
                {i + 1}. ({v.punto.x.toFixed(1)}, {v.punto.y.toFixed(1)}) d={v.distancia.toFixed(2)}{" "}
                <span className={v.punto.clase === 0 ? "text-class-red" : "text-class-blue"}>
                  {v.punto.clase === 0 ? "●" : "●"}
                </span>
              </span>
            ))}
          </div>
        </div>
      )}

      {/* Clear */}
      <button
        onClick={onClear}
        className="mt-auto px-3 py-2 rounded-md text-sm font-mono bg-destructive/10 text-destructive hover:bg-destructive/20 transition-colors"
      >
        Limpiar todo
      </button>
    </div>
  );
}
