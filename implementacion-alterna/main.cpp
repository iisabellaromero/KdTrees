//
// Created by MacBookPro on 23/11/23.
//
#import "kdtree.h"
#import "quadtree.h"
#import <iostream>
#import <fstream>

int main(){
    //Test the kdtree
    KDTreeNode* root = nullptr;
    int point1[2] = {1, 2};
    int point2[2] = {3, 4};
    int point3[2] = {5, 6};
    int point4[2] = {7, 8};
    int point5[2] = {9, 10};

    root = KDtree::insert(root, point1);
    root = KDtree::insert(root, point2);
    root = KDtree::insert(root, point3);
    root = KDtree::insert(root, point4);
    root = KDtree::insert(root, point5);

    KDtree::display(root, 0);

    //test nearest neighbor
    int point6[2] = {2, 3};
    KDTreeNode* nearest = KDtree::nearestNeighbour(root, point6);
    std::cout << "Nearest neighbor to (2, 3): (" << nearest->dataPoint[0] << ", " << nearest->dataPoint[1] << ")" << std::endl;

    //test search
    int point7[2] = {1, 2};
    bool found = KDtree::search(root, point7);

    if (found)
        std::cout << "Found point (1, 2)" << std::endl;
    else
        std::cout << "Did not find point (1, 2)" << std::endl;

    //test quadtree
    QuadPoint topLeft = QuadPoint(0, 0);
    QuadPoint botRight = QuadPoint(10, 10);
    Quad* quad = new Quad(topLeft, botRight);

    int point8[2] = {1, 2};
    int point9[2] = {3, 4};
    int point10[2] = {5, 6};
    int point11[2] = {7, 8};
    int point12[2] = {9, 10};

   QuadTreeNode node = QuadTreeNode(QuadPoint(1, 2), 1);
    QuadTreeNode node2 = QuadTreeNode(QuadPoint(3, 4), 2);
    QuadTreeNode node3 = QuadTreeNode(QuadPoint(5, 6), 3);
    QuadTreeNode node4 = QuadTreeNode(QuadPoint(7, 8), 4);
    QuadTreeNode node5 = QuadTreeNode(QuadPoint(9, 10), 5);

    quad->insert(&node);
    quad->insert(&node2);
    quad->insert(&node3);
    quad->insert(&node4);
    quad->insert(&node5);


//test nearest neighbor
    int point13[2] = {2, 3};
    QuadTreeNode* nearest2 = quad->nearestNeighbor(QuadPoint(2, 3), point13, point13);
    std::cout << "Nearest neighbor to (2, 3): (" << nearest2->dataPoint.coordinates[0] << ", " << nearest2->dataPoint.coordinates[1] << ")" << std::endl;

    //test search
    int point14[2] = {1, 2};
    bool found2 = quad->search(QuadPoint(1, 2));

    if (found2)
        std::cout << "Found point (1, 2)" << std::endl;
    else
        std::cout << "Did not find point (1, 2)" << std::endl;


    return 0;
}