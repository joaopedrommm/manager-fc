import { useState } from 'react';
import MenuPrincipal from './components/MenuPrincipal';
import SelecaoClube from './components/SelecaoClube';
import Dashboard from './components/Dashboard';
import Simulacao from './components/Simulação';
import PosJogo from './components/Pos-jogo';
import FimTemporada from './components/FimTemporada';

export default function App() {
  const [tela, setTela] = useState('menu');
  const [clubeSelecionado, setClubeSelecionado] = useState(null);
  const [resultadoRodada, setResultadoRodada] = useState(null);

  const handleConfirmarClube = async (time) => {
    await fetch('/api/iniciar', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ id: time.id })
    });
    setClubeSelecionado(time);
    setTela('dashboard');
  };

  return (
    <>
      {tela === 'menu' && (
        <MenuPrincipal onNovoJogo={() => setTela('selecao')} />
      )}
      {tela === 'selecao' && (
        <SelecaoClube
          onVoltar={() => setTela('menu')}
          onConfirmar={handleConfirmarClube}
        />
      )}
      {tela === 'dashboard' && (
        <Dashboard
          clube={clubeSelecionado}
          onProximoJogo={() => setTela('simulacao')}
          onFimTemporada={() => setTela('fim-temporada')}
          onSairdoJogo={() => { setClubeSelecionado(null); setTela('menu'); }}
        />
      )}
      {tela === 'simulacao' && (
        <Simulacao
          onAvancar={(resultado) => {
            setResultadoRodada(resultado);
            setTela('pos-jogo');
          }}
        />
      )}
      {tela === 'pos-jogo' && (
        <PosJogo
          resultado={resultadoRodada}
          onAvancar={() => setTela('dashboard')}
        />
      )}
      {tela === 'fim-temporada' && (
        <FimTemporada
          meuTimeId={clubeSelecionado?.id}
          onVoltar={() => { setClubeSelecionado(null); setTela('menu'); }}
        />
      )}
    </>
  );
}