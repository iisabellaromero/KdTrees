import logo from './logo.svg';
import './App.css';
import React from 'react';
// import Board from './components/board'

function Grid({ num }) {
  // Create rows and squares dynamically using nested loops
  const rows = [];
  for (let i = 0; i < num; i++) {
    const squares = [];
    for (let j = 0; j < num; j++) {
      squares.push(<div key={j} className="square"></div>);
    }
    rows.push(
      <div key={i} className="row">
        {squares}
      </div>
    );
  }

  return <div className="grid">{rows}</div>;
}

function NumberInputButton() {
  return (
    <div className="numberInputButton">
      <div className="numberInput">
        <input type="text" placeholder="Ingresa un número" />
      </div>
      <div className="numberInput">
        <input type="text" placeholder="Ingresa un número" />
      </div>
      <div className="button">
        <button type="submit">Enviar</button>
      </div>
    </div>
  );
}

function App() {
  return (

    <div className="App">
      <Grid num={6} />
      <NumberInputButton />
    </div>
  );
}

export default App;
