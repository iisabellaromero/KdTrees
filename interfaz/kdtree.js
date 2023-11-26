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

    nearestNeighbour(dataPoint){
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
