import logo from './logo.svg';
import './App.css';
import React, { useCallback } from 'react';
// import Board from './components/board'
import { useState } from 'react';
import { useEffect } from 'react';

function Grid({ num, x, y }) {
  // Create rows and squares dynamically using nested loops
  const [gridItems, setGridItems] = useState([]);
  console.log("holaa", x)

  useEffect(() => {
    const rows = [];
    for (let i = 0; i < num; i++) {
      const squares = [];
      for (let j = 0; j < num; j++) {
        // Determine if the current square is at the specified (x, y) coordinates
        const isRedDot = i === y && j === x;
        squares.push(
          <div
            key={j}
            className={`square ${isRedDot ? 'redDot' : ''}`}
          ></div>
        );
      }
      rows.push(
        <div key={i} className="row">
          {squares}
        </div>
      );
    }
    setGridItems(rows);
  }, [num, x, y]);

  return <div className="grid">{gridItems}</div>;
}



function NumberInputButton() {
  const [numOne, setNumOne] = useState(''); // State for the first input value
  const [numTwo, setNumTwo] = useState(''); // State for the second input value
  const [x, setX] = useState(null); // State for x coordinate
  const [y, setY] = useState(null); // State for y coordinate

  const handleInputChange = (e, setValue) => {
    setValue(e.target.value); // Update the respective state with input value
  };

  const handleButtonClick = () => {
    // Convert numOne and numTwo to integers
    const parsedNumOne = parseInt(numOne);
    const parsedNumTwo = parseInt(numTwo);
    console.log(parsedNumOne, parsedNumTwo)
    // Check if both inputs are valid numbers
    if (!isNaN(parsedNumOne) && !isNaN(parsedNumTwo)) {
      setX(parsedNumOne); // Set x coordinate
      setY(parsedNumTwo); // Set y coordinate
    } else {
      console.log('Please enter valid numbers.'); // Handle invalid input
    }
  };

  return (
    <div className="numberInputButton">
      <div className="numberInput">
        <input
          type="text"
          placeholder="Ingresa un número"
          value={numOne}
          onChange={(e) => handleInputChange(e, setNumOne)}
        />
      </div>
      <div className="numberInput">
        <input
          type="text"
          placeholder="Ingresa un número"
          value={numTwo}
          onChange={(e) => handleInputChange(e, setNumTwo)}
        />
      </div>
      <div className="button">
        <button type="button" onClick={handleButtonClick}>
          Enviar
        </button>
      </div>
    </div>
  );
}

function App() {
  const [x, setX] = useState(null); // State for x coordinate
  const [y, setY] = useState(null); // State for y coordinate
  return (
    <div className="App">
      <Grid num={6} x={x} y={y} /> {/* Pass x and y values to Grid */}
      <NumberInputButton />
    </div>
  );
}


export default App;
