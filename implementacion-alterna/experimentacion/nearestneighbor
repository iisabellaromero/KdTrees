void nearestNeighborTime(KDTreeNode* root, int point[]) {
    auto start = std::chrono::high_resolution_clock::now();

    KDtree::nearestNeighbor(root, point);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    std::cout << "Time taken by nearest neighbor algorithm: " << duration.count() << " nanoseconds" << std::endl;
}