import logo from './logo.svg';
import './App.css';
import React, { useState, useEffect } from 'react';


class KDTree{
  constructor(){
      this.root = null;
  }

  insert(dataPoint){
      this.root = KDTreeOperations.insert(this.root, dataPoint);
  }

  search(dataPoint){
      return KDTreeOperations.search(this.root, dataPoint);
  }

  nearestNeighbour(dataPoint) {
    return KDTreeOperations.nearestNeighbour(this.root, dataPoint);
  }
}

class KDTreeNode {
  constructor(point) {
      this.dataPoint = new Array(2);
      for (let i = 0; i < point.length; i++) {
          this.dataPoint[i] = point[i];
      }
      this.left = null;
      this.right = null;
  }
}

KDTreeNode.DIMENSION = 2;

class KDTreeOperations {
  static insertNode(root, dataPoint, depth) {
    if (root === null) {
      return new KDTreeNode(dataPoint);
    }
    const currentDimension = depth % KDTreeNode.DIMENSION;
    if (dataPoint[currentDimension] < root.dataPoint[currentDimension]) {
      root.left = KDTreeOperations.insertNode(root.left, dataPoint, depth + 1);
    } else {
      root.right = KDTreeOperations.insertNode(root.right, dataPoint, depth + 1);
    }
    return root;
  }

  static insert(root, dataPoint) {
    return KDTreeOperations.insertNode(root, dataPoint, 0);
  }

  static arePointsEqual(point1, point2) {
    for (let i = 0; i < KDTreeNode.DIMENSION; ++i) {
      if (point1[i] !== point2[i]) {
        return false;
      }
    }
    return true;
  }

  static search(root, dataPoint) {
    return KDTreeOperations.searchNode(root, dataPoint, 0);
  }

  static searchNode(root, dataPoint, depth) {
    if (root === null) {
      return false;
    }
    if (KDTreeOperations.arePointsEqual(root.dataPoint, dataPoint)) {
      return true;
    }
    const currentDimension = depth % KDTreeNode.DIMENSION;
    if (dataPoint[currentDimension] < root.dataPoint[currentDimension]) {
      return KDTreeOperations.searchNode(root.left, dataPoint, depth + 1);
    } else {
      return KDTreeOperations.searchNode(root.right, dataPoint, depth + 1);
    }
  }

  static nearestNeighbour(root, dataPoint) {
    return KDTreeOperations.searchNearestNeighbour(root, dataPoint, Number.MAX_VALUE, root);
  }

  static searchNearestNeighbour(root, dataPoint, minDist, bestNode) {
    if (root === null) {
      return bestNode;
    }
    const distanceFromNode = KDTreeOperations.euclidianDistance(root.dataPoint, dataPoint);
    if (KDTreeOperations.euclidianDistance(root.dataPoint, dataPoint) < minDist) {
      minDist = distanceFromNode;
      bestNode = root;
    }
    if (root.left === null) {
      return KDTreeOperations.searchNearestNeighbour(root.right, dataPoint, minDist, bestNode);
    }
    if (root.right === null) {
      return KDTreeOperations.searchNearestNeighbour(root.left, dataPoint, minDist, bestNode);
    }
    if (KDTreeOperations.euclidianDistance(root.left.dataPoint, dataPoint) < KDTreeOperations.euclidianDistance(root.right.dataPoint, dataPoint)) {
      bestNode = KDTreeOperations.searchNearestNeighbour(root.left, dataPoint, minDist, bestNode);
    } else {
      bestNode = KDTreeOperations.searchNearestNeighbour(root.right, dataPoint, minDist, bestNode);
    }
    return bestNode;
  }

  static euclidianDistance(a, b) {
    if (a === null || b === null) {
      return Number.MAX_VALUE;
    }
    return Math.sqrt((b[1] - a[1]) * (b[1] - a[1]) + (b[0] - a[0]) * (b[0] - a[0]));
  }
}


function Grid({ num, nearestNeighborCoordinates}) {
  console.log("inside grid " , nearestNeighborCoordinates)
  const [kdTreeNodes, setKDTreeNodes] = useState([]);
  const [xdivisiveLines, setXdivisiveLines] = useState([]);
  const [ydivisveLines, setYdivisiveLines] = useState([]);
  const [nearestNeighbour, setNearestNeighbour] = useState([]);

  useEffect(() => {
    const kdTree = new KDTree();
    kdTree.insert([10,10])
    kdTree.insert([5,5])
    kdTree.insert([15,15])
    kdTree.insert([3,2])
    kdTree.insert([2,7])

    // kdTree.insert([19,19])
    kdTree.insert([0,20])


    const nodes = [];
    const lines = [];

    // Function to traverse the KD tree and collect nodes and divisive lines for visualization
    const traverseKDTree = (node) => {
      if (node) {
        nodes.push({ x: node.dataPoint[0], 
          y: node.dataPoint[1], 
          isDivisive: node.left || node.right,
          nearestNeighbour: kdTree.nearestNeighbour([node.dataPoint[0], node.dataPoint[1]]) });
        if (node.left || node.right) {
          lines.push(node.dataPoint[0]);
        }
        traverseKDTree(node.left);
        traverseKDTree(node.right);
      }
    };
    const x = nearestNeighborCoordinates[0];
    const y = nearestNeighborCoordinates[1];
    
    const nearestNeighbour = kdTree.nearestNeighbour([x,y]);

    traverseKDTree(kdTree.root, nearestNeighbour);
    setKDTreeNodes(nodes);
    setXdivisiveLines(lines);
    setYdivisiveLines(lines);
    setNearestNeighbour(nearestNeighbour);
  }, [num, nearestNeighborCoordinates]);

  const [gridItems, setGridItems] = useState([]);


  useEffect(() => {
    const rows = [];
    // Busca el nodo más cercano solo después de que la recursión ha terminado
    console.log("inside grid useffect", nearestNeighbour)
    const nearestNeighbour2 = kdTreeNodes.find(node => node.x === nearestNeighbour.dataPoint[0] && node.y === nearestNeighbour.dataPoint[1]);
    // console.log(nearestNeighbour2)
    
    // console.log(nearestNeighbour2.dataPoint)
    for (let i = 0; i < num; i++) {
      const squares = [];
      for (let j = 0; j < num; j++) {
        const isKDTreeNode = kdTreeNodes.some(node => node.x === j && node.y === i);
        const isXDivisiveLine = xdivisiveLines.includes(i);
        const isYDivisiveLine = ydivisveLines.includes(j);
        // console.log("llave: " ,i,",", j)
        // console.log(nearestNeighbour2)
        if (nearestNeighbour2 && j == nearestNeighbour2.x && i == nearestNeighbour2.y){
          console.log(nearestNeighbour2.dataPoint)
          squares.push(
            <div
              
              key={`${i}-${j}`}
              className={`square ${isKDTreeNode ? 'kdTreeNode' : ''}}`}
              style={{
                backgroundColor: 'blue' ,
                borderRight: isYDivisiveLine ? '2px solid red' : 'none',
                borderBottom: isXDivisiveLine ? '2px solid red' : 'none',
              }}
            >{i},{ j}</div>
          );
        }
        else {
                  squares.push(
                    <div
                      key={`${i}-${j}`}
                      className={`square ${isKDTreeNode ? 'kdTreeNode' : ''}}`}
                      style={{
                        //if its a kdtree node but not the nearest neighbour, color it green
                        backgroundColor: (isKDTreeNode ) ? 'green' : 'white',
                        borderRight: isYDivisiveLine ? '2px solid red' : 'none',
                        borderBottom: isXDivisiveLine ? '2px solid red' : 'none',
                      }}
                    >{j},{i}</div>
                  );
                }
        }
      rows.push(
        <div key={i} className="row">
          {squares}
        </div>
      );
    }
    setGridItems(rows);
  }, [num, kdTreeNodes, xdivisiveLines]);
  
  return <div className="grid">{gridItems}</div>;
}

function NumberInputButton({ texto, onCoordinateSubmit }) {
  const [numOne, setNumOne] = useState(''); // State for the first input value
  const [numTwo, setNumTwo] = useState(''); // State for the second input value

  const handleCoordinateSubmit = () => {
    const xCoordinate = parseInt(numOne);
    const yCoordinate = parseInt(numTwo);

    if (!isNaN(xCoordinate) && !isNaN(yCoordinate)) {
      console.log(`Entered coordinate: (${xCoordinate}, ${yCoordinate})`);
      onCoordinateSubmit([xCoordinate, yCoordinate]); // Pass coordinates to the callback
    } else {
      console.log('Please enter valid numbers for both coordinates.');
    }
  };

  return (
    <div className="numberInputButton">
      <div className="numberInput">
        <h1>{texto}</h1>
        <input
          type="text"
          placeholder="Coordenada x"
          value={numOne}
          onChange={(e) => setNumOne(e.target.value)}
        />
      </div>
      <div className="numberInput">
        <input
          type="text"
          placeholder="Coordenada y"
          value={numTwo}
          onChange={(e) => setNumTwo(e.target.value)}
        />
      </div>
      <div className="button">
        <button type="button" onClick={handleCoordinateSubmit}>
          Submit
        </button>
      </div>
    </div>
  );
}

// Updated App component
function App() {
  const [nearestNeighborCoordinates, setNearestNeighborCoordinates] = useState([]);

  const handleNearestNeighborSearch = (coordinates) => {
    console.log('your coordinates', coordinates)
    setNearestNeighborCoordinates(coordinates);
    console.log(nearestNeighborCoordinates)
  };

  return (
    <div className="App">
      <div className='row'>
        <div className='col'>
          <Grid num={20} nearestNeighborCoordinates={nearestNeighborCoordinates} />
        </div>
        <div className='col'>
          <NumberInputButton texto={'Encontrar nearest neighbour'} onCoordinateSubmit={handleNearestNeighborSearch} />
          {/* Add other NumberInputButton components here with respective functionalities */}
        </div>
      </div>
    </div>
  );
}

export default App;

// //input button
// function NumberInputButton({texto}) {
//   const [numOne, setNumOne] = useState(''); // State for the first input value
//   const [numTwo, setNumTwo] = useState(''); // State for the second input value


//   const handleCoordinateSubmit = () => {
//     const xCoordinate = parseInt(numOne);
//     const yCoordinate = parseInt(numTwo);

//     if (!isNaN(xCoordinate) && !isNaN(yCoordinate)) {
//       console.log(`Entered coordinate: (${xCoordinate}, ${yCoordinate})`);
      
//     } else {
//       console.log('Please enter valid numbers for both coordinates.');
//     }
//   };

//   return (
//     <div className="numberInputButton">
//       <div className="numberInput">
//         <h1>{texto}</h1>
//         <input
//           type="text"
//           placeholder="Coordenada x"
//           value={numOne}
//           onChange={(e) => setNumOne(e.target.value)}
//         />
//       </div>
//       <div className="numberInput">
//         <input
//           type="text"
//           placeholder="Coordenada y"
//           value={numTwo}
//           onChange={(e) => setNumTwo(e.target.value)}
//         />
//       </div>
//       <div className="button">
//         <button type="button" onClick={handleCoordinateSubmit}>
//           Submit
//         </button>
//       </div>
//     </div>
//   );
// }


// function App() {
//   return (
//     <div className="App">
//           <div className='row'>
//         <div className='col'>
//         <Grid num={20} />

//         </div>
//         <div className='col'>
//         <NumberInputButton texto={'Encontrar nearest neighbour'}/>
//         <NumberInputButton texto={'Probar search'}/>
//         </div>

//       </div>
      
//     </div>
//   );
// }

// export default App;

