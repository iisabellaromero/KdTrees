//
// Created by MacBookPro on 23/11/23.
//

#ifndef PATHFINDING_GRUPOPATHFINDING_QUADNODE_H
#define PATHFINDING_GRUPOPATHFINDING_QUADNODE_H

#include <iostream>


class QuadPoint {
public:
    int coordinates[2];

    QuadPoint(int x, int y) {
        coordinates[0] = x;
        coordinates[1] = y;
    }
    QuadPoint() {
        coordinates[0] = 0;
        coordinates[1] = 0;
    }
};

class QuadTreeNode {
public:
    QuadPoint dataPoint;
    int data;

    QuadTreeNode(QuadPoint dataPt, int d) : dataPoint(dataPt), data(d) {}

    QuadTreeNode() : data(0) {}
};

#endif //PATHFINDING_GRUPOPATHFINDING_QUADNODE_H
