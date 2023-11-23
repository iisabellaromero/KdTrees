//
// Created by MacBookPro on 23/11/23.
//

#ifndef PATHFINDING_GRUPOPATHFINDING_KDTREE_H
#define PATHFINDING_GRUPOPATHFINDING_KDTREE_H
#include <iostream>
#include <cmath>
#include <limits>
#include "kdnode.h"

class KDtree {
private:
    static KDTreeNode* insertNode(KDTreeNode* root, int dataPoint[], int depth) {
        if (root == nullptr)
            return new KDTreeNode(dataPoint);

        int currentDimension = depth % KDTreeNode::DIMENSION;

        if (dataPoint[currentDimension] < (root->dataPoint[currentDimension]))
            root->left = insertNode(root->left, dataPoint, depth + 1);
        else
            root->right = insertNode(root->right, dataPoint, depth + 1);
        return root;
    }

    static bool arePointsEqual(int point1[], int point2[]) {
        for (int i = 0; i < KDTreeNode::DIMENSION; ++i)
            if (point1[i] != point2[i])
                return false;

        return true;
    }

    static bool searchNode(KDTreeNode* root, int dataPoint[], int depth) {
        if (root == nullptr)
            return false;
        if (arePointsEqual(root->dataPoint, dataPoint))
            return true;

        int currentDimension = depth % KDTreeNode::DIMENSION;

        if (dataPoint[currentDimension] < root->dataPoint[currentDimension])
            return searchNode(root->left, dataPoint, depth + 1);
        else
            return searchNode(root->right, dataPoint, depth + 1);
    }

    static double euclideanDistance(int a[], int b[]) {
        if (a == nullptr || b == nullptr)
            return std::numeric_limits<double>::max();
        return std::sqrt((b[1] - a[1]) * (b[1] - a[1]) + (b[0] - a[0]) * (b[0] - a[0]));
    }

public:
    static KDTreeNode* insert(KDTreeNode* root, int dataPoint[]) {
        return insertNode(root, dataPoint, 0);
    }

    static bool search(KDTreeNode* root, int dataPoint[]) {
        return searchNode(root, dataPoint, 0);
    }

    static KDTreeNode* nearestNeighbour(KDTreeNode* root, int dataPoint[]) {
        return searchNearestNeighbour(root, dataPoint, std::numeric_limits<double>::max(), root);
    }

    static KDTreeNode* searchNearestNeighbour(KDTreeNode* root, int dataPoint[], double minDist, KDTreeNode* bestNode) {
        if (root == nullptr)
            return bestNode;

        double distanceFromNode = euclideanDistance(root->dataPoint, dataPoint);
        if (euclideanDistance(root->dataPoint, dataPoint) < minDist) {
            minDist = distanceFromNode;
            bestNode = root;
        }
        if (root->left == nullptr)
            return searchNearestNeighbour(root->right, dataPoint, minDist, bestNode);
        if (root->right == nullptr)
            return searchNearestNeighbour(root->left, dataPoint, minDist, bestNode);

        if (euclideanDistance(root->left->dataPoint, dataPoint) < euclideanDistance(root->right->dataPoint, dataPoint))
            bestNode = searchNearestNeighbour(root->left, dataPoint, minDist, bestNode);
        else
            bestNode = searchNearestNeighbour(root->right, dataPoint, minDist, bestNode);
        return bestNode;
    }

    static void display(KDTreeNode* root, int depth) {
        if (root == nullptr)
            return;

        int currentDimension = depth % KDTreeNode::DIMENSION;

        std::cout << "(" << root->dataPoint[0] << ", " << root->dataPoint[1] << ") " << currentDimension << std::endl;

        display(root->left, depth + 1);
        display(root->right, depth + 1);

    };
};

#endif //PATHFINDING_GRUPOPATHFINDING_KDTREE_H
