import { useState, useEffect } from 'react';
import MFCShield, { getTeamStyle } from './MFCShield';

export default function SelecaoClube({ onVoltar, onConfirmar }) {
  const [times, setTimes]     = useState([]);
  const [loading, setLoading] = useState(true);
  const [hovered, setHovered] = useState(null);

  useEffect(() => {
    fetch('/api/times').then(r => r.json()).then(data => {
      setTimes(data); setLoading(false);
    });
  }, []);

  const forcaColor = (f) =>
    f >= 85 ? 'var(--c-gold)' :
    f >= 75 ? 'var(--c-text)' : 'var(--c-text-dim)';

  return (
    <div className="mfc-screen mfc-pitch-bg" style={{ display: 'flex', flexDirection: 'column' }}>
      <div className="mfc-topbar">
        <div>
          <div className="mfc-topbar-title">SELECIONAR CLUBE</div>
          <div className="mfc-topbar-sub">Brasileirao Serie A 2026 · 20 times</div>
        </div>
        <button className="mfc-btn mfc-btn-ghost" onClick={onVoltar}>← VOLTAR</button>
      </div>

      <div style={{ flex: 1, overflowY: 'auto', padding: '16px 20px' }}>
        {loading ? (
          <div className="mfc-loading">
            <div className="mfc-spinner">■</div>
            <div className="mfc-loading-text">CARREGANDO TIMES...</div>
          </div>
        ) : (
          <div style={{ maxWidth: '920px', margin: '0 auto' }}>
            <div className="mfc-team-grid">
              {times.map(t => {
                const ts = getTeamStyle(t.id);
                const isHover = hovered === t.id;
                return (
                  <button
                    key={t.id}
                    className="mfc-team-card"
                    onClick={() => onConfirmar(t)}
                    onMouseEnter={() => setHovered(t.id)}
                    onMouseLeave={() => setHovered(null)}
                    style={{ borderColor: isHover ? ts.primary : undefined }}
                  >
                    <div className="mfc-team-card-accent" style={{ background: ts.primary }} />
                    <div style={{ display: 'flex', alignItems: 'center', gap: '10px', flex: 1, minWidth: 0 }}>
                      <MFCShield teamId={t.id} sigla={t.sigla} size={38} />
                      <div style={{ minWidth: 0, flex: 1, textAlign: 'left' }}>
                        <div style={{ fontSize: '13px', color: 'var(--c-text)', whiteSpace: 'nowrap', overflow: 'hidden', textOverflow: 'ellipsis' }}>
                          {t.nome}
                        </div>
                        <div style={{ fontSize: '10px', color: 'var(--c-text-dim)', letterSpacing: '0.1em' }}>
                          {t.sigla} · {t.formacao}
                        </div>
                      </div>
                    </div>
                    <div style={{ textAlign: 'right', flexShrink: 0 }}>
                      <div style={{ fontFamily: 'var(--font-vt)', fontSize: '22px', color: forcaColor(t.forca), lineHeight: 1 }}>
                        {t.forca}
                      </div>
                      <div style={{ fontSize: '9px', color: 'var(--c-text-dim)', letterSpacing: '0.1em' }}>OVR</div>
                    </div>
                  </button>
                );
              })}
            </div>
            <div style={{ marginTop: '14px', textAlign: 'center', fontSize: '11px', color: 'var(--c-text-ghost)', letterSpacing: '0.15em', textTransform: 'uppercase' }}>
              CLIQUE NUM CLUBE PARA INICIAR
            </div>
          </div>
        )}
      </div>
    </div>
  );
}
