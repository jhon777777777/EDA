import React, { useState } from 'react';
import { Sparkles } from 'lucide-react';
import DroneCanvas from '@/components/DroneCanvas';
import MenuFormaciones, { ContenedorMenu, listaFormaciones } from '@/components/MenuFormaciones';
import StatsPanel from '@/components/StatsPanel';
import PanelCodigoCpp from '@/components/PanelCodigoCpp';
import ControlPanel from '@/components/ControlPanel';
import CurrentFormationBadge from '@/components/CurrentFormationBadge';
import { useDroneSimulation } from '@/hooks/useDroneSimulation';

const Index = () => {
  const {
    drones,
    activeFormation,
    isTransitioning,
    transitionProgress,
    edgeCount,
    fps,
    changeFormation,
    droneCount,
    canvasWidth,
    canvasHeight,
    velocidadTransicion,
    setVelocidadTransicion,
  } = useDroneSimulation('ESTRELLAS');
  
  const [showGraph, setShowGraph] = useState(true);
  const [showCode, setShowCode] = useState(false);

  const nombreFormacion = listaFormaciones.find(f => f.id === activeFormation)?.nombre || activeFormation;

  return (
    <div className="min-h-screen p-4 md:p-6 lg:p-8">
      {/* Encabezado */}
      <header className="text-center mb-6 md:mb-8 animate-fade-in">
        <div className="inline-flex items-center gap-3 mb-2">
          <Sparkles className="w-6 h-6 md:w-8 md:h-8 text-primary animate-pulse-glow" />
          <h1 className="font-display text-3xl md:text-4xl lg:text-5xl font-bold title-glow text-foreground">
            CANDELARIA 2026
          </h1>
          <Sparkles className="w-6 h-6 md:w-8 md:h-8 text-primary animate-pulse-glow" />
        </div>
        <p className="text-muted-foreground font-body text-base md:text-lg">
          Simulador de Espectáculo de Drones • Grafo de Proximidad
        </p>
      </header>

      <div className="max-w-[1700px] mx-auto grid lg:grid-cols-[1fr_380px] gap-6">
        {/* Área del Canvas */}
        <div className="space-y-4 animate-scale-in">
          {/* Barra de estadísticas */}
          <div className="flex flex-wrap items-center justify-between gap-4">
            <StatsPanel 
              droneCount={droneCount}
              edgeCount={edgeCount}
              fps={fps}
              isTransitioning={isTransitioning}
              transitionProgress={transitionProgress}
            />
            
            <ControlPanel
              showGraph={showGraph}
              onToggleGraph={() => setShowGraph(!showGraph)}
              showCode={showCode}
              onToggleCode={() => setShowCode(!showCode)}
              velocidad={velocidadTransicion}
              onVelocidadChange={setVelocidadTransicion}
            />
          </div>
          
          {/* Canvas */}
          <div className="canvas-container">
            <DroneCanvas 
              drones={drones}
              showGraph={showGraph}
              width={canvasWidth}
              height={canvasHeight}
            />
          </div>
          
          {/* Formación actual */}
          <CurrentFormationBadge 
            formationName={nombreFormacion}
            isTransitioning={isTransitioning}
          />
        </div>

        {/* Barra lateral */}
        <aside className="space-y-6 animate-slide-in-right">
          {/* Menú de formaciones */}
          <ContenedorMenu>
            <div className="mb-4">
              <h2 className="font-display text-lg text-foreground flex items-center gap-2">
                <span className="w-2 h-2 rounded-full bg-primary animate-pulse" />
                Formaciones
              </h2>
              <p className="text-xs text-muted-foreground mt-1">
                Selecciona una figura para el espectáculo
              </p>
            </div>
            <MenuFormaciones 
              formacionActiva={activeFormation}
              onSeleccionar={changeFormation}
            />
          </ContenedorMenu>
          
          {/* Panel de código C++ */}
          {showCode && (
            <ContenedorMenu className="animate-fade-in">
              <PanelCodigoCpp />
            </ContenedorMenu>
          )}
        </aside>
      </div>

      {/* Pie de página */}
      <footer className="text-center mt-8 md:mt-12 text-muted-foreground text-sm animate-fade-in">
        <p>
          Simulador para la Festividad de la Virgen de la Candelaria • Puno, Perú 2026
        </p>
      </footer>
    </div>
  );
};

export default Index;
