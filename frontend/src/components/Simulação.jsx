import { useState, useEffect, useRef } from 'react';

const TIPO_STYLE = {
  GOL:      { icon: '⚽', color: 'text-green-400',  bg: 'bg-green-900/40' },
  AMARELO:  { icon: '🟨', color: 'text-yellow-400', bg: 'bg-yellow-900/30' },
  VERMELHO: { icon: '🟥', color: 'text-red-400',    bg: 'bg-red-900/30' },
  INTERVALO:{ icon: '⏸',  color: 'text-blue-400',   bg: 'bg-blue-900/30' },
};

export default function Simulacao({ onAvancar }) {
  const [dados, setDados] = useState(null);
  const [loading, setLoading] = useState(true);
  const [eventosVisiveis, setEventosVisiveis] = useState([]);
  const [placarCasa, setPlacarCasa] = useState(0);
  const [placarVisit, setPlacarVisit] = useState(0);
  const [finalizado, setFinalizado] = useState(false);
  const logRef = useRef(null);
  const animandoRef = useRef(false);
  const fetchedRef = useRef(false);

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
    if (eventos.length === 0) { setFinalizado(true); return; }

    let golsCasa = 0, golsVisit = 0;
    let idx = 0;

    const tick = () => {
      if (idx >= eventos.length) {
        setPlacarCasa(dados.minhaPartida.golsCasa);
        setPlacarVisit(dados.minhaPartida.golsVisit);
        setTimeout(() => setFinalizado(true), 600);
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
      setTimeout(() => {
        if (logRef.current) logRef.current.scrollTop = logRef.current.scrollHeight;
      }, 50);
      setTimeout(tick, 650);
    };

    setTimeout(tick, 400);
  }, [dados, loading]);

  if (loading) return (
    <div className="min-h-screen bg-gray-900 flex items-center justify-center text-white">
      <div className="text-center">
        <div className="text-5xl mb-4 animate-pulse">⚽</div>
        <p className="text-xl font-bold">Simulando partida...</p>
      </div>
    </div>
  );

  if (!dados.minhaPartida) return (
    <div className="min-h-screen bg-gray-900 flex items-center justify-center text-white">
      <div className="text-center">
        <p className="text-lg mb-6 text-gray-400">Voce nao tinha jogo nessa rodada.</p>
        <button onClick={() => onAvancar(dados)} className="bg-blue-600 hover:bg-blue-500 px-8 py-3 rounded-2xl font-bold">Continuar</button>
      </div>
    </div>
  );

  const mp = dados.minhaPartida;

  return (
    <div className="min-h-screen bg-gray-900 text-white flex flex-col">
      {/* Placar */}
      <div className="bg-gray-800 border-b border-gray-700 px-6 py-6 text-center">
        <p className="text-gray-400 text-xs tracking-widest uppercase mb-3">Rodada {dados.rodada}</p>
        <div className="flex items-center justify-center gap-6">
          <div className="text-right flex-1">
            <p className="font-extrabold text-lg leading-tight">{mp.timeCasa}</p>
            <p className="text-gray-500 text-sm">{mp.siglaCasa}</p>
          </div>
          <div className="flex items-center gap-3">
            <span className="text-5xl font-black text-white">{placarCasa}</span>
            <span className="text-gray-500 text-2xl">x</span>
            <span className="text-5xl font-black text-white">{placarVisit}</span>
          </div>
          <div className="text-left flex-1">
            <p className="font-extrabold text-lg leading-tight">{mp.timeVisit}</p>
            <p className="text-gray-500 text-sm">{mp.siglaVisit}</p>
          </div>
        </div>
      </div>

      {/* Log de eventos */}
      <div ref={logRef} className="flex-1 overflow-y-auto px-4 py-4 max-h-96 space-y-2">
        {eventosVisiveis.map((e, i) => {
          const style = TIPO_STYLE[e.tipo] || TIPO_STYLE.AMARELO;
          if (e.tipo === 'INTERVALO') return (
            <div key={i} className="text-center py-2">
              <span className="text-blue-400 text-xs font-bold tracking-widest uppercase">— Intervalo — {e.descricao}</span>
            </div>
          );
          return (
            <div key={i} className={`flex items-start gap-3 rounded-xl px-4 py-3 ${style.bg}`}>
              <span className="text-xl">{style.icon}</span>
              <div className="flex-1">
                <span className={`text-xs font-bold ${style.color} mr-2`}>{e.minuto}'</span>
                <span className="text-sm text-gray-300">{e.descricao}</span>
              </div>
            </div>
          );
        })}
        {!finalizado && (
          <div className="text-center py-4">
            <span className="text-gray-500 text-sm animate-pulse">em andamento...</span>
          </div>
        )}
      </div>

      {/* Outros resultados + botao */}
      {finalizado && (
        <div className="border-t border-gray-700 px-4 py-4">
          <p className="text-gray-400 text-xs uppercase tracking-widest mb-2">Outros resultados</p>
          <div className="grid grid-cols-2 gap-1 text-xs text-gray-400 mb-4">
            {dados.outrasPartidas.map((p, i) => (
              <div key={i} className="bg-gray-800 rounded-lg px-3 py-2">
                {p.timeCasa} <span className="font-bold text-white">{p.golsCasa}-{p.golsVisit}</span> {p.timeVisit}
              </div>
            ))}
          </div>
          <button
            onClick={() => onAvancar(dados)}
            className="w-full bg-blue-600 hover:bg-blue-500 py-4 rounded-2xl font-bold text-lg transition-all"
          >
            Ver resumo →
          </button>
        </div>
      )}
    </div>
  );
}