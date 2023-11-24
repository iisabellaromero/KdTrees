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
    int point1[5] = {3, 6};
    int point2[5] = {17, 15};
    int point3[5] = {13, 15};
    int point4[5] = {6, 12};
    int point5[5] = {9, 1};
    int point6[5] = {2, 7};
    int point7[5] = {10, 19};

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
    cout << "Nearest neighbor to (17, 15): (" << nearest->dataPoint[0] << ", " << nearest->dataPoint[1] << ")" << endl;

    // Insert (uncomment for found to be true)
    //int pointTest[2] = {1, 2};
    //root = KDtree::insert(root, pointTest);

    //test search
    int point9[2] = {1, 2};
    bool found = KDtree::search(root, point9);



    if (found)
        cout << "Found point (1, 2)" << endl;
    else
        cout << "Did not find point (1, 2)" << endl;

    //test quadtree



    return 0;
}