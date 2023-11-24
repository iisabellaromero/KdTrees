//
// Created by MacBookPro on 23/11/23.
//
#import "kdtree.h"
#import "quadtree.h"
#import <iostream>
#import <fstream>
#import <chrono>

int main(){

    // Initialize chrono
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::duration<double> time_span;

    //Test the kdtree

    // Start chrono
    begin = std::chrono::steady_clock::now();

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

    //End chrono
    end = std::chrono::steady_clock::now();

    // Calculate time
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

    // Print time
    std::cout << "Time: " << time_span.count() << " seconds." << std::endl;


    //test quadtree

    // Start chrono
    begin = std::chrono::steady_clock::now();

    QuadTreeNode* root2 = nullptr;
    int point8[2] = {1, 2};
    int point9[2] = {3, 4};
    int point10[2] = {5, 6};
    int point11[2] = {7, 8};
    int point12[2] = {9, 10};

    root2 = Quadtree::insert(root2, point8);
    root2 = Quadtree::insert(root2, point9);
    root2 = Quadtree::insert(root2, point10);
    root2 = Quadtree::insert(root2, point11);
    root2 = Quadtree::insert(root2, point12);

    Quadtree::display(root2, 0);

    //test nearest neighbor
    int point13[2] = {2, 3};
    QuadTreeNode* nearest2 = Quadtree::nearestNeighbour(root2, point13);
    std::cout << "Nearest neighbor to (2, 3): (" << nearest2->dataPoint[0] << ", " << nearest2->dataPoint[1] << ")" << std::endl;

    //test search
    int point14[2] = {1, 2};
    bool found2 = Quadtree::search(root2, point14);

    if (found2)
        std::cout << "Found point (1, 2)" << std::endl;
    else
        std::cout << "Did not find point (1, 2)" << std::endl;

    //End chrono
    end = std::chrono::steady_clock::now();

    // Calculate time
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

    // Print time
    std::cout << "Time: " << time_span.count() << " seconds." << std::endl;

    return 0;
}