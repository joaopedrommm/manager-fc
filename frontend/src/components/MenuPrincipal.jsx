export default function MenuPrincipal() {
  return (
    <div
      className="min-h-screen flex flex-col items-center justify-center relative overflow-hidden"
      style={{ backgroundImage: "url('/estadio.jpg')", backgroundSize: "cover", backgroundPosition: "center" }}
    >
      {/* Overlay escuro */}
      <div className="absolute inset-0 bg-black opacity-60" />

      {/* Conteúdo */}
      <div className="relative z-10 flex flex-col items-center">

        {/* Ícone */}
        <div className="text-6xl mb-6">⚽</div>

        {/* Título */}
        <h1 className="text-white text-6xl font-extrabold tracking-tight mb-2">
          Manager <span className="text-blue-400">FC</span>
        </h1>
        <p className="text-gray-300 text-sm mb-12 tracking-widest uppercase">
          Gerencie seu clube ao topo
        </p>

        {/* Botões */}
        <div className="flex flex-col gap-3 w-72">
          <button className="bg-blue-600 hover:bg-blue-500 text-white text-lg font-semibold py-4 rounded-2xl transition-all duration-200 shadow-lg shadow-blue-900/60">
            Novo Jogo
          </button>
          <button className="bg-transparent border border-white/30 hover:border-white/60 text-white text-lg font-semibold py-4 rounded-2xl transition-all duration-200 backdrop-blur-sm">
            Créditos
          </button>
        </div>
      </div>

      {/* Versão */}
      <p className="absolute bottom-6 text-white/30 text-xs tracking-widest uppercase z-10">
        v0.1.0 — CIn/UFPE
      </p>
    </div>
  );
}