import { useEffect, useState } from "react";

export default function Creditos({ onVoltar }) {
  const [visivel, setVisivel] = useState(false);

  useEffect(() => {
    const t = setTimeout(() => setVisivel(true), 50);
    return () => clearTimeout(t);
  }, []);

  return (
    <div
      className="min-h-screen flex flex-col items-center justify-center relative overflow-hidden"
      style={{ backgroundImage: "url('/estadio.jpg')", backgroundSize: "cover", backgroundPosition: "center" }}
    >
      <div className="absolute inset-0 bg-black opacity-60" />

      <div
        className={`relative z-10 flex flex-col items-center text-center gap-8 px-6 transition-all duration-700 ${
          visivel ? "opacity-100 translate-y-0" : "opacity-0 translate-y-4"
        }`}
      >
        <h1 className="text-white text-5xl font-extrabold tracking-tight">
          Créditos
        </h1>

        <div className="w-16 h-px bg-white/40" />

        <div>
          <p className="text-gray-400 text-xs uppercase tracking-widest mb-1">Disciplina</p>
          <p className="text-white text-base">Estruturas de Dados Orientado a Objetos</p>
        </div>

        <div>
          <p className="text-gray-400 text-xs uppercase tracking-widest mb-1">Instituição</p>
          <p className="text-white text-base">CIn / UFPE</p>
        </div>

        <div>
          <p className="text-gray-400 text-xs uppercase tracking-widest mb-3">Desenvolvido por</p>
          <div className="flex flex-col gap-1">
            <p className="text-white text-base">João Luís de Siqueira</p>
            <p className="text-white text-base">João Pedro Medeiros</p>
            <p className="text-white text-base">Vitor Nunes</p>
            <p className="text-white text-base">Davi Mello</p>
          </div>
        </div>

        <a
          href="https://github.com/joaopedrommm/manager-fc"
          target="_blank"
          rel="noreferrer"
          className="text-gray-400 text-sm hover:text-white transition-colors duration-200"
        >
          github.com/joaopedrommm/manager-fc
        </a>

        <button
          onClick={onVoltar}
          className="mt-4 px-8 py-3 border border-white/30 hover:border-white/60 text-white text-base font-semibold rounded-2xl transition-all duration-200 backdrop-blur-sm"
        >
          ← Voltar ao Menu
        </button>
      </div>

      <p className="absolute bottom-6 text-white/30 text-xs tracking-widest uppercase z-10">
        v0.1.0 — CIn/UFPE
      </p>
    </div>
  );
}