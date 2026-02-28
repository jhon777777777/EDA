import { useState, useCallback, useEffect } from "react";
import KNNCanvas from "@/components/KNNCanvas";
import ControlPanel from "@/components/ControlPanel";
import { clasificar, type Punto, type VecinoConDistancia } from "@/lib/knn";

const Index = () => {
  const [puntos, setPuntos] = useState<Punto[]>([]);
  const [testPoint, setTestPoint] = useState<{ x: number; y: number } | null>(null);
  const [resultado, setResultado] = useState<{ clase: number; vecinos: VecinoConDistancia[] } | null>(null);
  const [mode, setMode] = useState<"train" | "test">("train");
  const [k, setK] = useState(3);

  const handleAddPoint = useCallback((x: number, y: number, clase: number) => {
    setPuntos((prev) => [...prev, { x, y, clase }]);
  }, []);

  const reclassify = useCallback(
    (point: { x: number; y: number }, currentK: number, currentPuntos: Punto[]) => {
      if (currentPuntos.length > 0) {
        const effectiveK = Math.min(currentK, currentPuntos.length);
        const res = clasificar(currentPuntos, point, effectiveK);
        setResultado(res);
      }
    },
    []
  );

  const handleSetTestPoint = useCallback(
    (x: number, y: number) => {
      setTestPoint({ x, y });
      reclassify({ x, y }, k, puntos);
    },
    [puntos, k, reclassify]
  );

  // Re-classify when K changes
  useEffect(() => {
    if (testPoint && puntos.length > 0) {
      reclassify(testPoint, k, puntos);
    }
  }, [k, testPoint, puntos, reclassify]);

  const handleClear = useCallback(() => {
    setPuntos([]);
    setTestPoint(null);
    setResultado(null);
    setMode("train");
  }, []);

  const handleModeChange = useCallback((m: "train" | "test") => {
    setMode(m);
    if (m === "train") {
      setTestPoint(null);
      setResultado(null);
    }
  }, []);

  return (
    <div className="flex h-screen bg-background overflow-hidden">
      {/* Sidebar */}
      <div className="w-80 shrink-0 border-r border-border overflow-y-auto">
        <ControlPanel
          mode={mode}
          setMode={handleModeChange}
          k={k}
          setK={setK}
          puntos={puntos}
          resultado={resultado}
          testPoint={testPoint}
          onClear={handleClear}
          onAddPoint={handleAddPoint}
          onSetTestPoint={handleSetTestPoint}
        />
      </div>

      {/* Canvas area - maximized */}
      <div className="flex-1 p-2">
        <KNNCanvas
          puntos={puntos}
          testPoint={testPoint}
          resultado={resultado}
          onAddPoint={handleAddPoint}
          onSetTestPoint={handleSetTestPoint}
          mode={mode}
        />
      </div>
    </div>
  );
};

export default Index;
