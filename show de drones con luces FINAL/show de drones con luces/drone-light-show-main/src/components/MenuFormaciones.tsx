// Componente unificado del menú de formaciones
import React from 'react';
import { Star, Crown, Building, Calendar, Type, Sparkles, Heart, Layers } from 'lucide-react';
import { cn } from '@/lib/utils';

// ===== TIPOS =====
export interface Formacion {
  id: string;
  nombre: string;
  descripcion: string;
  icono: React.ReactNode;
  categoria: 'texto' | 'icono' | 'simbolo';
}

// ===== LISTA DE FORMACIONES =====
export const listaFormaciones: Formacion[] = [
  { 
    id: 'PUNO_SE_RESPETA', 
    descripcion: 'Texto cultural', 
    nombre: 'PUNO SE RESPETA',
    icono: <Type className="w-5 h-5" />,
    categoria: 'texto'
  },
  { 
    id: 'SISTEMAS_UNAP', 
    descripcion: 'Facultad de Ingeniería', 
    nombre: 'SISTEMAS UNAP',
    icono: <Type className="w-5 h-5" />,
    categoria: 'texto'
  },
  { 
    id: 'EPIS', 
    descripcion: 'Escuela Profesional', 
    nombre: 'EPIS',
    icono: <Sparkles className="w-5 h-5" />,
    categoria: 'texto'
  },
  { 
    id: 'DIABLADA', 
    descripcion: 'Danza típica de Puno', 
    nombre: 'MÁSCARA DIABLADA',
    icono: <Crown className="w-5 h-5" />,
    categoria: 'icono'
  },
  { 
    id: 'VIRGEN', 
    descripcion: 'Patrona de Puno', 
    nombre: 'VIRGEN CANDELARIA',
    icono: <Heart className="w-5 h-5" />,
    categoria: 'icono'
  },
  { 
    id: 'ESTRELLAS', 
    descripcion: 'Formación de estrellas', 
    nombre: 'ESTRELLAS',
    icono: <Star className="w-5 h-5" />,
    categoria: 'simbolo'
  },
  { 
    id: 'TORRE_EIFFEL', 
    descripcion: 'Monumento icónico', 
    nombre: 'TORRE EIFFEL',
    icono: <Building className="w-5 h-5" />,
    categoria: 'simbolo'
  },
  { 
    id: '2026', 
    descripcion: 'Año del evento', 
    nombre: 'CANDELARIA 2026',
    icono: <Calendar className="w-5 h-5" />,
    categoria: 'simbolo'
  },
];

// ===== COMPONENTE BOTÓN =====
interface BotonMenuProps {
  icono: React.ReactNode;
  titulo: string;
  subtitulo: string;
  activo: boolean;
  onClick: () => void;
  indice: number;
}

const BotonMenu: React.FC<BotonMenuProps> = ({
  icono,
  titulo,
  subtitulo,
  activo,
  onClick,
  indice,
}) => {
  return (
    <button
      onClick={onClick}
      style={{ animationDelay: `${indice * 50}ms` }}
      className={cn(
        "group relative w-full px-4 py-3 rounded-xl text-left transition-all duration-300 ease-out",
        "border backdrop-blur-sm overflow-hidden",
        "animate-fade-in opacity-0 [animation-fill-mode:forwards]",
        "hover:scale-[1.02] hover:-translate-y-0.5",
        activo
          ? "bg-gradient-to-r from-primary/20 via-primary/10 to-transparent border-primary/50 shadow-lg shadow-primary/20"
          : "bg-card/40 border-border/50 hover:bg-card/60 hover:border-primary/30"
      )}
    >
      <div className={cn(
        "absolute inset-0 opacity-0 transition-opacity duration-300",
        "bg-gradient-to-r from-primary/10 via-transparent to-transparent",
        "group-hover:opacity-100"
      )} />
      
      <div className={cn(
        "absolute left-0 top-1/2 -translate-y-1/2 w-1 h-0 rounded-r-full bg-primary",
        "transition-all duration-300 ease-out",
        activo ? "h-8" : "group-hover:h-4"
      )} />
      
      <div className="relative flex items-center gap-3">
        <div className={cn(
          "flex items-center justify-center w-10 h-10 rounded-lg transition-all duration-300",
          activo 
            ? "bg-primary/20 text-primary shadow-inner" 
            : "bg-muted/50 text-muted-foreground group-hover:bg-primary/10 group-hover:text-primary"
        )}>
          {icono}
        </div>
        
        <div className="flex-1 min-w-0">
          <div className={cn(
            "font-medium text-sm truncate transition-colors duration-300",
            activo ? "text-primary" : "text-foreground group-hover:text-primary"
          )}>
            {titulo}
          </div>
          <div className="text-xs text-muted-foreground truncate">
            {subtitulo}
          </div>
        </div>
        
        <div className={cn(
          "w-5 h-5 flex items-center justify-center transition-all duration-300",
          "opacity-0 -translate-x-2",
          "group-hover:opacity-100 group-hover:translate-x-0",
          activo && "opacity-100 translate-x-0"
        )}>
          <svg 
            className="w-4 h-4 text-primary" 
            fill="none" 
            viewBox="0 0 24 24" 
            stroke="currentColor"
          >
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 5l7 7-7 7" />
          </svg>
        </div>
      </div>
    </button>
  );
};

// ===== COMPONENTE SECCIÓN =====
interface SeccionMenuProps {
  titulo: string;
  icono?: React.ReactNode;
  children: React.ReactNode;
}

const SeccionMenu: React.FC<SeccionMenuProps> = ({ titulo, icono, children }) => {
  return (
    <div className="space-y-3">
      <div className="flex items-center gap-2 px-1">
        {icono && <span className="text-primary/70">{icono}</span>}
        <h3 className="font-display text-xs uppercase tracking-[0.2em] text-muted-foreground">
          {titulo}
        </h3>
        <div className="flex-1 h-px bg-gradient-to-r from-border to-transparent" />
      </div>
      <div className="space-y-2">
        {children}
      </div>
    </div>
  );
};

// ===== COMPONENTE CONTENEDOR =====
interface ContenedorMenuProps {
  children: React.ReactNode;
  className?: string;
}

export const ContenedorMenu: React.FC<ContenedorMenuProps> = ({ children, className }) => {
  return (
    <div className={cn(
      "relative p-5 rounded-2xl overflow-hidden",
      "bg-gradient-to-b from-card/50 to-card/30",
      "border border-border/50",
      "backdrop-blur-xl",
      "shadow-2xl shadow-black/20",
      className
    )}>
      <div className="absolute -top-20 -right-20 w-40 h-40 bg-primary/10 rounded-full blur-3xl pointer-events-none" />
      <div className="absolute -bottom-20 -left-20 w-40 h-40 bg-secondary/10 rounded-full blur-3xl pointer-events-none" />
      
      <div 
        className="absolute inset-0 opacity-[0.03] pointer-events-none"
        style={{
          backgroundImage: `linear-gradient(to right, hsl(var(--foreground)) 1px, transparent 1px),
                           linear-gradient(to bottom, hsl(var(--foreground)) 1px, transparent 1px)`,
          backgroundSize: '20px 20px'
        }}
      />
      
      <div className="relative z-10">
        {children}
      </div>
    </div>
  );
};

// ===== COMPONENTE PRINCIPAL =====
interface MenuFormacionesProps {
  formacionActiva: string;
  onSeleccionar: (id: string) => void;
}

const MenuFormaciones: React.FC<MenuFormacionesProps> = ({ formacionActiva, onSeleccionar }) => {
  const textos = listaFormaciones.filter(f => f.categoria === 'texto');
  const iconos = listaFormaciones.filter(f => f.categoria === 'icono');
  const simbolos = listaFormaciones.filter(f => f.categoria === 'simbolo');

  return (
    <div className="space-y-6">
      <SeccionMenu titulo="Textos" icono={<Type className="w-3.5 h-3.5" />}>
        {textos.map((formacion, indice) => (
          <BotonMenu
            key={formacion.id}
            icono={formacion.icono}
            titulo={formacion.nombre}
            subtitulo={formacion.descripcion}
            activo={formacionActiva === formacion.id}
            onClick={() => onSeleccionar(formacion.id)}
            indice={indice}
          />
        ))}
      </SeccionMenu>

      <SeccionMenu titulo="Iconos Culturales" icono={<Crown className="w-3.5 h-3.5" />}>
        {iconos.map((formacion, indice) => (
          <BotonMenu
            key={formacion.id}
            icono={formacion.icono}
            titulo={formacion.nombre}
            subtitulo={formacion.descripcion}
            activo={formacionActiva === formacion.id}
            onClick={() => onSeleccionar(formacion.id)}
            indice={indice + textos.length}
          />
        ))}
      </SeccionMenu>

      <SeccionMenu titulo="Símbolos" icono={<Layers className="w-3.5 h-3.5" />}>
        {simbolos.map((formacion, indice) => (
          <BotonMenu
            key={formacion.id}
            icono={formacion.icono}
            titulo={formacion.nombre}
            subtitulo={formacion.descripcion}
            activo={formacionActiva === formacion.id}
            onClick={() => onSeleccionar(formacion.id)}
            indice={indice + textos.length + iconos.length}
          />
        ))}
      </SeccionMenu>
    </div>
  );
};

export default MenuFormaciones;
