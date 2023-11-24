//
// Created by MacBookPro on 23/11/23.
//
#import "kdtree.h"
#import "quadtree.h"
#import <iostream>
#import <fstream>

using namespace std;

int main(){
    //Test the kdtree
    KDTreeNode* root = nullptr;
    int point1[5] = {3, 6, 2, 1, 4};
    int point2[5] = {17, 15, 8, 9, 10};
    int point3[5] = {13, 15, 3, 5, 7};
    int point4[5] = {6, 12, 4, 6, 8};
    int point5[5] = {9, 1, 5, 7, 9};
    int point6[5] = {2, 7, 6, 8, 10};
    int point7[5] = {10, 19, 7, 9, 11};

    root = KDtree::insert(root, point1);
    root = KDtree::insert(root, point2);
    root = KDtree::insert(root, point3);
    root = KDtree::insert(root, point4);
    root = KDtree::insert(root, point5);
    root = KDtree::insert(root, point6);
    root = KDtree::insert(root, point7);
    

    KDtree::display(root, 0);

    //test nearest neighbor
    int point8[5] = {2, 3, 4, 5, 6};
    KDTreeNode* nearest = KDtree::nearestNeighbor(root, point3);
    cout << "Nearest neighbor to (17, 15, 8, 9, 10): (" << nearest->dataPoint[0] << ", " << nearest->dataPoint[1] << "," << nearest->dataPoint[2] << "," << nearest->dataPoint[3] << "," << nearest->dataPoint[4] << ")" << endl;

    //test search
    int point9[5] = {1, 2, 3, 4, 5};
    bool found = KDtree::search(root, point9);

    if (found)
        cout << "Found point (1, 2, 3, 4, 5)" << endl;
    else
        cout << "Did not find point (1, 2, 3, 4, 5)" << endl;

    //test quadtree



    return 0;
}