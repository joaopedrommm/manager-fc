import { useState, useEffect } from 'react';

const FORMACOES = ['4-4-2','4-3-3','4-2-3-1','3-5-2','3-4-3','4-2-4','5-4-1','5-3-2'];

const LOGOS = {
  1: 'flamengo', 2: 'atletico-mg', 3: 'palmeiras', 4: 'fluminense',
  5: 'athletico-pr', 6: 'internacional', 7: 'sao-paulo', 8: 'gremio',
  9: 'botafogo', 10: 'vasco', 11: 'corinthians', 12: 'cruzeiro',
  13: 'bahia', 14: 'santos', 15: 'bragantino', 16: 'chapecoense',
  17: 'coritiba', 18: 'vitoria', 19: 'mirassol', 20: 'remo'
};

function logoSrc(id) {
  const arq = LOGOS[id] || 'flamengo';
  return arq === 'gremio' ? '/times/gremio.svg' : `/times/${arq}.png`;
}

export default function Dashboard({ clube, onProximoJogo, onFimTemporada, onSairdoJogo }) {
  const [estado, setEstado] = useState(null);
  const [tabela, setTabela] = useState([]);
  const [elenco, setElenco] = useState([]);
  const [view, setView] = useState('main');
  const [modal, setModal] = useState(null);
  const [qtdMelhorar, setQtdMelhorar] = useState(1);
  const [msg, setMsg] = useState('');

  const carregarEstado = () =>
    fetch('/api/estado').then(r => r.json()).then(setEstado);

  useEffect(() => { carregarEstado(); }, []);

  const abrirTabela = () => {
    fetch('/api/tabela').then(r => r.json()).then(data => {
      setTabela(data);
      setView('tabela');
    });
  };

  const abrirElenco = () => {
    fetch('/api/elenco').then(r => r.json()).then(data => {
      setElenco(data);
      setView('elenco');
    });
  };

  const salvarFormacao = (f) => {
    fetch('/api/formacao', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ formacao: f })
    }).then(() => { carregarEstado(); setModal(null); setMsg('Formacao alterada!'); });
  };

  const confirmarMelhora = () => {
    fetch('/api/melhorar', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ quantidade: qtdMelhorar })
    }).then(r => r.json()).then(data => {
      if (data.ok) { carregarEstado(); setModal(null); setMsg(`Elenco melhorado! Forca: ${data.forca}`); }
      else setMsg(data.erro || 'Erro');
    });
  };

  if (!estado) return (
    <div className="min-h-screen flex items-center justify-center"
      style={{ background: 'radial-gradient(ellipse at top, #0f2027, #111827)' }}>
      <div className="text-white text-lg font-semibold animate-pulse">Carregando...</div>
    </div>
  );

  const t = estado.meuTime;
  const custo = qtdMelhorar * 15;
  const progressoRodada = (estado.rodadaAtual / 38) * 100;

  return (
    <div className="min-h-screen text-white" style={{ background: 'radial-gradient(ellipse at top, #0f2027, #111827)' }}>

      {/* Header */}
      <div style={{ background: 'linear-gradient(135deg, #0f2027 0%, #1a3a4a 100%)', borderBottom: '1px solid rgba(255,255,255,0.08)' }}
        className="px-6 py-4">
        <div className="max-w-4xl mx-auto flex items-center justify-between">
          <div className="flex items-center gap-4">
            <img src={logoSrc(clube?.id)} alt={t.nome} className="w-14 h-14 object-contain drop-shadow-lg" />
            <div>
              <h1 className="text-2xl font-extrabold tracking-tight">{t.nome}</h1>
              <p className="text-gray-400 text-xs mt-0.5">{t.formacao} · Força {t.forca} · R${t.orcamento.toFixed(1)}M</p>
            </div>
          </div>
          <div className="text-right">
            <p className="text-4xl font-black text-white">{t.pontos}</p>
            <p className="text-gray-400 text-xs">pontos</p>
          </div>
        </div>

        {/* Barra de progresso da temporada */}
        <div className="max-w-4xl mx-auto mt-3">
          <div className="flex justify-between text-xs text-gray-500 mb-1">
            <span>Rodada {estado.rodadaAtual} de 38</span>
            <span>{Math.round(progressoRodada)}%</span>
          </div>
          <div className="h-1.5 bg-gray-700 rounded-full overflow-hidden">
            <div className="h-full bg-blue-500 rounded-full transition-all duration-500"
              style={{ width: `${progressoRodada}%` }} />
          </div>
        </div>
      </div>

      {msg && (
        <div className="bg-emerald-600/90 text-white text-sm text-center py-2 px-4 backdrop-blur">
          {msg} <button className="ml-4 underline opacity-70 hover:opacity-100" onClick={() => setMsg('')}>ok</button>
        </div>
      )}

      <div className="max-w-4xl mx-auto px-4 py-6">

        {/* Nav */}
        <div className="flex gap-2 mb-6">
          {[['main', 'Início'], ['tabela', 'Tabela'], ['elenco', 'Elenco']].map(([v, label]) => (
            <button key={v}
              onClick={() => v === 'tabela' ? abrirTabela() : v === 'elenco' ? abrirElenco() : setView('main')}
              className="px-5 py-2 rounded-full text-sm font-semibold transition-all duration-200"
              style={view === v
                ? { background: 'rgba(59,130,246,0.9)', color: 'white' }
                : { background: 'rgba(255,255,255,0.06)', color: '#9ca3af' }}>
              {label}
            </button>
          ))}
        </div>

        {/* MAIN */}
        {view === 'main' && (
          <div className="space-y-4">

            {/* Botão principal */}
            {estado.encerrado ? (
              <button onClick={onFimTemporada}
                className="w-full py-6 rounded-2xl text-xl font-extrabold transition-all duration-200 shadow-xl"
                style={{ background: 'linear-gradient(135deg, #d97706, #f59e0b)', color: '#111' }}>
                🏆 Ver Classificação Final
              </button>
            ) : (
              <button onClick={onProximoJogo}
                className="w-full py-6 rounded-2xl text-xl font-bold transition-all duration-200 shadow-xl hover:scale-[1.01]"
                style={{ background: 'linear-gradient(135deg, #1d4ed8, #3b82f6)' }}>
                ⚽ Jogar Rodada {estado.rodadaAtual + 1}
              </button>
            )}

            {/* Cards de stats */}
            <div className="grid grid-cols-4 gap-3">
              {[
                { label: 'Vitórias', val: t.vitorias, color: '#4ade80' },
                { label: 'Empates', val: t.empates, color: '#facc15' },
                { label: 'Derrotas', val: t.derrotas, color: '#f87171' },
                { label: 'Saldo', val: (t.saldo >= 0 ? '+' : '') + t.saldo, color: t.saldo >= 0 ? '#4ade80' : '#f87171' },
              ].map(({ label, val, color }) => (
                <div key={label} className="rounded-2xl p-4 text-center"
                  style={{ background: 'rgba(255,255,255,0.04)', border: '1px solid rgba(255,255,255,0.06)' }}>
                  <div className="text-3xl font-black" style={{ color }}>{val}</div>
                  <div className="text-gray-500 text-xs mt-1">{label}</div>
                </div>
              ))}
            </div>

            {/* Ações */}
            <div className="grid grid-cols-2 gap-3">
              <button onClick={() => setModal('formacao')}
                className="rounded-2xl p-5 text-left transition-all hover:scale-[1.02]"
                style={{ background: 'rgba(255,255,255,0.04)', border: '1px solid rgba(255,255,255,0.06)' }}>
                <div className="text-2xl mb-2">🗂</div>
                <div className="font-semibold text-sm">Formação</div>
                <div className="text-gray-400 text-xs mt-0.5">{t.formacao}</div>
              </button>
              <button onClick={() => setModal('melhorar')}
                className="rounded-2xl p-5 text-left transition-all hover:scale-[1.02]"
                style={{ background: 'rgba(255,255,255,0.04)', border: '1px solid rgba(255,255,255,0.06)' }}>
                <div className="text-2xl mb-2">📈</div>
                <div className="font-semibold text-sm">Melhorar Elenco</div>
                <div className="text-gray-400 text-xs mt-0.5">R${t.orcamento.toFixed(1)}M disponível</div>
              </button>
            </div>

            <button onClick={onSairdoJogo}
              className="w-full text-gray-600 hover:text-gray-400 text-xs text-center transition-all pt-2">
              Sair do jogo
            </button>
          </div>
        )}

        {/* TABELA */}
        {view === 'tabela' && (
          <div>
            <div className="space-y-1">
              {tabela.map((tm) => {
                const isMe = tm.id === estado.meuTime?.id;
                const borderColor = tm.pos === 1 ? '#f59e0b' : tm.pos <= 6 ? '#3b82f6' : tm.pos <= 12 ? '#22c55e' : tm.pos >= 17 ? '#ef4444' : 'transparent';
                return (
                  <div key={tm.id}
                    className="flex items-center gap-3 px-3 py-3 rounded-xl transition-all"
                    style={{
                      background: isMe ? 'rgba(59,130,246,0.12)' : 'rgba(255,255,255,0.03)',
                      borderLeft: `3px solid ${borderColor}`,
                      border: isMe ? '1px solid rgba(59,130,246,0.3)' : '1px solid transparent',
                      borderLeftColor: borderColor,
                    }}>
                    <span className="text-gray-500 text-xs w-5 text-right">{tm.pos}</span>
                    <img src={logoSrc(tm.id)} alt={tm.nome} className="w-6 h-6 object-contain" />
                    <span className="flex-1 text-sm font-semibold">
                      {tm.nome} {isMe && <span className="text-blue-400 text-xs">(você)</span>}
                    </span>
                    <span className="font-black text-sm w-8 text-right">{tm.pontos}</span>
                    <span className="text-gray-500 text-xs w-20 text-right">{tm.vitorias}V {tm.empates}E {tm.derrotas}D</span>
                    <span className={`text-xs w-8 text-right font-semibold ${tm.saldo >= 0 ? 'text-green-400' : 'text-red-400'}`}>
                      {tm.saldo > 0 ? '+' : ''}{tm.saldo}
                    </span>
                  </div>
                );
              })}
            </div>
            <div className="flex gap-4 mt-4 text-xs text-gray-600 justify-center flex-wrap">
              <span>🟡 Campeão</span>
              <span>🔵 Libertadores</span>
              <span>🟢 Sul-Americana</span>
              <span>🔴 Rebaixamento</span>
            </div>
          </div>
        )}

        {/* ELENCO */}
        {view === 'elenco' && (
          <div className="space-y-1">
            {elenco.map((j) => (
              <div key={j.numero}
                className="flex items-center gap-3 px-4 py-3 rounded-xl transition-all hover:bg-white/5"
                style={{ background: 'rgba(255,255,255,0.03)', border: '1px solid rgba(255,255,255,0.05)' }}>
                <span className="text-gray-600 text-xs w-5">{j.numero}</span>
                <span className="flex-1 text-sm font-semibold">{j.nome}</span>
                <span className="text-gray-500 text-xs">{j.tipo}</span>
                <span className="text-blue-400 font-black text-sm w-8 text-right">{j.habilidade}</span>
              </div>
            ))}
          </div>
        )}
      </div>

      {/* Modal Formacao */}
      {modal === 'formacao' && (
        <div className="fixed inset-0 flex items-center justify-center z-50"
          style={{ background: 'rgba(0,0,0,0.75)', backdropFilter: 'blur(4px)' }}>
          <div className="rounded-2xl p-6 w-80" style={{ background: '#1a2535', border: '1px solid rgba(255,255,255,0.1)' }}>
            <h3 className="font-bold text-lg mb-4">Escolha a Formação</h3>
            <div className="grid grid-cols-2 gap-2 mb-4">
              {FORMACOES.map(f => (
                <button key={f} onClick={() => salvarFormacao(f)}
                  className="py-3 rounded-xl text-sm font-semibold transition-all"
                  style={t.formacao === f
                    ? { background: '#2563eb' }
                    : { background: 'rgba(255,255,255,0.06)' }}>
                  {f}
                </button>
              ))}
            </div>
            <button onClick={() => setModal(null)} className="w-full text-gray-500 hover:text-white text-sm transition-all">Cancelar</button>
          </div>
        </div>
      )}

      {/* Modal Melhorar */}
      {modal === 'melhorar' && (
        <div className="fixed inset-0 flex items-center justify-center z-50"
          style={{ background: 'rgba(0,0,0,0.75)', backdropFilter: 'blur(4px)' }}>
          <div className="rounded-2xl p-6 w-80" style={{ background: '#1a2535', border: '1px solid rgba(255,255,255,0.1)' }}>
            <h3 className="font-bold text-lg mb-1">Melhorar Elenco</h3>
            <p className="text-gray-500 text-sm mb-5">R$15M por +1 de força</p>
            <div className="flex items-center gap-4 justify-center mb-4">
              <button onClick={() => setQtdMelhorar(q => Math.max(1, q - 1))}
                className="w-10 h-10 rounded-xl text-lg font-bold transition-all"
                style={{ background: 'rgba(255,255,255,0.08)' }}>−</button>
              <span className="text-3xl font-black w-12 text-center">{qtdMelhorar}</span>
              <button onClick={() => setQtdMelhorar(q => q + 1)}
                className="w-10 h-10 rounded-xl text-lg font-bold transition-all"
                style={{ background: 'rgba(255,255,255,0.08)' }}>+</button>
            </div>
            <p className="text-center text-xs text-gray-500 mb-5">
              Custo: R${custo.toFixed(1)}M · Disponível: R${t.orcamento.toFixed(1)}M
            </p>
            <button onClick={confirmarMelhora}
              className="w-full py-3 rounded-xl font-semibold mb-2 transition-all"
              style={{ background: 'linear-gradient(135deg, #1d4ed8, #3b82f6)' }}>
              Confirmar
            </button>
            <button onClick={() => setModal(null)} className="w-full text-gray-500 hover:text-white text-sm transition-all">Cancelar</button>
          </div>
        </div>
      )}
    </div>
  );
}