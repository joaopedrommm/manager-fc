import React from 'react';
import './App.css'; // Use para estilizar a página de divulgação

function PaginaDivulgacao() {
  return (
    <div className="landing-page">
      {/* 1. TÍTULO */}
      <header className="hero-section">
        <h1>Manager FC</h1>
        <p className="subtitle">O Simulador de Gestão de Futebol e Simulação de Partidas</p>
      </header>

      {/* 2. DESCRIÇÃO */}
      <section className="about-section">
        <h2>Sobre o Projeto</h2>
        <p> O Manager FC é um simulador de gestão e simulação de partidas de futebol inspirado em clássicos como Brasfoot e Football Manager. O objetivo principal do sistema é permitir a organização de um campeonato no formato de pontos corridos, processando estatísticas das equipes e simulando eventos de jogo em tempo real. Desenvolvido como um sistema de informação robusto, o projeto utiliza um motor matemático de simulação implementado puramente em C++ no Backend e uma interface interativa construída em React no Frontend.  </p>
      </section>

      {/* 3. FUNCIONALIDADES */}
      <section className="video-section">
        <video width="100%" controls autoPlay muted loop>
        <source src="./public/video demonstra.mp4" type="video/mp4" />
        O seu navegador não suporta a tag de vídeo.
        </video>
      </section>

      {/* 4. LINKS E RECURSOS */}
      <section className="resources-section">
        <h2>Recursos e Downloads</h2>
        <div className="buttons-container">
          <a href="https://github.com/joaopedrommm/manager-fc" target="_blank" rel="noreferrer" className="btn-link repo">
            Ver Código no GitHub
          </a>
          <a href="/relatorio.pdf" target="_blank" className="btn-link doc">
            Ler Relatório Completo (PDF)
          </a>
          <a href="https://youtube.com/..." target="_blank" rel="noreferrer" className="btn-link video">
            Assistir Demonstração no YouTube
          </a>
        </div>
      </section>
    </div>
  );
}

export default PaginaDivulgacao;