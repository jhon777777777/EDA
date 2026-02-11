import React from 'react';
import { Eye, EyeOff, Code, Gauge } from 'lucide-react';
import { cn } from '@/lib/utils';
import { Slider } from '@/components/ui/slider';

interface ControlPanelProps {
  showGraph: boolean;
  onToggleGraph: () => void;
  showCode: boolean;
  onToggleCode: () => void;
  velocidad: number;
  onVelocidadChange: (velocidad: number) => void;
}

const ControlPanel: React.FC<ControlPanelProps> = ({
  showGraph,
  onToggleGraph,
  showCode,
  onToggleCode,
  velocidad,
  onVelocidadChange,
}) => {
  return (
    <div className="flex items-center gap-4">
      <ControlButton
        icon={showGraph ? <Eye className="w-4 h-4" /> : <EyeOff className="w-4 h-4" />}
        label="Grafo"
        isActive={showGraph}
        onClick={onToggleGraph}
      />
      
      <ControlButton
        icon={<Code className="w-4 h-4" />}
        label="C++"
        isActive={showCode}
        onClick={onToggleCode}
      />
      
      {/* Control de velocidad */}
      <div className="flex items-center gap-3 px-4 py-2 rounded-xl bg-card/40 border border-border/50">
        <Gauge className="w-4 h-4 text-muted-foreground" />
        <span className="text-sm text-muted-foreground whitespace-nowrap">Velocidad:</span>
        <Slider
          value={[velocidad]}
          onValueChange={(values) => onVelocidadChange(values[0])}
          min={0.3}
          max={3}
          step={0.1}
          className="w-24"
        />
        <span className="text-sm font-medium text-primary min-w-[3ch]">
          {velocidad.toFixed(1)}x
        </span>
      </div>
    </div>
  );
};

interface ControlButtonProps {
  icon: React.ReactNode;
  label: string;
  isActive: boolean;
  onClick: () => void;
}

const ControlButton: React.FC<ControlButtonProps> = ({
  icon,
  label,
  isActive,
  onClick,
}) => {
  return (
    <button
      onClick={onClick}
      className={cn(
        "group relative flex items-center gap-2 px-4 py-2.5 rounded-xl",
        "border transition-all duration-300 ease-out",
        "hover:scale-105 active:scale-95",
        isActive
          ? "bg-primary/20 border-primary/50 text-primary shadow-lg shadow-primary/20"
          : "bg-card/40 border-border/50 text-muted-foreground hover:bg-card/60 hover:text-foreground hover:border-primary/30"
      )}
    >
      <span className={cn(
        "transition-transform duration-300",
        "group-hover:scale-110",
        isActive && "animate-pulse-glow"
      )}>
        {icon}
      </span>
      <span className="text-sm font-medium">{label}</span>
      
      {/* Active dot indicator */}
      {isActive && (
        <span className="absolute -top-1 -right-1 w-2.5 h-2.5 rounded-full bg-primary animate-pulse" />
      )}
    </button>
  );
};

export default ControlPanel;
