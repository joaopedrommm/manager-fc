import { useState, useEffect } from 'react';
import MFCShield, { getTeamStyle } from './MFCShield';
import MFCFormation, { FORMACOES } from './MFCFormation';

function CalendarRow({ jogo, meuId, compact = false }) {
  const isMine = jogo.casaId === meuId || jogo.visitId === meuId;
  return (
    <div className="mfc-cal-row" style={{
      background: isMine ? 'var(--c-blue-bg)' : undefined,
      padding: compact ? '4px 8px' : '6px 10px',
    }}>
      <div className="mfc-cal-team mfc-cal-home">
        <span className="mfc-cal-team-name">{jogo.timeCasa}</span>
        <MFCShield teamId={jogo.casaId} sigla={jogo.siglaCasa} size={compact ? 18 : 22} />
      </div>
      <div className="mfc-cal-score">
        {jogo.jogado
          ? <span style={{ fontFamily: 'var(--font-vt)', fontSize: compact ? '16px' : '18px', color: 'var(--c-score)' }}>
              {jogo.golsCasa} – {jogo.golsVisit}
            </span>
          : <span style={{ fontFamily: 'var(--font-mono)', fontSize: '11px', color: 'var(--c-text-dim)' }}>vs</span>
        }
      </div>
      <div className="mfc-cal-team mfc-cal-away">
        <MFCShield teamId={jogo.visitId} sigla={jogo.siglaVisit} size={compact ? 18 : 22} />
        <span className="mfc-cal-team-name">{jogo.timeVisit}</span>
      </div>
    </div>
  );
}

export default function Dashboard({ clube, onProximoJogo, onFimTemporada, onSairdoJogo }) {
  const [estado, setEstado]         = useState(null);
  const [tabela, setTabela]         = useState([]);
  const [elenco, setElenco]         = useState([]);
  const [calendario, setCalendario] = useState([]);
  const [view, setView]             = useState('main');
  const [modal, setModal]           = useState(null);
  const [qtd, setQtd]               = useState(1);
  const [msg, setMsg]               = useState('');

  const loadEstado     = () => fetch('/api/estado').then(r => r.json()).then(setEstado);
  const loadTabela     = () => fetch('/api/tabela').then(r => r.json()).then(setTabela);
  const loadElenco     = () => fetch('/api/elenco').then(r => r.json()).then(setElenco);
  const loadCalendario = () => fetch('/api/calendario').then(r => r.json()).then(d => setCalendario(d.calendario || []));

  useEffect(() => { loadEstado(); loadTabela(); loadCalendario(); loadElenco(); }, []);
  useEffect(() => {
    if (view === 'tabela')     loadTabela();
    if (view === 'calendario') loadCalendario();
    if (view === 'elenco')     loadElenco();
  }, [view]);

  const salvarFormacao = (f) => {
    fetch('/api/formacao', { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify({ formacao: f }) })
      .then(() => { loadEstado(); setModal(null); setMsg('Formação: ' + f); });
  };

  const confirmarMelhora = () => {
    fetch('/api/melhorar', { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify({ quantidade: qtd }) })
      .then(r => r.json()).then(d => {
        if (d.ok) { loadEstado(); setModal(null); setMsg('Elenco melhorado! OVR: ' + d.forca); }
        else setMsg(d.erro || 'Erro');
      });
  };

  if (!estado) return (
    <div className="mfc-loading">
      <div className="mfc-spinner">■</div>
      <div className="mfc-loading-text">CARREGANDO...</div>
    </div>
  );

  const t = estado.meuTime;
  const custo = qtd * 15;
  const meuStyle = getTeamStyle(t.id);

  function zoneClass(pos) {
    if (pos === 1)  return 'mfc-zone-campeao';
    if (pos <= 6)   return 'mfc-zone-liberta';
    if (pos <= 12)  return 'mfc-zone-sulam';
    if (pos >= 17)  return 'mfc-zone-rebaixa';
    return '';
  }
  function zoneColor(pos) {
    if (pos === 1)  return 'var(--c-gold)';
    if (pos <= 6)   return 'var(--c-blue-hi)';
    if (pos <= 12)  return 'var(--c-green-hi)';
    if (pos >= 17)  return 'var(--c-red-hi)';
    return 'var(--c-text-ghost)';
  }

  const TABS = [
    { id: 'main',       label: 'INÍCIO' },
    { id: 'tabela',     label: 'TABELA' },
    { id: 'calendario', label: 'CALENDÁRIO' },
    { id: 'elenco',     label: 'ELENCO' },
  ];

  function MainPreviews() {
    const top = tabela.slice(0, 6);
    const meuPos = tabela.find(x => x.id === t.id);
    const meusJogos = [];
    for (const r of calendario) {
      for (const j of r.jogos) {
        if (j.meu) meusJogos.push(j);
      }
    }
    const proximosJogos = meusJogos.filter(j => !j.jogado).slice(0, 3);
    const ultimosJogos  = meusJogos.filter(j => j.jogado).slice(-3).reverse();
    const topJogadores  = (elenco.slice().sort((a, b) => b.habilidade - a.habilidade)).slice(0, 5);

    return (
      <div className="mfc-main-grid">
        <div className="mfc-preview-card mfc-span-2">
          <div className="mfc-preview-head">
            <span>PRÓXIMOS JOGOS</span>
            <button className="mfc-btn-ghost" onClick={() => setView('calendario')}>VER TUDO →</button>
          </div>
          <div className="mfc-preview-body">
            {proximosJogos.length === 0 && (
              <div className="mfc-xs-upper-dim" style={{ padding: '14px', textAlign: 'center' }}>TEMPORADA ENCERRADA</div>
            )}
            {proximosJogos.map((j, i) => <CalendarRow key={i} jogo={j} meuId={t.id} compact />)}
          </div>
        </div>

        <div className="mfc-preview-card">
          <div className="mfc-preview-head">
            <span>MINHA POSIÇÃO</span>
            <button className="mfc-btn-ghost" onClick={() => setView('tabela')}>TABELA →</button>
          </div>
          <div className="mfc-preview-body" style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', padding: '12px 14px' }}>
            <div style={{ fontFamily: 'var(--font-vt)', fontSize: '48px', color: zoneColor(meuPos?.pos || 20), lineHeight: 1 }}>
              {meuPos?.pos || '–'}º
            </div>
            <div style={{ textAlign: 'right' }}>
              <div style={{ fontFamily: 'var(--font-vt)', fontSize: '28px', color: 'var(--c-score)' }}>
                {t.pontos} <span style={{ fontSize: '12px', color: 'var(--c-text-dim)' }}>PTS</span>
              </div>
              <div className="mfc-xs-upper-dim">{t.vitorias}V · {t.empates}E · {t.derrotas}D</div>
            </div>
          </div>
        </div>

        <div className="mfc-preview-card">
          <div className="mfc-preview-head"><span>TOP 6 — LIBERTADORES</span></div>
          <div className="mfc-preview-body">
            {top.length === 0 && (
              <div className="mfc-xs-upper-dim" style={{ padding: '14px', textAlign: 'center' }}>JOGUE A RODADA 1</div>
            )}
            {top.map(tm => {
              const isMe = tm.id === t.id;
              return (
                <div key={tm.id} className="mfc-tbl-mini-row" style={{
                  borderLeft: `3px solid ${zoneColor(tm.pos)}`,
                  background: isMe ? 'var(--c-blue-bg)' : undefined,
                }}>
                  <span className="mfc-tbl-mini-pos">{tm.pos}</span>
                  <MFCShield teamId={tm.id} sigla={tm.sigla} size={20} />
                  <span className="mfc-tbl-mini-name" style={{ color: isMe ? 'var(--c-gold)' : 'var(--c-text-mid)' }}>
                    {tm.nome}
                  </span>
                  <span className="mfc-tbl-mini-pts">{tm.pontos}</span>
                </div>
              );
            })}
          </div>
        </div>

        <div className="mfc-preview-card">
          <div className="mfc-preview-head"><span>ÚLTIMOS JOGOS</span></div>
          <div className="mfc-preview-body">
            {ultimosJogos.length === 0 && (
              <div className="mfc-xs-upper-dim" style={{ padding: '14px', textAlign: 'center' }}>AINDA SEM JOGOS</div>
            )}
            {ultimosJogos.map((j, i) => <CalendarRow key={i} jogo={j} meuId={t.id} compact />)}
          </div>
        </div>

        <div className="mfc-preview-card">
          <div className="mfc-preview-head">
            <span>DESTAQUES DO ELENCO</span>
            <button className="mfc-btn-ghost" onClick={() => setView('elenco')}>VER →</button>
          </div>
          <div className="mfc-preview-body">
            {topJogadores.map(j => (
              <div key={j.numero} className="mfc-tbl-mini-row">
                <span className="mfc-tbl-mini-pos">{j.numero}</span>
                <span className="mfc-tbl-mini-name" style={{ color: 'var(--c-text-mid)' }}>{j.nome}</span>
                <span className="mfc-xs-upper-dim" style={{ marginRight: '8px' }}>{j.tipo}</span>
                <span className="mfc-tbl-mini-pts" style={{
                  color: j.habilidade >= 85 ? 'var(--c-gold)' : j.habilidade >= 75 ? 'var(--c-text)' : 'var(--c-text-dim)'
                }}>{j.habilidade}</span>
              </div>
            ))}
          </div>
        </div>

        <div className="mfc-preview-card">
          <div className="mfc-preview-head">
            <span>FORMAÇÃO ATUAL</span>
            <button className="mfc-btn-ghost" onClick={() => setModal('formacao')}>ALTERAR →</button>
          </div>
          <div className="mfc-preview-body" style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-around', padding: '10px' }}>
            <MFCFormation name={t.formacao} color={meuStyle.primary} highlight={true} width={100} height={130} />
            <div style={{ textAlign: 'center' }}>
              <div style={{ fontFamily: 'var(--font-vt)', fontSize: '28px', color: 'var(--c-gold)', lineHeight: 1 }}>{t.formacao}</div>
              <div className="mfc-xs-upper-dim" style={{ marginTop: '4px' }}>esquema</div>
              <div style={{ fontFamily: 'var(--font-vt)', fontSize: '22px', color: 'var(--c-text)', marginTop: '10px' }}>{t.forca}</div>
              <div className="mfc-xs-upper-dim">OVR</div>
            </div>
          </div>
        </div>

        <div className="mfc-preview-card">
          <div className="mfc-preview-head">
            <span>FINANÇAS</span>
            <button className="mfc-btn-ghost" onClick={() => setModal('melhorar')}>MELHORAR →</button>
          </div>
          <div className="mfc-preview-body" style={{ padding: '14px', textAlign: 'center' }}>
            <div style={{ fontFamily: 'var(--font-vt)', fontSize: '32px', color: 'var(--c-gold)' }}>
              R${t.orcamento.toFixed(1)}M
            </div>
            <div className="mfc-xs-upper-dim" style={{ marginTop: '4px' }}>orçamento disponível</div>
            <div style={{ marginTop: '10px', fontSize: '11px', color: 'var(--c-text-dim)' }}>R$15M = +1 OVR</div>
          </div>
        </div>
      </div>
    );
  }

  return (
    <div className="mfc-screen" style={{ background: 'var(--c-bg)', display: 'flex', flexDirection: 'column' }}>

      <div className="mfc-statusbar" style={{ borderBottom: `2px solid ${meuStyle.primary}` }}>
        <div style={{ display: 'flex', alignItems: 'center', gap: '12px' }}>
          <MFCShield teamId={t.id} sigla={t.sigla} size={42} />
          <div style={{ display: 'flex', flexDirection: 'column', gap: '4px' }}>
            <div className="mfc-statusbar-name" style={{ color: meuStyle.primary }}>{t.nome}</div>
            <div style={{ display: 'flex', gap: '6px', flexWrap: 'wrap' }}>
              {[t.formacao, 'OVR ' + t.forca, 'R$' + t.orcamento.toFixed(1) + 'M'].map(c => (
                <span key={c} className="mfc-chip">{c}</span>
              ))}
            </div>
          </div>
        </div>
        <div style={{ textAlign: 'right' }}>
          <div className="mfc-statusbar-pts">{t.pontos} <span style={{ fontSize: '12px', color: 'var(--c-text-dim)' }}>PTS</span></div>
          <div className="mfc-xs-upper-dim">ROD. {estado.rodadaAtual}/38</div>
        </div>
      </div>

      {msg && (
        <div className="mfc-alert-success">
          <span>{msg}</span>
          <button className="mfc-btn mfc-btn-ghost" style={{ padding: '0 6px', fontSize: '11px' }} onClick={() => setMsg('')}>OK</button>
        </div>
      )}

      <div className="mfc-tabs">
        {TABS.map(tab => (
          <button key={tab.id}
            className={'mfc-tab' + (view === tab.id ? ' active' : '')}
            onClick={() => setView(tab.id)}>{tab.label}</button>
        ))}
        <div style={{ flex: 1 }} />
        <button className="mfc-tab mfc-btn-ghost" onClick={onSairdoJogo}
          style={{ fontSize: '11px', color: 'var(--c-text-dim)' }}>SAIR</button>
      </div>

      <div style={{ flex: 1, overflowY: 'auto' }}>

        {view === 'main' && (
          <div style={{ maxWidth: '1100px', margin: '0 auto', padding: '14px 16px', display: 'flex', flexDirection: 'column', gap: '12px' }}>
            {estado.encerrado ? (
              <button onClick={onFimTemporada} className="mfc-btn mfc-btn-final">★ VER CLASSIFICAÇÃO FINAL</button>
            ) : (
              <button onClick={onProximoJogo} className="mfc-btn mfc-btn-play"
                style={{ borderColor: meuStyle.primary, color: meuStyle.primary }}>
                ▶ JOGAR RODADA {estado.rodadaAtual + 1}
              </button>
            )}
            <MainPreviews />
          </div>
        )}

        {view === 'tabela' && (
          <div>
            <div className="mfc-section-header">
              <span>TABELA DE CLASSIFICAÇÃO</span>
              <span className="mfc-xs-upper-dim">RODADA {estado.rodadaAtual}/38</span>
            </div>
            <div style={{ padding: '0 12px 16px' }}>
              <table className="mfc-table" style={{ width: '100%' }}>
                <thead>
                  <tr>
                    <th style={{ width: '32px' }}>#</th>
                    <th style={{ width: '34px' }}></th>
                    <th style={{ textAlign: 'left', minWidth: '120px' }}>CLUBE</th>
                    <th>PTS</th><th>J</th><th>V</th><th>E</th><th>D</th><th>GP</th><th>GC</th><th>SG</th>
                  </tr>
                </thead>
                <tbody>
                  {tabela.map(tm => {
                    const isMe = tm.id === t.id;
                    const jogos = tm.vitorias + tm.empates + tm.derrotas;
                    return (
                      <tr key={tm.id} className={zoneClass(tm.pos)}
                        style={{ background: isMe ? 'var(--c-blue-bg)' : undefined }}>
                        <td style={{ textAlign: 'center', color: 'var(--c-text-dim)' }}>{tm.pos}</td>
                        <td style={{ textAlign: 'center', padding: '2px' }}>
                          <MFCShield teamId={tm.id} sigla={tm.sigla} size={22} />
                        </td>
                        <td style={{ fontWeight: isMe ? 'bold' : 'normal', color: isMe ? 'var(--c-gold)' : 'var(--c-text-mid)' }}>
                          {isMe ? '▶ ' : '  '}{tm.nome}
                        </td>
                        <td style={{ textAlign: 'center', fontWeight: 'bold', color: 'var(--c-text)' }}>{tm.pontos}</td>
                        <td style={{ textAlign: 'center', color: 'var(--c-text-dim)' }}>{jogos}</td>
                        <td style={{ textAlign: 'center', color: 'var(--c-green-hi)' }}>{tm.vitorias}</td>
                        <td style={{ textAlign: 'center', color: 'var(--c-yellow-hi)' }}>{tm.empates}</td>
                        <td style={{ textAlign: 'center', color: 'var(--c-red-hi)' }}>{tm.derrotas}</td>
                        <td style={{ textAlign: 'center', color: 'var(--c-text-dim)' }}>{tm.gm}</td>
                        <td style={{ textAlign: 'center', color: 'var(--c-text-dim)' }}>{tm.gc}</td>
                        <td style={{ textAlign: 'center', color: tm.saldo >= 0 ? 'var(--c-green-hi)' : 'var(--c-red-hi)' }}>
                          {tm.saldo > 0 ? '+' : ''}{tm.saldo}
                        </td>
                      </tr>
                    );
                  })}
                </tbody>
              </table>
              <div style={{ display: 'flex', gap: '16px', marginTop: '10px', flexWrap: 'wrap' }}>
                {[
                  { label: 'Campeão',       color: 'var(--c-gold)' },
                  { label: 'Libertadores',  color: 'var(--c-blue-hi)' },
                  { label: 'Sul-Americana', color: 'var(--c-green-hi)' },
                  { label: 'Rebaixamento',  color: 'var(--c-red-hi)' },
                ].map(({ label, color }) => (
                  <span key={label} style={{ borderLeft: `3px solid ${color}`, paddingLeft: '6px', fontSize: '11px', color: 'var(--c-text-dim)' }}>
                    {label}
                  </span>
                ))}
              </div>
            </div>
          </div>
        )}

        {view === 'calendario' && (
          <div>
            <div className="mfc-section-header">
              <span>CALENDÁRIO — 38 RODADAS</span>
              <span className="mfc-xs-upper-dim">PRÓXIMA: ROD. {Math.min(38, estado.rodadaAtual + 1)}</span>
            </div>
            <div style={{ padding: '8px 12px 16px', display: 'flex', flexDirection: 'column', gap: '14px' }}>
              {calendario.map(r => {
                const isProx = r.rodada === estado.rodadaAtual + 1;
                const isPast = r.rodada <= estado.rodadaAtual;
                return (
                  <div key={r.rodada} className="mfc-cal-rodada"
                    style={{ borderColor: isProx ? meuStyle.primary : 'var(--c-border)' }}>
                    <div className="mfc-cal-rodada-head" style={{
                      color: isProx ? meuStyle.primary : isPast ? 'var(--c-text-dim)' : 'var(--c-text)',
                    }}>
                      <span>RODADA {r.rodada}</span>
                      <span style={{ fontSize: '10px' }}>
                        {isProx ? '● PRÓXIMA' : isPast ? '✓ JOGADA' : 'futura'}
                      </span>
                    </div>
                    <div className="mfc-cal-rodada-jogos">
                      {r.jogos.map((j, i) => <CalendarRow key={i} jogo={j} meuId={t.id} />)}
                    </div>
                  </div>
                );
              })}
            </div>
          </div>
        )}

        {view === 'elenco' && (
          <div>
            <div className="mfc-section-header">
              <span>ELENCO — {t.nome.toUpperCase()}</span>
              <span className="mfc-xs-upper-dim">OVR MÉD.: {t.forca}</span>
            </div>
            <div style={{ padding: '0 12px 16px' }}>
              <table className="mfc-table" style={{ width: '100%' }}>
                <thead>
                  <tr>
                    <th style={{ width: '40px' }}>#</th>
                    <th style={{ textAlign: 'left' }}>NOME</th>
                    <th style={{ width: '58px' }}>POS</th>
                    <th style={{ width: '58px' }}>HAB</th>
                  </tr>
                </thead>
                <tbody>
                  {elenco.map(j => (
                    <tr key={j.numero}>
                      <td style={{ textAlign: 'center', color: 'var(--c-text-dim)' }}>{j.numero}</td>
                      <td style={{ color: 'var(--c-text-mid)' }}>{j.nome}</td>
                      <td style={{ textAlign: 'center', fontSize: '11px', color: 'var(--c-text-dim)' }}>{j.tipo}</td>
                      <td style={{ textAlign: 'center', fontWeight: 'bold',
                        color: j.habilidade >= 85 ? 'var(--c-gold)' : j.habilidade >= 75 ? 'var(--c-text)' : 'var(--c-text-dim)' }}>
                        {j.habilidade}
                      </td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          </div>
        )}
      </div>

      {modal === 'formacao' && (
        <div className="mfc-modal-overlay" onClick={() => setModal(null)}>
          <div className="mfc-modal" onClick={e => e.stopPropagation()} style={{ maxWidth: '520px' }}>
            <div className="mfc-modal-title">SELECIONAR FORMAÇÃO</div>
            <div className="mfc-formacao-grid">
              {FORMACOES.map(f => {
                const sel = t.formacao === f;
                return (
                  <button key={f} className="mfc-formacao-card"
                    onClick={() => salvarFormacao(f)}
                    style={{
                      borderColor: sel ? meuStyle.primary : 'var(--c-border-hi)',
                      background: sel ? 'var(--c-gold-bg)' : 'var(--c-panel)',
                    }}>
                    <MFCFormation name={f} color={sel ? meuStyle.primary : 'var(--c-text-mid)'} highlight={sel} width={84} height={108} />
                    <div style={{ marginTop: '4px', color: sel ? meuStyle.primary : 'var(--c-text)', fontSize: '13px', letterSpacing: '0.06em' }}>{f}</div>
                  </button>
                );
              })}
            </div>
            <button className="mfc-btn mfc-btn-ghost" onClick={() => setModal(null)}
              style={{ width: '100%', textAlign: 'center', marginTop: '10px' }}>CANCELAR</button>
          </div>
        </div>
      )}

      {modal === 'melhorar' && (
        <div className="mfc-modal-overlay" onClick={() => setModal(null)}>
          <div className="mfc-modal" onClick={e => e.stopPropagation()}>
            <div className="mfc-modal-title">MELHORAR ELENCO</div>
            <div className="mfc-info-row">
              <span className="mfc-xs-upper-dim">OVR ATUAL</span>
              <span style={{ color: 'var(--c-gold)' }}>{t.forca}</span>
            </div>
            <div className="mfc-info-row">
              <span className="mfc-xs-upper-dim">APÓS MELHORA</span>
              <span style={{ color: 'var(--c-green-hi)' }}>{t.forca + qtd}</span>
            </div>
            <div className="mfc-counter">
              <button className="mfc-counter-btn" onClick={() => setQtd(q => Math.max(1, q - 1))}>−</button>
              <span className="mfc-counter-val">{qtd}</span>
              <button className="mfc-counter-btn" onClick={() => setQtd(q => q + 1)}>+</button>
            </div>
            <div className="mfc-info-row" style={{ marginBottom: '12px' }}>
              <span className="mfc-xs-upper-dim">CUSTO: <span style={{ color: 'var(--c-red-hi)' }}>R${custo.toFixed(1)}M</span></span>
              <span className="mfc-xs-upper-dim">DISP.: <span style={{ color: 'var(--c-text)' }}>R${t.orcamento.toFixed(1)}M</span></span>
            </div>
            <button onClick={confirmarMelhora} className="mfc-btn"
              style={{ width: '100%', textAlign: 'center', marginBottom: '6px', borderColor: 'var(--c-green)', color: 'var(--c-green-hi)', background: 'var(--c-green-bg)', padding: '10px' }}>
              CONFIRMAR
            </button>
            <button className="mfc-btn mfc-btn-ghost" onClick={() => setModal(null)}
              style={{ width: '100%', textAlign: 'center' }}>CANCELAR</button>
          </div>
        </div>
      )}
    </div>
  );
}
