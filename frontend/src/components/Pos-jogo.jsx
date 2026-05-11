export default function PosJogo({ resultado, onAvancar }) {
  if (!resultado) return null;

  const mp = resultado.minhaPartida;
  const rodada = resultado.rodada;

  const gols = mp ? mp.eventos.filter(e => e.tipo === 'GOL') : [];
  const cartoes = mp ? mp.eventos.filter(e => e.tipo === 'AMARELO' || e.tipo === 'VERMELHO') : [];

  const vitoria = mp && mp.golsCasa > mp.golsVisit;
  const derrota = mp && mp.golsCasa < mp.golsVisit;
  const empate  = mp && mp.golsCasa === mp.golsVisit;

  const resultadoTexto = !mp ? null
    : vitoria ? 'Vitória!' : derrota ? 'Derrota' : 'Empate';

  const gradiente = vitoria
    ? 'linear-gradient(160deg, #0f2a1a 0%, #111827 60%)'
    : derrota
    ? 'linear-gradient(160deg, #2a0f0f 0%, #111827 60%)'
    : 'linear-gradient(160deg, #1a1a2a 0%, #111827 60%)';

  const accentColor = vitoria ? '#4ade80' : derrota ? '#f87171' : '#facc15';

  return (
    <div className="min-h-screen text-white" style={{ background: gradiente }}>

      {/* Placar */}
      <div className="px-6 pt-10 pb-8 text-center"
        style={{ borderBottom: '1px solid rgba(255,255,255,0.06)' }}>
        <p className="text-xs tracking-widest uppercase mb-6"
          style={{ color: 'rgba(255,255,255,0.35)' }}>
          Rodada {rodada} · Resultado Final
        </p>

        {mp ? (
          <>
            <div className="flex items-center justify-center gap-4 mb-6">
              <div className="flex-1 text-right">
                <p className="font-extrabold text-lg leading-tight">{mp.timeCasa}</p>
              </div>

              <div className="flex items-center gap-3 px-4 py-3 rounded-2xl"
                style={{ background: 'rgba(255,255,255,0.06)', minWidth: 140 }}>
                <span className="text-6xl font-black w-12 text-right">{mp.golsCasa}</span>
                <span className="text-gray-600 text-2xl">×</span>
                <span className="text-6xl font-black w-12 text-left">{mp.golsVisit}</span>
              </div>

              <div className="flex-1 text-left">
                <p className="font-extrabold text-lg leading-tight">{mp.timeVisit}</p>
              </div>
            </div>

            <span className="text-lg font-extrabold px-5 py-1.5 rounded-full"
              style={{ background: `${accentColor}22`, color: accentColor }}>
              {resultadoTexto}
            </span>
          </>
        ) : (
          <p className="text-gray-500 text-sm">Sem jogo nessa rodada</p>
        )}
      </div>

      <div className="max-w-2xl mx-auto px-4 py-6 space-y-3">

        {/* Gols */}
        {gols.length > 0 && (
          <div className="rounded-2xl p-4"
            style={{ background: 'rgba(255,255,255,0.04)', border: '1px solid rgba(255,255,255,0.06)' }}>
            <p className="text-xs uppercase tracking-widest mb-3"
              style={{ color: 'rgba(255,255,255,0.3)' }}>Gols</p>
            <div className="space-y-2">
              {gols.map((e, i) => (
                <div key={i} className="flex items-center gap-3 text-sm">
                  <span className="text-green-400 font-bold w-8 text-right shrink-0">{e.minuto}'</span>
                  <span>⚽</span>
                  <span className="text-gray-300">{e.descricao}</span>
                </div>
              ))}
            </div>
          </div>
        )}

        {/* Cartões */}
        {cartoes.length > 0 && (
          <div className="rounded-2xl p-4"
            style={{ background: 'rgba(255,255,255,0.04)', border: '1px solid rgba(255,255,255,0.06)' }}>
            <p className="text-xs uppercase tracking-widest mb-3"
              style={{ color: 'rgba(255,255,255,0.3)' }}>Cartões</p>
            <div className="space-y-2">
              {cartoes.map((e, i) => (
                <div key={i} className="flex items-center gap-3 text-sm">
                  <span className={`font-bold w-8 text-right shrink-0 ${e.tipo === 'VERMELHO' ? 'text-red-400' : 'text-yellow-400'}`}>
                    {e.minuto}'
                  </span>
                  <span>{e.tipo === 'VERMELHO' ? '🟥' : '🟨'}</span>
                  <span className="text-gray-300">{e.descricao}</span>
                </div>
              ))}
            </div>
          </div>
        )}

        {/* Outros resultados */}
        <div className="rounded-2xl p-4"
          style={{ background: 'rgba(255,255,255,0.04)', border: '1px solid rgba(255,255,255,0.06)' }}>
          <p className="text-xs uppercase tracking-widest mb-3"
            style={{ color: 'rgba(255,255,255,0.3)' }}>Outros resultados</p>
          <div className="space-y-1">
            {resultado.outrasPartidas.map((p, i) => (
              <div key={i} className="flex items-center justify-between text-sm py-1.5"
                style={{ borderBottom: '1px solid rgba(255,255,255,0.05)' }}>
                <span className="text-gray-400 flex-1 text-right pr-3">{p.timeCasa}</span>
                <span className="font-black text-white px-3 tabular-nums">{p.golsCasa} – {p.golsVisit}</span>
                <span className="text-gray-400 flex-1 pl-3">{p.timeVisit}</span>
              </div>
            ))}
          </div>
        </div>

        <button onClick={onAvancar}
          className="w-full py-4 rounded-2xl font-bold text-lg transition-all hover:scale-[1.01]"
          style={{ background: 'linear-gradient(135deg, #1d4ed8, #3b82f6)' }}>
          Próxima Rodada →
        </button>
      </div>
    </div>
  );
}