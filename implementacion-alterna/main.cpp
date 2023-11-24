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
    int point1[2] = {3, 6};
    int point2[2] = {17, 15};
    int point3[2] = {13, 15};
    int point4[2] = {6, 12};
    int point5[2] = {9, 1};
    int point6[2] = {2, 7};
    int point7[2] = {10, 19};

    root = KDtree::insert(root, point1);
    root = KDtree::insert(root, point2);
    root = KDtree::insert(root, point3);
    root = KDtree::insert(root, point4);
    root = KDtree::insert(root, point5);
    root = KDtree::insert(root, point6);
    root = KDtree::insert(root, point7);
    

    KDtree::display(root, 0);

    //test nearest neighbor
    int point8[2] = {2, 3};
    KDTreeNode* nearest = KDtree::nearestNeighbor(root, point3);
    std::cout << "Nearest neighbor to (17,15): (" << nearest->dataPoint[0] << ", " << nearest->dataPoint[1] << ")" << std::endl;

    //test search
    int point9[2] = {1, 2};
    bool found = KDtree::search(root, point7);

    if (found)
        std::cout << "Found point (1, 2)" << std::endl;
    else
        std::cout << "Did not find point (1, 2)" << std::endl;

    //test quadtree



    return 0;
}