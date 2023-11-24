//
// Created by MacBookPro on 23/11/23.
//

#ifndef PATHFINDING_GRUPOPATHFINDING_KDNODE_H
#define PATHFINDING_GRUPOPATHFINDING_KDNODE_H

class KDTreeNode {
public:
    int dataPoint[2];
    static const int DIMENSION = 2; // dos dimensiones

    KDTreeNode* left;
    KDTreeNode* right;

    KDTreeNode(int point[]) {
        for (int i = 0; i < DIMENSION; i++) {
            dataPoint[i] = point[i];
        }
        left = nullptr;
        right = nullptr;
    }
};

#endif //PATHFINDING_GRUPOPATHFINDING_KDNODE_H
