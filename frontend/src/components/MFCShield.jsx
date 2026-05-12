const TEAM_LOGOS = {
  1:  '/times/flamengo.png',
  2:  '/times/atletico-mg.png',
  3:  '/times/palmeiras.png',
  4:  '/times/fluminense.png',
  5:  '/times/athletico-pr.png',
  6:  '/times/internacional.png',
  7:  '/times/sao-paulo.png',
  8:  '/times/gremio.svg',
  9:  '/times/botafogo.png',
  10: '/times/vasco.png',
  11: '/times/corinthians.png',
  12: '/times/cruzeiro.png',
  13: '/times/bahia.png',
  14: '/times/santos.png',
  15: '/times/bragantino.png',
  16: '/times/chapecoense.png',
  17: '/times/coritiba.png',
  18: '/times/vitoria.png',
  19: '/times/mirassol.png',
  20: '/times/remo.png',
};

const TEAM_STYLES = {
  1:  { primary:'#d12020', secondary:'#1a1a1a' },
  2:  { primary:'#1a1a1a', secondary:'#ffffff' },
  3:  { primary:'#1f7a3d', secondary:'#ffffff' },
  4:  { primary:'#7a1818', secondary:'#0a3a1f' },
  5:  { primary:'#e02020', secondary:'#1a1a1a' },
  6:  { primary:'#c01818', secondary:'#ffffff' },
  7:  { primary:'#c01818', secondary:'#ffffff' },
  8:  { primary:'#1668c0', secondary:'#1a1a1a' },
  9:  { primary:'#1a1a1a', secondary:'#ffffff' },
  10: { primary:'#1a1a1a', secondary:'#c01818' },
  11: { primary:'#1a1a1a', secondary:'#ffffff' },
  12: { primary:'#1a4caa', secondary:'#ffffff' },
  13: { primary:'#1668c0', secondary:'#c01818' },
  14: { primary:'#0a0a0a', secondary:'#ffffff' },
  15: { primary:'#cc1f1f', secondary:'#1a1a1a' },
  16: { primary:'#1f7a3d', secondary:'#ffffff' },
  17: { primary:'#1f7a3d', secondary:'#ffffff' },
  18: { primary:'#c01818', secondary:'#1a1a1a' },
  19: { primary:'#1f7a3d', secondary:'#e8b820' },
  20: { primary:'#1a4caa', secondary:'#ffffff' },
};

export function getTeamStyle(id) {
  return TEAM_STYLES[id] || { primary: '#c8a820', secondary: '#1a1a1a' };
}

export default function MFCShield({ teamId, sigla, size = 28 }) {
  const src = TEAM_LOGOS[teamId];
  if (!src) {
    const s = getTeamStyle(teamId);
    return (
      <span style={{
        display: 'inline-flex', alignItems: 'center', justifyContent: 'center',
        width: size, height: size, flexShrink: 0, verticalAlign: 'middle',
        background: s.primary, border: '1px solid rgba(0,0,0,0.6)',
        fontFamily: 'var(--font-mono)', fontSize: Math.round(size * 0.32) + 'px',
        color: '#ffffff', letterSpacing: '0.04em', fontWeight: 'bold',
      }}>{sigla}</span>
    );
  }
  return (
    <span style={{
      display: 'inline-flex', alignItems: 'center', justifyContent: 'center',
      width: size, height: size, flexShrink: 0, verticalAlign: 'middle',
    }}>
      <img
        src={src}
        alt={sigla}
        width={size}
        height={size}
        style={{ width: size, height: size, objectFit: 'contain', display: 'block' }}
        loading="lazy"
      />
    </span>
  );
}
