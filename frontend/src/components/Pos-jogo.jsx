import MFCShield from './MFCShield';

export default function PosJogo({ resultado, onAvancar }) {
  if (!resultado) return null;
  const mp     = resultado.minhaPartida;
  const rodada = resultado.rodada;
  const gols   = mp ? mp.eventos.filter(e => e.tipo === 'GOL')                              : [];
  const cards  = mp ? mp.eventos.filter(e => e.tipo === 'AMARELO' || e.tipo === 'VERMELHO') : [];

  let resTexto, resColor;
  if (!mp)                          { resTexto = 'SEM JOGO';            resColor = 'var(--c-text-dim)'; }
  else if (mp.golsCasa > mp.golsVisit) { resTexto = mp.siglaCasa + ' VENCEU'; resColor = 'var(--c-green-hi)'; }
  else if (mp.golsCasa < mp.golsVisit) { resTexto = mp.siglaVisit + ' VENCEU'; resColor = 'var(--c-red-hi)'; }
  else                              { resTexto = 'EMPATE';              resColor = 'var(--c-yellow-hi)'; }

  return (
    <div className="mfc-screen" style={{ background: 'var(--c-bg)', display: 'flex', flexDirection: 'column' }}>

      <div className="mfc-scoreboard">
        <div className="mfc-xs-upper-dim" style={{ marginBottom: '8px', letterSpacing: '0.18em' }}>
          RODADA {rodada} — RESULTADO FINAL
        </div>
        {mp && (
          <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'center', gap: '16px', marginBottom: '8px' }}>
            <div style={{ flex: 1, display: 'flex', alignItems: 'center', justifyContent: 'flex-end', gap: '10px' }}>
              <span style={{ fontSize: '15px', textTransform: 'uppercase', letterSpacing: '0.04em', color: 'var(--c-text)' }}>{mp.timeCasa}</span>
              <MFCShield teamId={mp.casaId} sigla={mp.siglaCasa} size={42} />
            </div>
            <div style={{ display: 'flex', alignItems: 'center', gap: '6px', flexShrink: 0 }}>
              <span className="mfc-score-digit">{mp.golsCasa}</span>
              <span className="mfc-score-sep">×</span>
              <span className="mfc-score-digit">{mp.golsVisit}</span>
            </div>
            <div style={{ flex: 1, display: 'flex', alignItems: 'center', justifyContent: 'flex-start', gap: '10px' }}>
              <MFCShield teamId={mp.visitId} sigla={mp.siglaVisit} size={42} />
              <span style={{ fontSize: '15px', textTransform: 'uppercase', letterSpacing: '0.04em', color: 'var(--c-text)' }}>{mp.timeVisit}</span>
            </div>
          </div>
        )}
        <div style={{ color: resColor, fontSize: '13px', letterSpacing: '0.18em', fontWeight: 'bold' }}>
          {resTexto}
        </div>
      </div>

      <div style={{ flex: 1, overflowY: 'auto' }}>
        <div style={{ maxWidth: '680px', margin: '0 auto', padding: '0 12px 16px' }}>

          {gols.length > 0 && (
            <div>
              <div className="mfc-section-header"><span>GOLS</span></div>
              <table className="mfc-table" style={{ width: '100%' }}>
                <tbody>
                  {gols.map((e, i) => (
                    <tr key={i}>
                      <td style={{ width: '38px', textAlign: 'center', color: 'var(--c-text-dim)', fontSize: '12px' }}>{e.minuto}'</td>
                      <td style={{ width: '40px', textAlign: 'center', color: 'var(--c-green-hi)', fontSize: '11px' }}>GOL</td>
                      <td style={{ color: 'var(--c-text-mid)' }}>{e.descricao}</td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          )}

          {cards.length > 0 && (
            <div>
              <div className="mfc-section-header"><span>CARTÕES</span></div>
              <table className="mfc-table" style={{ width: '100%' }}>
                <tbody>
                  {cards.map((e, i) => (
                    <tr key={i}>
                      <td style={{ width: '38px', textAlign: 'center', color: 'var(--c-text-dim)', fontSize: '12px' }}>{e.minuto}'</td>
                      <td style={{ width: '40px', textAlign: 'center', fontSize: '11px',
                        color: e.tipo === 'VERMELHO' ? 'var(--c-red-hi)' : 'var(--c-yellow-hi)' }}>
                        {e.tipo === 'VERMELHO' ? 'VM' : 'AM'}
                      </td>
                      <td style={{ color: 'var(--c-text-mid)' }}>{e.descricao}</td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          )}

          <div>
            <div className="mfc-section-header"><span>OUTROS RESULTADOS — ROD. {rodada}</span></div>
            <table className="mfc-table" style={{ width: '100%' }}>
              <tbody>
                {resultado.outrasPartidas.map((p, i) => (
                  <tr key={i}>
                    <td style={{ color: 'var(--c-text-mid)' }}>{p.timeCasa}</td>
                    <td style={{ textAlign: 'center', fontWeight: 'bold', color: 'var(--c-score)', width: '60px' }}>
                      {p.golsCasa} – {p.golsVisit}
                    </td>
                    <td style={{ color: 'var(--c-text-mid)', textAlign: 'right' }}>{p.timeVisit}</td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>

          <div style={{ marginTop: '16px' }}>
            <button onClick={onAvancar} className="mfc-btn mfc-btn-play">PRÓXIMA RODADA →</button>
          </div>
        </div>
      </div>
    </div>
  );
}
