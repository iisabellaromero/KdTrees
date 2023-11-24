//
// Created by MacBookPro on 23/11/23.
//
#include "kdtree.h"
#include "quadtree.h"
#include <iostream>
#include <fstream>
#include <chrono>

#include <vector> // SOLO ES USADO PARA TESTS
#include <random> // SOLO ES USADO PARA TESTS

int main(){
    // Init random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100000000);


    for (int i = 10; i < 100000000; i *= 10){

        std::cout << std::endl;
        std::cout << "Testing with " << i << " points" << std::endl;

        // Create i points
        std::vector<int*> points;
        for (int j = 0; j < i; j++){
            int* point = new int[2];
            point[0] = dis(gen);
            point[1] = dis(gen);
            points.push_back(point);
        }


        // Set up chrono
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;
        std::chrono::duration<double> time_span;

        // Test the kdtree

        std::cout << "Testing KDTree" << std::endl;

        // Start timer
        begin = std::chrono::steady_clock::now();

        KDTreeNode* root = nullptr;

        // Insert points
        for (int j = 0; j < i; j++){
            root = KDtree::insert(root, points[j]);
        }

        // For debug
        //KDtree::display(root, 0);

        // Test nearest neighbor
        // Select random point
        int point1[2] = {dis(gen), dis(gen)};
        KDTreeNode* nearest = KDtree::nearestNeighbor(root, point1);
        std::cout << "Nearest neighbor to (" << point1[0] << ", " << point1[1] << "): (" << nearest->dataPoint[0] << ", " << nearest->dataPoint[1] << ")" << std::endl;

        // Test search
        int point2[2] = {1, 2};
        bool found = KDtree::search(root, point2);

        if (found)
            std::cout << "Found point (1, 2)" << std::endl;
        else
            std::cout << "Did not find point (1, 2)" << std::endl;

        // End timer
        end = std::chrono::steady_clock::now();

        // Calculate time
        time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

        // Print time
        std::cout << "Time elapsed: " << time_span.count() << " seconds." << std::endl;

        // Test quadtree

        std::cout << "Testing QuadTree" << std::endl;

        // Start timer
        begin = std::chrono::steady_clock::now();

        QuadPoint topLeft = QuadPoint(0, 0);
        QuadPoint botRight = QuadPoint(100000000, 100000000);
        Quad* quad = new Quad(topLeft, botRight);

        // Create nodes based on the points
        for (int j = 0; j < i; j++){
            auto* node = new QuadTreeNode(QuadPoint(points[j][0], points[j][1]), j);
            quad->insert(node);
        }

        // Test nearest neighbor
        int point13[2] = {1, 2};
        QuadTreeNode* nearest2 = quad->nearestNeighbor(QuadPoint(2, 3), point13, point13);
        std::cout << "Nearest neighbor to (2, 3): (" << nearest2->dataPoint.coordinates[0] << ", " << nearest2->dataPoint.coordinates[1] << ")" << std::endl;

        // Test search
        bool found2 = quad->search(QuadPoint(1, 2));

        if (found2)
            std::cout << "Found point (1, 2)" << std::endl;
        else
            std::cout << "Did not find point (1, 2)" << std::endl;

        // End timer
        end = std::chrono::steady_clock::now();

        // Calculate time
        time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

        // Print time
        std::cout << "Time elapsed: " << time_span.count() << " seconds." << std::endl;

    }


    return 0;
}