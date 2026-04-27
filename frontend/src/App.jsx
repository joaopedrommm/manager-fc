import { useState } from 'react';
import MenuPrincipal from './components/MenuPrincipal';
import SelecaoClube from './components/SelecaoClube';

export default function App() {
  const [tela, setTela] = useState('menu');
  const [clubeSelecionado, setClubeSelecionado] = useState(null);

  return (
    <>
      {tela === 'menu' && (
        <MenuPrincipal onNovoJogo={() => setTela('selecao')} />
      )}
      {tela === 'selecao' && (
        <SelecaoClube
          onVoltar={() => setTela('menu')}
          onConfirmar={(clube) => {
            setClubeSelecionado(clube);
            setTela('dashboard');
          }}
        />
      )}
      {tela === 'simulacao' && (
        <Simulacao
          clube={clubeSelecionado}
          onAvancar={() => setTela('pos-jogo')}
        />
      )}
      {tela === 'pos-jogo' && (
        <PosJogo
          clube={clubeSelecionado}
          onAvancar={() => setTela('dashboard')}
        />
      )}
    </>
  );
}