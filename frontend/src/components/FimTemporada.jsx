import { useState, useEffect } from 'react';
import MFCShield from './MFCShield';

export default function FimTemporada({ meuTimeId, onVoltar }) {
  const [tabela, setTabela] = useState([]);
  useEffect(() => { fetch('/api/tabela').then(r => r.json()).then(setTabela); }, []);

  const campeao = tabela[0];

  function getZone(pos) {
    if (pos === 1)  return { label: 'CAMPEÃO',       cls: 'mfc-zone-campeao', color: 'var(--c-gold)' };
    if (pos <= 6)   return { label: 'LIBERTADORES',  cls: 'mfc-zone-liberta', color: 'var(--c-blue-hi)' };
    if (pos <= 12)  return { label: 'SUL-AMERICANA', cls: 'mfc-zone-sulam',   color: 'var(--c-green-hi)' };
    if (pos >= 17)  return { label: 'REBAIXADO',     cls: 'mfc-zone-rebaixa', color: 'var(--c-red-hi)' };
    return { label: '', cls: '', color: 'var(--c-text-ghost)' };
  }

  return (
    <div className="mfc-screen" style={{ background: 'var(--c-bg)', display: 'flex', flexDirection: 'column' }}>

      <div className="mfc-section-header" style={{ padding: '12px 16px' }}>
        <span style={{ color: 'var(--c-gold)', letterSpacing: '0.18em' }}>
          BRASILEIRÃO SÉRIE A 2026 — TEMPORADA ENCERRADA
        </span>
      </div>

      {campeao && (
        <div className="mfc-champion-banner">
          <div className="mfc-xs-upper-dim" style={{ letterSpacing: '0.3em', marginBottom: '6px' }}>★ CAMPEÃO BRASILEIRO ★</div>
          <div className="mfc-champion-name">{campeao.nome.toUpperCase()}</div>
          <div className="mfc-xs-upper-dim" style={{ marginTop: '6px', letterSpacing: '0.1em' }}>
            {campeao.pontos} PTS · {campeao.vitorias}V {campeao.empates}E {campeao.derrotas}D · SG {campeao.saldo >= 0 ? '+' : ''}{campeao.saldo}
          </div>
        </div>
      )}

      <div className="mfc-section-header"><span>CLASSIFICAÇÃO FINAL</span></div>

      <div style={{ flex: 1, overflowY: 'auto' }}>
        <div style={{ overflowX: 'auto', padding: '0 12px 16px' }}>
          <table className="mfc-table" style={{ width: '100%' }}>
            <thead>
              <tr>
                <th style={{ width: '32px' }}>#</th>
                <th style={{ width: '34px' }}></th>
                <th style={{ textAlign: 'left', minWidth: '110px' }}>CLUBE</th>
                <th>PTS</th><th>V</th><th>E</th><th>D</th><th>SG</th>
                <th style={{ minWidth: '80px' }}>ZONA</th>
              </tr>
            </thead>
            <tbody>
              {tabela.map(tm => {
                const z    = getZone(tm.pos);
                const isMe = tm.id === meuTimeId;
                return (
                  <tr key={tm.id} className={z.cls}
                    style={{ background: isMe ? 'var(--c-blue-bg)' : undefined }}>
                    <td style={{ textAlign: 'center', color: 'var(--c-text-dim)' }}>{tm.pos}</td>
                    <td style={{ textAlign: 'center', padding: '2px' }}>
                      <MFCShield teamId={tm.id} sigla={tm.sigla} size={22} />
                    </td>
                    <td style={{ fontWeight: isMe ? 'bold' : 'normal', color: isMe ? 'var(--c-gold)' : 'var(--c-text-mid)' }}>
                      {isMe ? '▶ ' : '  '}{tm.nome}
                      {isMe && <span style={{ color: 'var(--c-blue-hi)', fontSize: '10px', marginLeft: '4px' }}>(você)</span>}
                    </td>
                    <td style={{ textAlign: 'center', fontWeight: 'bold' }}>{tm.pontos}</td>
                    <td style={{ textAlign: 'center', color: 'var(--c-green-hi)' }}>{tm.vitorias}</td>
                    <td style={{ textAlign: 'center', color: 'var(--c-yellow-hi)' }}>{tm.empates}</td>
                    <td style={{ textAlign: 'center', color: 'var(--c-red-hi)' }}>{tm.derrotas}</td>
                    <td style={{ textAlign: 'center', color: tm.saldo >= 0 ? 'var(--c-green-hi)' : 'var(--c-red-hi)' }}>
                      {tm.saldo > 0 ? '+' : ''}{tm.saldo}
                    </td>
                    <td style={{ textAlign: 'center', fontSize: '10px', color: z.color, letterSpacing: '0.04em' }}>
                      {z.label}
                    </td>
                  </tr>
                );
              })}
            </tbody>
          </table>
          <div style={{ marginTop: '16px' }}>
            <button onClick={onVoltar} className="mfc-btn"
              style={{ width: '100%', textAlign: 'center', padding: '12px' }}>← VOLTAR AO MENU</button>
          </div>
        </div>
      </div>
    </div>
  );
}
