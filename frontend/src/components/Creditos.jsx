import { useEffect, useState } from "react";

export default function Creditos({ onVoltar }) {
  const [visivel, setVisivel] = useState(false);

  useEffect(() => {
    const t = setTimeout(() => setVisivel(true), 50);
    return () => clearTimeout(t);
  }, []);

  return (
    <div
      className="mfc-screen"
      style={{
        backgroundImage: "url('/estadio.jpg')",
        backgroundSize: "cover",
        backgroundPosition: "center",
        backgroundRepeat: "no-repeat",
        display: "flex",
        flexDirection: "column",
        alignItems: "center",
        justifyContent: "center",
        position: "relative",
        overflow: "hidden",
      }}
    >
      <div
        style={{
          position: "absolute",
          inset: 0,
          pointerEvents: "none",
          background: "linear-gradient(180deg, rgba(6,13,6,0.78) 0%, rgba(6,13,6,0.55) 40%, rgba(6,13,6,0.85) 100%)",
        }}
      ></div>

      <div
        style={{
          position: "absolute",
          inset: 0,
          pointerEvents: "none",
          backgroundImage: "repeating-linear-gradient(0deg,rgba(0,0,0,0.18) 0px,rgba(0,0,0,0.18) 1px,transparent 1px,transparent 3px)",
        }}
      ></div>

      <div
        style={{
          position: "relative",
          zIndex: 10,
          display: "flex",
          flexDirection: "column",
          alignItems: "center",
          textAlign: "center",
          gap: "24px",
          padding: "0 24px",
          opacity: visivel ? 1 : 0,
          transform: visivel ? "translateY(0)" : "translateY(16px)",
          transition: "opacity 0.7s ease, transform 0.7s ease",
        }}
      >
        <div className="mfc-menu-eyebrow">BRASILEIRAO SERIE A 2026</div>
        <div className="mfc-menu-logo" style={{ fontSize: "2.8rem" }}>CRÉDITOS</div>

        <div style={{ width: "60px", height: "1px", background: "rgba(255,255,255,0.3)", margin: "4px auto" }}></div>

        <div>
          <p style={{ color: "var(--c-gold)", fontSize: "0.7rem", textTransform: "uppercase", letterSpacing: "0.15em", marginBottom: "4px" }}>
            Disciplina
          </p>
          <p style={{ color: "var(--c-text)", fontSize: "0.95rem" }}>
            Estruturas de Dados Orientado a Objetos
          </p>
        </div>

        <div>
          <p style={{ color: "var(--c-gold)", fontSize: "0.7rem", textTransform: "uppercase", letterSpacing: "0.15em", marginBottom: "4px" }}>
            Instituição
          </p>
          <p style={{ color: "var(--c-text)", fontSize: "0.95rem" }}>CIn / UFPE</p>
        </div>

        <div>
          <p style={{ color: "var(--c-gold)", fontSize: "0.7rem", textTransform: "uppercase", letterSpacing: "0.15em", marginBottom: "12px" }}>
            Desenvolvido por
          </p>
          <div style={{ display: "flex", flexDirection: "column", gap: "6px" }}>
            <p style={{ color: "var(--c-text)", fontSize: "0.95rem" }}>João Luís de Siqueira</p>
            <p style={{ color: "var(--c-text)", fontSize: "0.95rem" }}>João Pedro Medeiros</p>
            <p style={{ color: "var(--c-text)", fontSize: "0.95rem" }}>Vitor Nunes</p>
            <p style={{ color: "var(--c-text)", fontSize: "0.95rem" }}>Davi Mello</p>
          </div>
        </div>

        <a
          href="https://github.com/joaopedrommm/manager-fc"
          target="_blank"
          rel="noreferrer"
          className="mfc-credits-link"
        >
          github.com/joaopedrommm/manager-fc
        </a>

        <button
          className="mfc-btn mfc-btn-lg"
          onClick={onVoltar}
          style={{ marginTop: "8px", width: "260px" }}
        >
          ← VOLTAR AO MENU
        </button>
      </div>

      <div className="mfc-menu-version">v0.2.0 — CIn/UFPE</div>
    </div>
  );
}
