import { useState, useEffect, useRef } from 'react';
import MFCShield from './MFCShield';

export default function Simulacao({ onAvancar }) {
  const [dados, setDados]                     = useState(null);
  const [loading, setLoading]                 = useState(true);
  const [eventosVisiveis, setEventosVisiveis] = useState([]);
  const [placarCasa, setPlacarCasa]           = useState(0);
  const [placarVisit, setPlacarVisit]         = useState(0);
  const [finalizado, setFinalizado]           = useState(false);
  const logRef      = useRef(null);
  const animandoRef = useRef(false);
  const fetchedRef  = useRef(false);

  useEffect(() => {
    if (fetchedRef.current) return;
    fetchedRef.current = true;
    fetch('/api/jogar-rodada', { method: 'POST' })
      .then(r => r.json())
      .then(data => { setDados(data); setLoading(false); });
  }, []);

  useEffect(() => {
    if (!dados || loading || animandoRef.current) return;
    if (!dados.minhaPartida) { setFinalizado(true); return; }
    animandoRef.current = true;
    const eventos = dados.minhaPartida.eventos;
    if (!eventos.length) { setFinalizado(true); return; }

    let golsCasa = 0, golsVisit = 0, idx = 0;
    const simSpeed = 700;

    const tick = () => {
      if (idx >= eventos.length) {
        setPlacarCasa(dados.minhaPartida.golsCasa);
        setPlacarVisit(dados.minhaPartida.golsVisit);
        setTimeout(() => setFinalizado(true), 500);
        return;
      }
      const e = eventos[idx++];
      if (e.tipo === 'GOL') {
        if (e.time === dados.minhaPartida.timeCasa) golsCasa++;
        else golsVisit++;
        setPlacarCasa(golsCasa);
        setPlacarVisit(golsVisit);
      }
      setEventosVisiveis(prev => [...prev, e]);
      setTimeout(() => { if (logRef.current) logRef.current.scrollTop = logRef.current.scrollHeight; }, 40);
      setTimeout(tick, simSpeed);
    };
    setTimeout(tick, 400);
  }, [dados, loading]);

  if (loading) return (
    <div className="mfc-loading mfc-pitch-bg">
      <div className="mfc-spinner" style={{ color: 'var(--c-score)' }}>■</div>
      <div className="mfc-loading-text" style={{ letterSpacing: '0.25em' }}>SIMULANDO PARTIDA...</div>
    </div>
  );

  if (!dados.minhaPartida) return (
    <div className="mfc-loading">
      <div className="mfc-xs-upper-dim" style={{ marginBottom: '20px' }}>FOLGA NESTA RODADA</div>
      <button onClick={() => onAvancar(dados)} className="mfc-btn mfc-btn-play">CONTINUAR →</button>
    </div>
  );

  const mp = dados.minhaPartida;

  return (
    <div className="mfc-screen" style={{ background: 'var(--c-bg)', display: 'flex', flexDirection: 'column' }}>

      <div className="mfc-scoreboard">
        <div className="mfc-xs-upper-dim" style={{ marginBottom: '10px', letterSpacing: '0.2em' }}>
          RODADA {dados.rodada} — CAMPEONATO BRASILEIRO
        </div>
        <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'center', gap: '16px' }}>
          <div style={{ flex: 1, display: 'flex', alignItems: 'center', justifyContent: 'flex-end', gap: '10px' }}>
            <div style={{ textAlign: 'right' }}>
              <div style={{ fontSize: '15px', textTransform: 'uppercase', letterSpacing: '0.04em', color: 'var(--c-text)' }}>{mp.timeCasa}</div>
              <div className="mfc-xs-upper-dim">{mp.siglaCasa}</div>
            </div>
            <MFCShield teamId={mp.casaId} sigla={mp.siglaCasa} size={48} />
          </div>
          <div style={{ display: 'flex', alignItems: 'center', gap: '6px', flexShrink: 0 }}>
            <span className="mfc-score-digit">{placarCasa}</span>
            <span className="mfc-score-sep">×</span>
            <span className="mfc-score-digit">{placarVisit}</span>
          </div>
          <div style={{ flex: 1, display: 'flex', alignItems: 'center', justifyContent: 'flex-start', gap: '10px' }}>
            <MFCShield teamId={mp.visitId} sigla={mp.siglaVisit} size={48} />
            <div style={{ textAlign: 'left' }}>
              <div style={{ fontSize: '15px', textTransform: 'uppercase', letterSpacing: '0.04em', color: 'var(--c-text)' }}>{mp.timeVisit}</div>
              <div className="mfc-xs-upper-dim">{mp.siglaVisit}</div>
            </div>
          </div>
        </div>
      </div>

      <div className="mfc-section-header">
        <span>LOG DE PARTIDA</span>
        {!finalizado
          ? <span style={{ color: 'var(--c-green-hi)', fontSize: '11px', animation: 'mfc-blink 1.2s step-start infinite' }}>● AO VIVO</span>
          : <span className="mfc-xs-upper-dim">ENCERRADO</span>
        }
      </div>

      <div ref={logRef} className="mfc-event-log" style={{ flex: 1 }}>
        {eventosVisiveis.map((e, i) => {
          if (e.tipo === 'INTERVALO') return (
            <div key={i} className="mfc-event-interval">— INTERVALO — {e.descricao}</div>
          );
          const tipo = e.tipo;
          const isCasa = e.sigla === mp.siglaCasa;
          return (
            <div key={i} className={'mfc-event' + (tipo === 'GOL' ? ' ev-gol' : tipo === 'AMARELO' ? ' ev-am' : ' ev-vm')}
              style={{ flexDirection: isCasa ? 'row' : 'row-reverse' }}>
              <span className="mfc-ev-min">{e.minuto}'</span>
              <span className={'mfc-ev-badge ' + (tipo === 'GOL' ? 'badge-gol' : tipo === 'AMARELO' ? 'badge-am' : 'badge-vm')}>
                {tipo === 'GOL' ? 'GOL' : tipo === 'AMARELO' ? 'AM' : 'VM'}
              </span>
              <span className="mfc-ev-desc" style={{ textAlign: isCasa ? 'left' : 'right' }}>
                <span style={{ color: 'var(--c-text-dim)', fontSize: '10px', letterSpacing: '0.1em', marginRight: isCasa ? '5px' : 0, marginLeft: isCasa ? 0 : '5px' }}>
                  {e.sigla}
                </span>
                {e.descricao}
              </span>
            </div>
          );
        })}
        {!finalizado && (
          <div className="mfc-event" style={{ justifyContent: 'center', color: 'var(--c-text-ghost)', fontSize: '12px', animation: 'mfc-blink 1.4s step-start infinite' }}>
            em andamento...
          </div>
        )}
      </div>

      {finalizado && (
        <div style={{ borderTop: '1px solid var(--c-border)' }}>
          <div className="mfc-section-header"><span>OUTROS RESULTADOS</span></div>
          <div className="mfc-outros-grid" style={{ padding: '8px 12px' }}>
            {dados.outrasPartidas.map((p, i) => (
              <div key={i} className="mfc-outro-item">
                <span className="mfc-outro-team">{p.timeCasa}</span>
                <span className="mfc-outro-placar">{p.golsCasa}–{p.golsVisit}</span>
                <span className="mfc-outro-team" style={{ textAlign: 'right' }}>{p.timeVisit}</span>
              </div>
            ))}
          </div>
          <div style={{ padding: '8px 12px 14px' }}>
            <button onClick={() => onAvancar(dados)} className="mfc-btn mfc-btn-play">
              VER RESUMO DA RODADA →
            </button>
          </div>
        </div>
      )}
    </div>
  );
}
