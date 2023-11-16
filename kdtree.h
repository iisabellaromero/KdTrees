#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include "KDNode.h"
using namespace std;

class KDTree
{
    KDNode *root;

    KDNode *buildKdTree(std::vector<int*> &points, int depth){
        if(points.size() == 0){
            return NULL;
        }
        int dim = depth % 2;
        int median = points.size() / 2;
        KDNode *node = new KDNode(dim, points[median]);
        std::vector<int*> leftPoints;
        std::vector<int*> rightPoints;
        for(int i = 0; i < points.size(); i++){
            if(i != median){
                if(points[i][dim] < points[median][dim]){
                    leftPoints.push_back(points[i]);
                }
                else{
                    rightPoints.push_back(points[i]);
                }
            }
        }
        node->setLeft(buildKdTree(leftPoints, depth + 1));
        node->setRight(buildKdTree(rightPoints, depth + 1));
        return node;
    }
    
public:

    KDNode *getRoot(){
        return root;
    }

    void setRoot(KDNode *root){
        this->root = root;
    }

    //Constructor
    KDTree(std::vector<int*> &points){
        root = buildKdTree(points, 0);
    }

    //Destructor
    ~KDTree(){
        delete root;
    }

    //Insert
    void insert(int dim, int *pointData){
        KDNode *newNode = new KDNode(dim, pointData);
        if(root == NULL){
            root = newNode;
        }
        else{
            KDNode *current = root;
            KDNode *parent = NULL;
            while(current != NULL){
                parent = current;
                if(pointData[current->getDim()] < current->getData()[current->getDim()]){
                    current = current->getLeft();
                }
                else{
                    current = current->getRight();
                }
            }
            if(pointData[parent->getDim()] < parent->getData()[parent->getDim()]){
                parent->setLeft(newNode);
            }
            else{
                parent->setRight(newNode);
            }
        }
    }
};

#endif  // KDTREE_H