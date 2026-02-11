import React from 'react';
import { Activity, Zap, Link } from 'lucide-react';
import { Progress } from '@/components/ui/progress';

interface StatsPanelProps {
  droneCount: number;
  edgeCount: number;
  fps: number;
  isTransitioning: boolean;
  transitionProgress: number;
}

const StatsPanel: React.FC<StatsPanelProps> = ({ 
  droneCount, 
  edgeCount, 
  fps,
  isTransitioning,
  transitionProgress
}) => {
  return (
    <div className="flex flex-wrap items-center gap-4">
      <div className="stat-display flex items-center gap-2">
        <Zap className="w-4 h-4 text-primary" />
        <span className="text-sm">
          <span className="text-muted-foreground">Drones: </span>
          <span className="font-display text-foreground">{droneCount}</span>
        </span>
      </div>
      
      <div className="stat-display flex items-center gap-2">
        <Link className="w-4 h-4 text-accent" />
        <span className="text-sm">
          <span className="text-muted-foreground">Conexiones: </span>
          <span className="font-display text-foreground">{edgeCount}</span>
        </span>
      </div>
      
      <div className="stat-display flex items-center gap-2">
        <Activity className="w-4 h-4 text-accent" />
        <span className="text-sm">
          <span className="text-muted-foreground">FPS: </span>
          <span className="font-display text-foreground">{fps}</span>
        </span>
      </div>
      
      {isTransitioning && (
        <div className="flex items-center gap-3 px-3 py-1.5 bg-muted/30 rounded-lg border border-border/50 animate-pulse-glow">
          <span className="text-sm text-secondary font-medium whitespace-nowrap">
            Formando...
          </span>
          <div className="w-24 md:w-32">
            <Progress value={transitionProgress} className="h-2" />
          </div>
          <span className="text-xs text-muted-foreground font-mono">
            {Math.round(transitionProgress)}%
          </span>
        </div>
      )}
    </div>
  );
};

export default StatsPanel;
