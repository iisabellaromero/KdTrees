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

    std::cout << "Deseas realizar: " << std::endl;
    std::cout << "1. Prueba de insercion" << std::endl;
    std::cout << "2. Prueba de busqueda" << std::endl;
    std::cout << "3. Prueba completa" << std::endl;

    int opcion;
    std::cin >> opcion;

    int point1[2] = {dis(gen), dis(gen)};

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

        // Start timer (if test is insertion test or complete test)
        if (opcion == 1 || opcion == 3) {
            begin = std::chrono::steady_clock::now();
        }

        KDTreeNode* root = nullptr;

        // Insert points
        for (int j = 0; j < i; j++){
            root = KDtree::insert(root, points[j]);
        }

        // If test is search test, start timer here and end timer if it's insertion test
        if (opcion == 2) {
            begin = std::chrono::steady_clock::now();
        }
        else if (opcion == 1) {
            end = std::chrono::steady_clock::now();
        }

        if (opcion != 1) {

            // For debug
            //KDtree::display(root, 0);

            // Test nearest neighbor
            KDTreeNode *nearest = KDtree::nearestNeighbor(root, point1);
            std::cout << "Nearest neighbor to (" << point1[0] << ", " << point1[1] << "): (" << nearest->dataPoint[0]
                      << ", " << nearest->dataPoint[1] << ")" << std::endl;

            // Test search
            int point2[2] = {points[0][0], points[0][1]};
            bool found = KDtree::search(root, point2);

            if (found) {
                std::cout << "Found point (" << points[0][0] << ", " << points[0][1] << ")" << std::endl;
            } else {
                std::cout << "Did not find point (" << points[0][0] << ", " << points[0][1] << ")" << std::endl;
            }

            // End timer if test is not insertion test

            end = std::chrono::steady_clock::now();
        }

        // Calculate time
        time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

        // Print time
        std::cout << "Time elapsed: " << time_span.count() << " seconds." << std::endl;

        // Test quadtree

        std::cout << "Testing QuadTree" << std::endl;

        // Start timer if test is insertion test or complete test

        if (opcion == 1 || opcion == 3) {
            begin = std::chrono::steady_clock::now();
        }

        QuadPoint topLeft = QuadPoint(0, 0);
        QuadPoint botRight = QuadPoint(100000000, 100000000);
        Quad* quad = new Quad(topLeft, botRight);

        // Create nodes based on the points
        for (int j = 0; j < i; j++){
            auto* node = new QuadTreeNode(QuadPoint(points[j][0], points[j][1]), j);
            quad->insert(node);
        }

        // If test is search test, start timer here
        if (opcion == 2) {
            begin = std::chrono::steady_clock::now();
        }
        else if (opcion == 1) {
            end = std::chrono::steady_clock::now();
        }

        if (opcion != 1) {

            // Test nearest neighbor

            QuadTreeNode *nearest2 = quad->nearestNeighbor(QuadPoint(point1[0], point1[1]),
                                                           quad->bottomLeft.coordinates, quad->topRight.coordinates);
            std::cout << "Nearest neighbor to (" << point1[0] << ", " << point1[1] << "): ("
                      << nearest2->dataPoint.coordinates[0] << ", " << nearest2->dataPoint.coordinates[1] << ")"
                      << std::endl;

            // Test search
            bool found2 = quad->search(QuadPoint(points[0][0], points[0][1]));

            if (found2)
                std::cout << "Found point (" << points[0][0] << ", " << points[0][1] << ")" << std::endl;
            else
                std::cout << "Did not find point (" << points[0][0] << ", " << points[0][1] << ")" << std::endl;

            // End timer if test is not insertion test
            end = std::chrono::steady_clock::now();
        }

        // Calculate time
        time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

        // Print time
        std::cout << "Time elapsed: " << time_span.count() << " seconds." << std::endl;

    }


    return 0;
}