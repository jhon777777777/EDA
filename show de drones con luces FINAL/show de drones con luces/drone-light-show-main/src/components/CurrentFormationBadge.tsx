import React from 'react';
import { Sparkles } from 'lucide-react';
import { cn } from '@/lib/utils';

interface CurrentFormationBadgeProps {
  formationName: string;
  isTransitioning: boolean;
}

const CurrentFormationBadge: React.FC<CurrentFormationBadgeProps> = ({
  formationName,
  isTransitioning,
}) => {
  return (
    <div className="flex justify-center">
      <div className={cn(
        "relative inline-flex items-center gap-3 px-8 py-3 rounded-full",
        "bg-gradient-to-r from-primary/20 via-primary/10 to-primary/20",
        "border border-primary/30",
        "backdrop-blur-sm",
        "shadow-lg shadow-primary/10",
        "transition-all duration-500",
        isTransitioning && "animate-pulse"
      )}>
        {/* Animated border */}
        <div className="absolute inset-0 rounded-full overflow-hidden">
          <div className={cn(
            "absolute inset-[-50%] bg-gradient-conic from-primary via-transparent to-primary",
            "animate-spin [animation-duration:3s]",
            "opacity-20"
          )} />
        </div>
        
        {/* Content */}
        <div className="relative flex items-center gap-3">
          <Sparkles className={cn(
            "w-5 h-5 text-primary",
            isTransitioning ? "animate-spin" : "animate-pulse-glow"
          )} />
          
          <span className="font-display text-lg text-primary font-semibold tracking-wide">
            {formationName}
          </span>
          
          <Sparkles className={cn(
            "w-5 h-5 text-primary",
            isTransitioning ? "animate-spin" : "animate-pulse-glow"
          )} />
        </div>
        
        {/* Transition indicator */}
        {isTransitioning && (
          <div className="absolute -bottom-6 left-1/2 -translate-x-1/2">
            <span className="text-xs text-secondary font-medium animate-pulse">
              Formando...
            </span>
          </div>
        )}
      </div>
    </div>
  );
};

export default CurrentFormationBadge;
