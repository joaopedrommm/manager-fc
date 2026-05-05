import { useState, useEffect } from 'react';

const FORMACOES = ['4-4-2','4-3-3','4-2-3-1','3-5-2','3-4-3','4-2-4','5-4-1','5-3-2'];

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

  if (!estado) return <div className="min-h-screen bg-gray-900 flex items-center justify-center text-white">Carregando...</div>;

  const t = estado.meuTime;
  const custo = qtdMelhorar * 15;

  return (
    <div className="min-h-screen bg-gray-900 text-white">
      {/* Header */}
      <div className="bg-gray-800 border-b border-gray-700 px-6 py-4 flex items-center justify-between">
        <div>
          <h1 className="text-xl font-extrabold text-blue-400">{t.nome}</h1>
          <p className="text-gray-400 text-sm">{t.formacao} · Forca {t.forca} · R${t.orcamento.toFixed(1)}M</p>
        </div>
        <div className="text-right">
          <p className="text-2xl font-bold">{t.pontos} pts</p>
          <p className="text-gray-400 text-sm">Rodada {estado.rodadaAtual}/38</p>
        </div>
      </div>

      {msg && (
        <div className="bg-green-700 text-white text-sm text-center py-2 px-4">
          {msg} <button className="ml-4 underline" onClick={() => setMsg('')}>ok</button>
        </div>
      )}

      <div className="max-w-4xl mx-auto px-4 py-6">
        {/* Nav */}
        <div className="flex gap-2 mb-6 flex-wrap">
          {[['main','Inicio'],['tabela','Tabela'],['elenco','Elenco']].map(([v, label]) => (
            <button
              key={v}
              onClick={() => v === 'tabela' ? abrirTabela() : v === 'elenco' ? abrirElenco() : setView('main')}
              className={`px-4 py-2 rounded-lg text-sm font-semibold transition-all ${view === v ? 'bg-blue-600 text-white' : 'bg-gray-700 hover:bg-gray-600 text-gray-300'}`}
            >
              {label}
            </button>
          ))}
        </div>

        {/* MAIN */}
        {view === 'main' && (
          <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
            {estado.encerrado ? (
              <button
                onClick={onFimTemporada}
                className="col-span-2 bg-yellow-500 hover:bg-yellow-400 text-gray-900 rounded-2xl py-6 text-xl font-extrabold shadow-lg transition-all"
              >
                🏆 Ver Classificacao Final
              </button>
            ) : (
              <button
                onClick={onProximoJogo}
                className="col-span-2 bg-blue-600 hover:bg-blue-500 rounded-2xl py-6 text-xl font-bold shadow-lg transition-all"
              >
                ⚽ Jogar Rodada {estado.rodadaAtual + 1}
              </button>
            )}
            <button onClick={() => setModal('formacao')} className="bg-gray-700 hover:bg-gray-600 rounded-2xl py-5 text-center font-semibold transition-all">
              <div className="text-2xl mb-1">🗂</div>
              Mudar Formacao
              <div className="text-gray-400 text-sm mt-1">{t.formacao}</div>
            </button>
            <button onClick={() => setModal('melhorar')} className="bg-gray-700 hover:bg-gray-600 rounded-2xl py-5 text-center font-semibold transition-all">
              <div className="text-2xl mb-1">📈</div>
              Melhorar Elenco
              <div className="text-gray-400 text-sm mt-1">R${t.orcamento.toFixed(1)}M disponivel</div>
            </button>
            <div className="col-span-2 bg-gray-800 rounded-2xl p-4 grid grid-cols-4 gap-4 text-center">
              {[['V', t.vitorias, 'text-green-400'], ['E', t.empates, 'text-yellow-400'], ['D', t.derrotas, 'text-red-400'], ['SG', t.saldo, t.saldo >= 0 ? 'text-green-400' : 'text-red-400']].map(([label, val, color]) => (
                <div key={label}>
                  <div className={`text-2xl font-bold ${color}`}>{val}</div>
                  <div className="text-gray-400 text-xs">{label}</div>
                </div>
              ))}
            </div>
            <button onClick={onSairdoJogo} className="col-span-2 text-gray-500 hover:text-gray-300 text-sm underline text-center transition-all">
              Sair do jogo
            </button>
          </div>
        )}

        {/* TABELA */}
        {view === 'tabela' && (
          <div className="overflow-x-auto">
            <table className="w-full text-sm">
              <thead>
                <tr className="text-gray-400 border-b border-gray-700">
                  <th className="text-left py-2 w-8">#</th>
                  <th className="text-left py-2">Clube</th>
                  <th className="py-2">Pts</th>
                  <th className="py-2">V</th>
                  <th className="py-2">E</th>
                  <th className="py-2">D</th>
                  <th className="py-2">SG</th>
                </tr>
              </thead>
              <tbody>
                {tabela.map((tm) => {
                  const isMe = tm.id === (estado.meuTime?.id);
                  const zona = tm.pos <= 6 ? 'border-l-2 border-blue-500' : tm.pos >= 17 ? 'border-l-2 border-red-500' : tm.pos <= 12 ? 'border-l-2 border-green-500' : '';
                  return (
                    <tr key={tm.id} className={`border-b border-gray-800 ${isMe ? 'bg-blue-900/30' : 'hover:bg-gray-800'} ${zona}`}>
                      <td className="py-2 pl-2 text-gray-400">{tm.pos}</td>
                      <td className="py-2 font-semibold">{tm.nome}</td>
                      <td className="py-2 text-center font-bold">{tm.pontos}</td>
                      <td className="py-2 text-center text-green-400">{tm.vitorias}</td>
                      <td className="py-2 text-center text-yellow-400">{tm.empates}</td>
                      <td className="py-2 text-center text-red-400">{tm.derrotas}</td>
                      <td className={`py-2 text-center ${tm.saldo >= 0 ? 'text-green-400' : 'text-red-400'}`}>{tm.saldo > 0 ? '+' : ''}{tm.saldo}</td>
                    </tr>
                  );
                })}
              </tbody>
            </table>
            <p className="text-gray-600 text-xs mt-3">Azul=Libertadores · Verde=Sul-Americana · Vermelho=Rebaixamento</p>
          </div>
        )}

        {/* ELENCO */}
        {view === 'elenco' && (
          <div>
            <table className="w-full text-sm">
              <thead>
                <tr className="text-gray-400 border-b border-gray-700">
                  <th className="text-left py-2 w-8">#</th>
                  <th className="text-left py-2">Nome</th>
                  <th className="text-left py-2">Pos</th>
                  <th className="py-2 text-right">HAB</th>
                </tr>
              </thead>
              <tbody>
                {elenco.map((j) => (
                  <tr key={j.numero} className="border-b border-gray-800 hover:bg-gray-800">
                    <td className="py-2 text-gray-500">{j.numero}</td>
                    <td className="py-2 font-semibold">{j.nome}</td>
                    <td className="py-2 text-gray-400">{j.tipo}</td>
                    <td className="py-2 text-right text-blue-400 font-bold">{j.habilidade}</td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        )}
      </div>

      {/* Modal Formacao */}
      {modal === 'formacao' && (
        <div className="fixed inset-0 bg-black/70 flex items-center justify-center z-50">
          <div className="bg-gray-800 rounded-2xl p-6 w-80">
            <h3 className="font-bold text-lg mb-4">Escolha a Formacao</h3>
            <div className="grid grid-cols-2 gap-2 mb-4">
              {FORMACOES.map(f => (
                <button key={f} onClick={() => salvarFormacao(f)}
                  className={`py-3 rounded-xl text-sm font-semibold transition-all ${t.formacao === f ? 'bg-blue-600' : 'bg-gray-700 hover:bg-gray-600'}`}>
                  {f}
                </button>
              ))}
            </div>
            <button onClick={() => setModal(null)} className="w-full text-gray-400 hover:text-white text-sm underline">Cancelar</button>
          </div>
        </div>
      )}

      {/* Modal Melhorar */}
      {modal === 'melhorar' && (
        <div className="fixed inset-0 bg-black/70 flex items-center justify-center z-50">
          <div className="bg-gray-800 rounded-2xl p-6 w-80">
            <h3 className="font-bold text-lg mb-1">Melhorar Elenco</h3>
            <p className="text-gray-400 text-sm mb-4">R$15M por +1 de forca</p>
            <div className="flex items-center gap-4 justify-center mb-4">
              <button onClick={() => setQtdMelhorar(q => Math.max(1, q - 1))} className="bg-gray-700 px-4 py-2 rounded-xl text-lg">-</button>
              <span className="text-2xl font-bold w-12 text-center">{qtdMelhorar}</span>
              <button onClick={() => setQtdMelhorar(q => q + 1)} className="bg-gray-700 px-4 py-2 rounded-xl text-lg">+</button>
            </div>
            <p className="text-center text-sm text-gray-400 mb-4">Custo: R${custo.toFixed(1)}M · Disponivel: R${t.orcamento.toFixed(1)}M</p>
            <button onClick={confirmarMelhora} className="w-full bg-blue-600 hover:bg-blue-500 py-3 rounded-xl font-semibold mb-2 transition-all">Confirmar</button>
            <button onClick={() => setModal(null)} className="w-full text-gray-400 hover:text-white text-sm underline">Cancelar</button>
          </div>
        </div>
      )}
    </div>
  );
}