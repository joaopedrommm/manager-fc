const FORMATION_LAYOUTS = {
  '4-4-2':       [[1],[4,4],[4],[2]],
  '4-3-3':       [[1],[4],[3],[3]],
  '4-2-3-1':     [[1],[4],[2],[3],[1]],
  '3-5-2':       [[1],[3],[5],[2]],
  '3-4-3':       [[1],[3],[4],[3]],
  '4-2-4':       [[1],[4],[2],[4]],
  '4-1-2-1-2':   [[1],[4],[1],[2],[1],[2]],
  '5-4-1':       [[1],[5],[4],[1]],
  '5-3-2':       [[1],[5],[3],[2]],
  '5-2-3':       [[1],[5],[2],[3]],
};

export const FORMACOES = Object.keys(FORMATION_LAYOUTS);

export default function MFCFormation({ name, color = 'var(--c-gold)', highlight = false, width = 110, height = 130 }) {
  const lines = FORMATION_LAYOUTS[name] || FORMATION_LAYOUTS['4-3-3'];
  const N = lines.length;
  const padX = 10, padY = 10;
  const innerW = width - padX * 2;
  const innerH = height - padY * 2;
  const lineSpace = innerH / (N - 1 || 1);

  const dots = [];
  lines.forEach((count, li) => {
    const y = padY + innerH - li * lineSpace;
    for (let i = 0; i < count; i++) {
      const x = padX + (count === 1 ? innerW / 2 : (innerW * (i + 0.5) / count));
      dots.push({ x, y, isGk: li === 0 });
    }
  });

  return (
    <svg viewBox={`0 0 ${width} ${height}`} width={width} height={height} style={{ display: 'block' }}>
      <rect x="2" y="2" width={width - 4} height={height - 4}
        fill="rgba(20,60,30,0.18)" stroke={highlight ? color : 'var(--c-border)'} strokeWidth={highlight ? 2 : 1} />
      <line x1="2" y1={height / 2} x2={width - 2} y2={height / 2}
        stroke="var(--c-border)" strokeWidth="0.7" strokeDasharray="2 2" />
      <circle cx={width / 2} cy={height / 2} r="12" fill="none" stroke="var(--c-border)" strokeWidth="0.7" />
      <rect x={width * 0.25} y="2" width={width * 0.5} height="10" fill="none" stroke="var(--c-border)" strokeWidth="0.7" />
      <rect x={width * 0.25} y={height - 12} width={width * 0.5} height="10" fill="none" stroke="var(--c-border)" strokeWidth="0.7" />
      {dots.map((d, i) => (
        <g key={i}>
          <circle cx={d.x} cy={d.y} r={d.isGk ? 4.5 : 4} fill={color} stroke="rgba(0,0,0,0.6)" strokeWidth="0.8" />
          {d.isGk && (
            <text x={d.x} y={d.y + 2} textAnchor="middle" fontSize="6"
              fill="rgba(0,0,0,0.7)" fontFamily="monospace">G</text>
          )}
        </g>
      ))}
    </svg>
  );
}
