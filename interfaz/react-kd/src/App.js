import logo from './logo.svg';
import './App.css';
import React from 'react';
// import Board from './components/board'

function Grid(){
  return(
    <div className="grid">
      <div className="row">
        <div className="square"></div>
        <div className="square"></div>
        <div className="square"></div>
      </div>
      <div className="row">
        <div className="square"></div>
        <div className="square"></div>
        <div className="square"></div>
      </div>
      <div className="row">
        <div className="square"></div>
        <div className="square"></div>
        <div className="square"></div>
      </div>
    </div>
  )
}


function App() {
  return (

    <div className="App">
      <Grid />
    </div>
  );
}

export default App;
