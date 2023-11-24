//
// Created by MacBookPro on 23/11/23.
//

#ifndef PATHFINDING_GRUPOPATHFINDING_QUEADTREE_H
#define PATHFINDING_GRUPOPATHFINDING_QUEADTREE_H
#include <iostream>
#include <cmath>
#include "quadnode.h"


class Quad {
public:
    QuadPoint bottomLeft;
    QuadPoint topRight;

    QuadTreeNode* node;

    Quad* topLeftTree;
    Quad* topRightTree;
    Quad* botLeftTree;
    Quad* botRightTree;

    Quad() {
        bottomLeft = QuadPoint(0, 0);
        topRight = QuadPoint(0, 0);
        node = nullptr;
        topLeftTree = nullptr;
        topRightTree = nullptr;
        botLeftTree = nullptr;
        botRightTree = nullptr;
    }

    Quad(QuadPoint topL, QuadPoint botR) {
        node = nullptr;
        topLeftTree = nullptr;
        topRightTree = nullptr;
        botLeftTree = nullptr;
        botRightTree = nullptr;
        bottomLeft = topL;
        topRight = botR;
    }
    bool withinWindow(QuadPoint p) {
        return (p.coordinates[0] >= bottomLeft.coordinates[0] &&
                p.coordinates[0] <= topRight.coordinates[0] &&
                p.coordinates[1] >= bottomLeft.coordinates[1] &&
                p.coordinates[1] <= topRight.coordinates[1]);
    }

    void insert(QuadTreeNode* newNode) {
        if (newNode == nullptr)
            return;

        if (!withinWindow(newNode->dataPoint))
            return;

        if (node == nullptr) {
            node = newNode;
            return;
        }

        if ((bottomLeft.coordinates[0] + topRight.coordinates[0]) / 2 >= newNode->dataPoint.coordinates[0]) {
            if ((bottomLeft.coordinates[1] + topRight.coordinates[1]) / 2 >= newNode->dataPoint.coordinates[1]) {
                if (botLeftTree == nullptr) {
                    botLeftTree = new Quad(
                            QuadPoint(bottomLeft.coordinates[0], bottomLeft.coordinates[1]),
                            QuadPoint((bottomLeft.coordinates[0] + topRight.coordinates[0]) / 2, (bottomLeft.coordinates[1] + topRight.coordinates[1]) / 2)
                    );
                }
                botLeftTree->insert(newNode);
            } else {
                if (topLeftTree == nullptr) {
                    topLeftTree = new Quad(
                            QuadPoint(bottomLeft.coordinates[0], (bottomLeft.coordinates[1] + topRight.coordinates[1]) / 2),
                            QuadPoint((bottomLeft.coordinates[0] + topRight.coordinates[0]) / 2, topRight.coordinates[1])
                    );
                }
                topLeftTree->insert(newNode);
            }
        } else {
            if ((bottomLeft.coordinates[1] + topRight.coordinates[1]) / 2 >= newNode->dataPoint.coordinates[1]) {
                if (botRightTree == nullptr) {
                    botRightTree = new Quad(
                            QuadPoint((bottomLeft.coordinates[0] + topRight.coordinates[0]) / 2, bottomLeft.coordinates[1]),
                            QuadPoint(topRight.coordinates[0], (bottomLeft.coordinates[1] + topRight.coordinates[1]) / 2)
                    );
                }
                botRightTree->insert(newNode);
            } else {
                if (topRightTree == nullptr) {
                    topRightTree = new Quad(
                            QuadPoint((bottomLeft.coordinates[0] + topRight.coordinates[0]) / 2, (bottomLeft.coordinates[1] + topRight.coordinates[1]) / 2),
                            QuadPoint(topRight.coordinates[0], topRight.coordinates[1])
                    );
                }
                topRightTree->insert(newNode);
            }
        }
    }


    QuadTreeNode* nearestNeighbor(QuadPoint p, int botLeftPoint[], int topRightPoint[]) {
        if (node == nullptr)
            return nullptr;

        QuadTreeNode* bestNode = node;
        double bestDist = euclideanDist(p, node->dataPoint);

        if (botLeftTree == nullptr && botRightTree == nullptr && topLeftTree == nullptr && topRightTree == nullptr)
            return bestNode;

        if (botLeftTree != nullptr && checkRectOverlap(botLeftTree, botLeftPoint, topRightPoint)) {
            QuadTreeNode* temp = botLeftTree->nearestNeighbor(p, botLeftPoint, topRightPoint);
            if (temp != nullptr && euclideanDist(p, temp->dataPoint) < bestDist) {
                bestNode = temp;
                bestDist = euclideanDist(p, temp->dataPoint);
            }
        }

        if (botRightTree != nullptr && checkRectOverlap(botRightTree, botLeftPoint, topRightPoint)) {
            QuadTreeNode* temp = botRightTree->nearestNeighbor(p, botLeftPoint, topRightPoint);
            if (temp != nullptr && euclideanDist(p, temp->dataPoint) < bestDist) {
                bestNode = temp;
                bestDist = euclideanDist(p, temp->dataPoint);
            }
        }

        if (topLeftTree != nullptr && checkRectOverlap(topLeftTree, botLeftPoint, topRightPoint)) {
            QuadTreeNode* temp = topLeftTree->nearestNeighbor(p, botLeftPoint, topRightPoint);
            if (temp != nullptr && euclideanDist(p, temp->dataPoint) < bestDist) {
                bestNode = temp;
                bestDist = euclideanDist(p, temp->dataPoint);
            }
        }

        if (topRightTree != nullptr && checkRectOverlap(topRightTree, botLeftPoint, topRightPoint)) {
            QuadTreeNode* temp = topRightTree->nearestNeighbor(p, botLeftPoint, topRightPoint);
            if (temp != nullptr && euclideanDist(p, temp->dataPoint) < bestDist) {
                bestNode = temp;
                bestDist = euclideanDist(p, temp->dataPoint);
            }
        }

        return bestNode;
    }

    bool checkRectOverlap(Quad* node, int l2[], int r2[]) {
        if (node == nullptr)
            return false;

        if (node->topRight.coordinates[0] < l2[0] || bottomLeft.coordinates[0] > r2[0])
            return false;

        if (node->topRight.coordinates[1] < l2[1] || bottomLeft.coordinates[1] > r2[1])
            return false;

        return true;
    }

    double euclideanDist(QuadPoint a, QuadPoint b) {
        return std::sqrt((b.coordinates[1] - a.coordinates[1]) * (b.coordinates[1] - a.coordinates[1]) + (b.coordinates[0] - a.coordinates[0]) * (b.coordinates[0] - a.coordinates[0]));
    }

    QuadTreeNode* search(QuadPoint p) {
        if (node == nullptr)
            return nullptr;

        if (node->dataPoint.coordinates[0] == p.coordinates[0] && node->dataPoint.coordinates[1] == p.coordinates[1])
            return node;

        if (botLeftTree != nullptr && botLeftTree->withinWindow(p))
            return botLeftTree->search(p);

        if (botRightTree != nullptr && botRightTree->withinWindow(p))
            return botRightTree->search(p);

        if (topLeftTree != nullptr && topLeftTree->withinWindow(p))
            return topLeftTree->search(p);

        if (topRightTree != nullptr && topRightTree->withinWindow(p))
            return topRightTree->search(p);

        return nullptr;
    }
};
#endif //PATHFINDING_GRUPOPATHFINDING_QUEADTREE_H
