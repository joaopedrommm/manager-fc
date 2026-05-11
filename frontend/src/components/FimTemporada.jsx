import { useState, useEffect } from 'react';

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

function zona(pos) {
  if (pos === 1)        return { label: 'CAMPEAO',        bg: 'bg-yellow-500/20', border: 'border-l-4 border-yellow-400', text: 'text-yellow-400' };
  if (pos <= 6)         return { label: 'Libertadores',   bg: 'bg-blue-500/10',   border: 'border-l-4 border-blue-500',   text: 'text-blue-400' };
  if (pos <= 12)        return { label: 'Sul-Americana',  bg: 'bg-green-500/10',  border: 'border-l-4 border-green-500',  text: 'text-green-400' };
  if (pos >= 17)        return { label: 'Rebaixado',      bg: 'bg-red-500/10',    border: 'border-l-4 border-red-500',    text: 'text-red-400' };
  return { label: '', bg: '', border: 'border-l-4 border-transparent', text: '' };
}

export default function FimTemporada({ meuTimeId, onVoltar }) {
  const [tabela, setTabela] = useState([]);

  useEffect(() => {
    fetch('/api/tabela').then(r => r.json()).then(setTabela);
  }, []);

  const campeao = tabela[0];

  return (
    <div className="min-h-screen bg-gray-900 text-white">
      {/* Header */}
      <div className="bg-gradient-to-b from-yellow-600/30 to-gray-900 px-6 py-10 text-center">
        <p className="text-yellow-400 text-xs tracking-widest uppercase mb-2">Brasileirao Serie A 2026</p>
        <h1 className="text-4xl font-extrabold mb-1">Temporada Encerrada</h1>

        {campeao && (
          <div className="mt-6 flex flex-col items-center gap-3">
            <img src={logoSrc(campeao.id)} alt={campeao.nome} className="w-20 h-20 object-contain drop-shadow-lg" />
            <div>
              <p className="text-yellow-400 text-xs tracking-widest uppercase">Campeao Brasileiro</p>
              <p className="text-3xl font-extrabold">{campeao.nome}</p>
              <p className="text-gray-400 text-sm mt-1">{campeao.pontos} pontos · {campeao.vitorias}V {campeao.empates}E {campeao.derrotas}D</p>
            </div>
          </div>
        )}
      </div>

      {/* Tabela */}
      <div className="max-w-2xl mx-auto px-4 pb-8">
        <div className="space-y-1">
          {tabela.map((tm) => {
            const z = zona(tm.pos);
            const isMe = tm.id === meuTimeId;
            return (
              <div
                key={tm.id}
                className={`flex items-center gap-3 px-3 py-3 rounded-xl ${z.bg} ${z.border} ${isMe ? 'ring-1 ring-white/30' : ''}`}
              >
                <span className="text-gray-500 text-sm w-5 text-right">{tm.pos}</span>
                <img src={logoSrc(tm.id)} alt={tm.nome} className="w-7 h-7 object-contain" />
                <span className={`flex-1 font-semibold text-sm ${isMe ? 'text-white' : 'text-gray-200'}`}>
                  {tm.nome} {isMe && <span className="text-blue-400 text-xs ml-1">(você)</span>}
                </span>
                {z.label && (
                  <span className={`text-xs font-bold ${z.text} hidden sm:block`}>{z.label}</span>
                )}
                <span className="font-bold text-sm w-8 text-right">{tm.pontos}</span>
                <span className="text-gray-400 text-xs w-12 text-right">{tm.vitorias}V {tm.derrotas}D</span>
              </div>
            );
          })}
        </div>

        {/* Legenda */}
        <div className="flex gap-4 mt-4 text-xs text-gray-500 justify-center flex-wrap">
          <span className="flex items-center gap-1"><span className="w-3 h-3 bg-yellow-400 rounded-sm inline-block"/>Campeao</span>
          <span className="flex items-center gap-1"><span className="w-3 h-3 bg-blue-500 rounded-sm inline-block"/>Libertadores</span>
          <span className="flex items-center gap-1"><span className="w-3 h-3 bg-green-500 rounded-sm inline-block"/>Sul-Americana</span>
          <span className="flex items-center gap-1"><span className="w-3 h-3 bg-red-500 rounded-sm inline-block"/>Rebaixamento</span>
        </div>

        <button
          onClick={onVoltar}
          className="w-full mt-6 bg-gray-700 hover:bg-gray-600 py-4 rounded-2xl font-bold transition-all"
        >
          Voltar ao Menu
        </button>
      </div>
    </div>
  );
}