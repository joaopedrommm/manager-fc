import { useState, useEffect } from 'react';

const LOGOS = {
  1: 'flamengo', 2: 'atletico-mg', 3: 'palmeiras', 4: 'fluminense',
  5: 'athletico-pr', 6: 'internacional', 7: 'sao-paulo', 8: 'gremio',
  9: 'botafogo', 10: 'vasco', 11: 'corinthians', 12: 'cruzeiro',
  13: 'bahia', 14: 'santos', 15: 'bragantino', 16: 'chapecoense',
  17: 'coritiba', 18: 'vitoria', 19: 'mirassol', 20: 'remo'
};

function logoSrc(time) {
  const arq = LOGOS[time.id] || time.sigla.toLowerCase();
  return arq === 'gremio' ? '/times/gremio.svg' : `/times/${arq}.png`;
}

export default function SelecaoClube({ onVoltar, onConfirmar }) {
  const [times, setTimes] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    fetch('/api/times')
      .then(r => r.json())
      .then(data => { setTimes(data); setLoading(false); });
  }, []);

  return (
    <div
      className="min-h-screen flex flex-col items-center justify-center relative overflow-hidden"
      style={{ backgroundImage: "url('/estadio.jpg')", backgroundSize: 'cover', backgroundPosition: 'center' }}
    >
      <div className="absolute inset-0 bg-black opacity-70" />
      <div className="relative z-10 w-full max-w-4xl px-6 py-10">
        <h2 className="text-white text-4xl font-extrabold text-center mb-2">
          Escolha seu <span className="text-blue-400">Clube</span>
        </h2>
        <p className="text-gray-400 text-sm text-center mb-8 tracking-widest uppercase">
          Brasileirao Serie A 2026
        </p>

        {loading ? (
          <p className="text-white text-center py-12">Carregando times...</p>
        ) : (
          <div className="grid grid-cols-4 sm:grid-cols-5 gap-4 mb-8">
            {times.map((time) => (
              <button
                key={time.id}
                onClick={() => onConfirmar(time)}
                className="flex flex-col items-center gap-2 bg-white/10 hover:bg-blue-600/40 border border-white/20 hover:border-blue-500 py-4 px-2 rounded-2xl transition-all duration-200 backdrop-blur-sm"
              >
                <img src={logoSrc(time)} alt={time.nome} className="w-12 h-12 object-contain" />
                <span className="text-white text-xs font-semibold text-center leading-tight">{time.nome}</span>
                <span className="text-blue-300 text-xs">{time.forca} ovr</span>
              </button>
            ))}
          </div>
        )}

        <div className="flex justify-center">
          <button onClick={onVoltar} className="text-gray-400 hover:text-white text-sm transition-all underline underline-offset-4">
            ← Voltar ao menu
          </button>
        </div>
      </div>
    </div>
  );
}