const times = [
  { nome: "Flamengo", arquivo: "flamengo" },
  { nome: "Palmeiras", arquivo: "palmeiras" },
  { nome: "Cruzeiro", arquivo: "cruzeiro" },
  { nome: "Mirassol", arquivo: "mirassol" },
  { nome: "Fluminense", arquivo: "fluminense" },
  { nome: "Bahia", arquivo: "bahia" },
  { nome: "Botafogo", arquivo: "botafogo" },
  { nome: "São Paulo", arquivo: "sao-paulo" },
  { nome: "Red Bull Bragantino", arquivo: "bragantino" },
  { nome: "Corinthians", arquivo: "corinthians" },
  { nome: "Grêmio", arquivo: "gremio.svg" },
  { nome: "Vasco", arquivo: "vasco" },
  { nome: "Atlético-MG", arquivo: "atletico-mg" },
  { nome: "Santos", arquivo: "santos" },
  { nome: "Vitória", arquivo: "vitoria" },
  { nome: "Internacional", arquivo: "internacional" },
  { nome: "Coritiba", arquivo: "coritiba" },
  { nome: "Athletico-PR", arquivo: "athletico-pr" },
  { nome: "Chapecoense", arquivo: "chapecoense" },
  { nome: "Remo", arquivo: "remo" },
];

export default function SelecaoClube({ onVoltar, onConfirmar}) {
  return (
    <div
      className="min-h-screen flex flex-col items-center justify-center relative overflow-hidden"
      style={{ backgroundImage: "url('/estadio.jpg')", backgroundSize: "cover", backgroundPosition: "center" }}
    >
      <div className="absolute inset-0 bg-black opacity-70" />

      <div className="relative z-10 w-full max-w-4xl px-6 py-10">
        <h2 className="text-white text-4xl font-extrabold text-center mb-2">
          Escolha seu <span className="text-blue-400">Clube</span>
        </h2>
        <p className="text-gray-400 text-sm text-center mb-8 tracking-widest uppercase">
          Brasileirão Série A 2026
        </p>

        <div className="grid grid-cols-4 sm:grid-cols-5 gap-4 mb-8">
          {times.map((time) => (
            <button
              key={time.nome}
              onClick={() => onConfirmar(time.nome)}
              className="flex flex-col items-center gap-2 bg-white/10 hover:bg-blue-600/40 border border-white/20 hover:border-blue-500 py-4 px-2 rounded-2xl transition-all duration-200 backdrop-blur-sm"
            >
              <img
                src={`/times/${time.arquivo}${time.arquivo.endsWith('.svg') ? '' : '.png'}`}
                alt={time.nome}
                className="w-12 h-12 object-contain"
              />
              <span className="text-white text-xs font-semibold text-center leading-tight">
                {time.nome}
              </span>
            </button>
          ))}
        </div>

        <div className="flex justify-center">
          <button
            onClick={onVoltar}
            className="text-gray-400 hover:text-white text-sm transition-all duration-200 underline underline-offset-4"
          >
            ← Voltar ao menu
          </button>
        </div>
      </div>
    </div>
  );
}