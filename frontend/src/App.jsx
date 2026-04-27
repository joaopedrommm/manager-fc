import { useState } from 'react';
import MenuPrincipal from './components/MenuPrincipal';
import SelecaoClube from './components/SelecaoClube';

export default function App() {
  const [tela, setTela] = useState('menu');

  return (
    <>
      {tela === 'menu' && <MenuPrincipal onNovoJogo={() => setTela('selecao')} />}
      {tela === 'selecao' && <SelecaoClube onVoltar={() => setTela('menu')} />}
    </>
  );
}