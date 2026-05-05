export default function PosJogo({ resultado, onAvancar }) {
  if (!resultado) return null;

  const mp = resultado.minhaPartida;
  const rodada = resultado.rodada;

  const gols = mp ? mp.eventos.filter(e => e.tipo === 'GOL') : [];
  const cartoes = mp ? mp.eventos.filter(e => e.tipo === 'AMARELO' || e.tipo === 'VERMELHO') : [];

  const resultado_texto = !mp
    ? 'Sem jogo nessa rodada'
    : mp.golsCasa > mp.golsVisit
    ? `${mp.siglaCasa} venceu!`
    : mp.golsCasa < mp.golsVisit
    ? `${mp.siglaVisit} venceu!`
    : 'Empate';

  return (
    <div className="min-h-screen bg-gray-900 text-white">
      {/* Header resultado */}
      <div className="bg-gray-800 border-b border-gray-700 px-6 py-8 text-center">
        <p className="text-gray-400 text-xs tracking-widest uppercase mb-1">Rodada {rodada} · Resultado Final</p>
        {mp && (
          <>
            <div className="flex items-center justify-center gap-6 mt-3">
              <div className="text-right flex-1">
                <p className="font-extrabold text-xl">{mp.timeCasa}</p>
              </div>
              <div className="flex items-center gap-3">
                <span className="text-6xl font-black">{mp.golsCasa}</span>
                <span className="text-gray-500 text-2xl">x</span>
                <span className="text-6xl font-black">{mp.golsVisit}</span>
              </div>
              <div className="text-left flex-1">
                <p className="font-extrabold text-xl">{mp.timeVisit}</p>
              </div>
            </div>
            <p className="mt-3 text-blue-400 font-semibold">{resultado_texto}</p>
          </>
        )}
      </div>

      <div className="max-w-2xl mx-auto px-4 py-6 space-y-4">
        {/* Gols */}
        {gols.length > 0 && (
          <div className="bg-gray-800 rounded-2xl p-4">
            <p className="text-gray-400 text-xs uppercase tracking-widest mb-3">Gols</p>
            {gols.map((e, i) => (
              <div key={i} className="flex items-center gap-2 py-1 text-sm">
                <span>⚽</span>
                <span className="text-green-400 font-bold w-8">{e.minuto}'</span>
                <span>{e.descricao}</span>
              </div>
            ))}
          </div>
        )}

        {/* Cartoes */}
        {cartoes.length > 0 && (
          <div className="bg-gray-800 rounded-2xl p-4">
            <p className="text-gray-400 text-xs uppercase tracking-widest mb-3">Cartoes</p>
            {cartoes.map((e, i) => (
              <div key={i} className="flex items-center gap-2 py-1 text-sm">
                <span>{e.tipo === 'VERMELHO' ? '🟥' : '🟨'}</span>
                <span className={`font-bold w-8 ${e.tipo === 'VERMELHO' ? 'text-red-400' : 'text-yellow-400'}`}>{e.minuto}'</span>
                <span className="text-gray-300">{e.descricao}</span>
              </div>
            ))}
          </div>
        )}

        {/* Outros resultados */}
        <div className="bg-gray-800 rounded-2xl p-4">
          <p className="text-gray-400 text-xs uppercase tracking-widest mb-3">Outros resultados</p>
          <div className="space-y-1">
            {resultado.outrasPartidas.map((p, i) => (
              <div key={i} className="flex justify-between text-sm py-1 border-b border-gray-700 last:border-0">
                <span className="text-gray-300">{p.timeCasa}</span>
                <span className="font-bold px-3">{p.golsCasa} - {p.golsVisit}</span>
                <span className="text-gray-300">{p.timeVisit}</span>
              </div>
            ))}
          </div>
        </div>

        <button
          onClick={onAvancar}
          className="w-full bg-blue-600 hover:bg-blue-500 py-4 rounded-2xl font-bold text-lg transition-all"
        >
          Proxima Rodada →
        </button>
      </div>
    </div>
  );
}