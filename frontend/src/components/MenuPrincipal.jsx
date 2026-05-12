import MFCShield from './MFCShield';

const TEAM_IDS = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20];

const TIMES_SIGLAS = {
  1:'FLA',2:'CAM',3:'PAL',4:'FLU',5:'CAP',6:'INT',7:'SAO',8:'GRE',9:'BOT',10:'VAS',
  11:'COR',12:'CRU',13:'BAH',14:'SAN',15:'RBB',16:'CHA',17:'CFC',18:'VIT',19:'MIR',20:'REM',
};

export default function MenuPrincipal({ onNovoJogo }) {
  return (
    <div className="mfc-screen" style={{
      display: 'flex', flexDirection: 'column',
      alignItems: 'center', justifyContent: 'center',
      position: 'relative', overflow: 'hidden',
      backgroundColor: 'var(--c-bg)',
      backgroundImage: 'url("/estadio.jpg")',
      backgroundSize: 'cover',
      backgroundPosition: 'center',
      backgroundRepeat: 'no-repeat',
    }}>
      <div style={{
        position: 'absolute', inset: 0, pointerEvents: 'none',
        background: 'linear-gradient(180deg, rgba(6,13,6,0.78) 0%, rgba(6,13,6,0.55) 40%, rgba(6,13,6,0.85) 100%)',
      }} />
      <div style={{
        position: 'absolute', inset: 0, pointerEvents: 'none',
        backgroundImage: 'repeating-linear-gradient(0deg,rgba(0,0,0,0.18) 0px,rgba(0,0,0,0.18) 1px,transparent 1px,transparent 3px)',
      }} />

      <div style={{ position: 'relative', zIndex: 10, textAlign: 'center' }}>
        <div className="mfc-menu-eyebrow">BRASILEIRAO SERIE A 2026</div>
        <div className="mfc-menu-logo">MANAGER FC</div>
        <div className="mfc-menu-tagline">gerencie seu clube ao topo</div>

        <div style={{
          display: 'flex', justifyContent: 'center', flexWrap: 'wrap', gap: '10px',
          maxWidth: '560px', margin: '0 auto 28px', opacity: 0.92,
        }}>
          {TEAM_IDS.map(id => (
            <MFCShield key={id} teamId={id} sigla={TIMES_SIGLAS[id]} size={28} />
          ))}
        </div>

        <div style={{ display: 'flex', flexDirection: 'column', gap: '6px', width: '300px', margin: '0 auto' }}>
          <button className="mfc-btn mfc-btn-primary mfc-btn-lg" onClick={onNovoJogo}>
            ▶ NOVO JOGO
          </button>
          <button className="mfc-btn mfc-btn-lg" style={{ opacity: 0.5, cursor: 'default' }}>
            CRÉDITOS
          </button>
        </div>
      </div>

      <div className="mfc-menu-version">v0.2.0 — CIn/UFPE</div>
    </div>
  );
}
