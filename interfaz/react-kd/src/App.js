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
function Grid({ num }) {
  const [kdTreeNodes, setKDTreeNodes] = useState([]);
  const [xdivisiveLines, setXdivisiveLines] = useState([]);
  const [ydivisveLines, setYdivisiveLines] = useState([]);
  const [nearestNeighbour, setNearestNeighbour] = useState([]);
  useEffect(() => {
    const kdTree = new KDTree();
    kdTree.insert([1, 1]);
    kdTree.insert([10, 2]);
    kdTree.insert([3, 6]);
    kdTree.insert([17, 15]);
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
    const nearestNeighbour = kdTree.nearestNeighbour([13, 15]);
    console.log("nearestNeighbour", nearestNeighbour);
    traverseKDTree(kdTree.root, nearestNeighbour);
    setKDTreeNodes(nodes);
    setXdivisiveLines(lines);
    setYdivisiveLines(lines);
    setNearestNeighbour(nearestNeighbour);
  }, [num]);

  const [gridItems, setGridItems] = useState([]);


  useEffect(() => {
    const rows = [];
    // Busca el nodo más cercano solo después de que la recursión ha terminado
    const nearestNeighbour2 = kdTreeNodes.find(node => node.nearestNeighbour); // Obtén nearestNeighbour2 antes del loop
    for (let i = 0; i < num; i++) {
      const squares = [];
      for (let j = 0; j < num; j++) {
        const isKDTreeNode = kdTreeNodes.some(node => node.x === j && node.y === i);
        const isXDivisiveLine = xdivisiveLines.includes(i);
        const isYDivisiveLine = ydivisveLines.includes(j);

        squares.push(
          <div
            key={`${i}-${j}`}
            className={`square ${isKDTreeNode ? 'kdTreeNode' : ''} ${nearestNeighbour2 ? 'nearestNeighbour' : ''}`}
            style={{
              //if its a kdtree node but not the nearest neighbour, color it green
              backgroundColor: (isKDTreeNode && !nearestNeighbour2) ? 'green' : ((isKDTreeNode && nearestNeighbour2) ? 'blue' : 'white'),
              borderRight: isYDivisiveLine ? '2px solid red' : 'none',
              borderBottom: isXDivisiveLine ? '2px solid red' : 'none',
            }}
          ></div>
        );
      }
      rows.push(
        <div key={i} className="row">
	@@ -192,8 +193,8 @@ function Grid({ num }) {
      );
    }
    setGridItems(rows);
  }, [num, kdTreeNodes, xdivisiveLines]);
  
  return <div className="grid">{gridItems}</div>;
}



// // test 
// const kdTree = new KDTree();
// kdTree.insert([3, 6]);
// kdTree.insert([17, 15]);
// kdTree.insert([13, 15]);
// kdTree.insert([6, 12]);
// kdTree.insert([9, 1]);
// kdTree.insert([2, 7]);

// console.log(kdTree.search([6, 12]));

// //nearest neighbour
// console.log(kdTree.nearestNeighbour([11,12]))





// function Grid({ num, x, y }) {
//   // Create rows and squares dynamically using nested loops
//   const [gridItems, setGridItems] = useState([]);
//   console.log("holaa", x)

//   useEffect(() => {
//     const rows = [];
//     for (let i = 0; i < num; i++) {
//       const squares = [];
//       for (let j = 0; j < num; j++) {
//         // Determine if the current square is at the specified (x, y) coordinates
//         const isRedDot = i === y && j === x;
//         squares.push(
//           <div
//             key={j}
//             className={`square ${isRedDot ? 'redDot' : ''}`}
//           ></div>
//         );
//       }
//       rows.push(
//         <div key={i} className="row">
//           {squares}
//         </div>
//       );
//     }
//     setGridItems(rows);
//   }, [num, x, y]);

//   return <div className="grid">{gridItems}</div>;
// }



// function NumberInputButton() {
//   const [numOne, setNumOne] = useState(''); // State for the first input value
//   const [numTwo, setNumTwo] = useState(''); // State for the second input value
//   const [x, setX] = useState(null); // State for x coordinate
//   const [y, setY] = useState(null); // State for y coordinate

//   const handleInputChange = (e, setValue) => {
//     setValue(e.target.value); // Update the respective state with input value
//   };

//   const handleButtonClick = () => {
//     // Convert numOne and numTwo to integers
//     const parsedNumOne = parseInt(numOne);
//     const parsedNumTwo = parseInt(numTwo);
//     console.log(parsedNumOne, parsedNumTwo)
//     // Check if both inputs are valid numbers
//     if (!isNaN(parsedNumOne) && !isNaN(parsedNumTwo)) {
//       setX(parsedNumOne); // Set x coordinate
//       setY(parsedNumTwo); // Set y coordinate
//     } else {
//       console.log('Please enter valid numbers.'); // Handle invalid input
//     }
//   };

//   return (
//     <div className="numberInputButton">
//       <div className="numberInput">
//         <input
//           type="text"
//           placeholder="Ingresa un número"
//           value={numOne}
//           onChange={(e) => handleInputChange(e, setNumOne)}
//         />
//       </div>
//       <div className="numberInput">
//         <input
//           type="text"
//           placeholder="Ingresa un número"
//           value={numTwo}
//           onChange={(e) => handleInputChange(e, setNumTwo)}
//         />
//       </div>
//       <div className="button">
//         <button type="button" onClick={handleButtonClick}>
//           Enviar
//         </button>
//       </div>
//     </div>
//   );
// }

// function App() {
//   const [x, setX] = useState(null); // State for x coordinate
//   const [y, setY] = useState(null); // State for y coordinate
//   return (
//     <div className="App">
//       <Grid num={6} x={x} y={y} /> {/* Pass x and y values to Grid */}
//       <NumberInputButton />
//     </div>
//   );
// }


// export default App;
