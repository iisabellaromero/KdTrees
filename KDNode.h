#include <iostream>
using namespace std;

const int k = 2;

class KDNode
{
public:
    int point[k];
    KDNode *left;
    KDNode *right;

    KDNode() {
        left = right = nullptr;
    }
};