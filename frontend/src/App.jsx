import { useState } from 'react';
import MenuPrincipal from './components/MenuPrincipal';
import SelecaoClube from './components/SelecaoClube';
import Creditos from "./components/Creditos";

export default function App() {
  const [tela, setTela] = useState('menu');
  const [clubeSelecionado, setClubeSelecionado] = useState(null);

  return (
    <>
      {tela === 'menu' && (
        <MenuPrincipal
          onNovoJogo={() => setTela('selecao')}
          onCreditos={() => setTela('creditos')}
        />
      )}
      {tela === 'selecao' && (
        <SelecaoClube
          onVoltar={() => setTela('menu')}
          onConfirmar={(clube) => {
            setClubeSelecionado(clube);
            setTela('simulacao');
          }}
        />
      )}
      {tela === 'simulacao' && (
        <div className="min-h-screen bg-gray-950 flex items-center justify-center">
          <p className="text-white text-2xl">Simulação — {clubeSelecionado}</p>
        </div>
      )}
      {tela === 'creditos' && (
        <Creditos onVoltar={() => setTela('menu')} />
      )}
    </>
  );
}