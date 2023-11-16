#include <iostream>
#include <vector>

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

class KDTree
{
public:
    KDNode *root;

    KDTree()
    {
        root = nullptr;
    }

    // Get the root of the tree
    KDNode *getRoot()
    {
        return root;
    }

    // Insert a point into the tree
    void insert(int point[])
    {
        root = insert(root, point, 0);
    }

    // Get point
    int *getPoint(KDNode *node)
    {
        return node->point;
    }

    // Get left child
    KDNode *getLeft(KDNode *node)
    {
        return node->left;
    }

    void display()
    {
        display(root, 0);
    }

private:
    KDNode *newNode(int arr[])
    {
        KDNode *temp = new KDNode;
        // Copy the data
        for (int i = 0; i < k; i++)
            temp->point[i] = arr[i];
        // Initialize the children as NULL
        temp->left = temp->right = nullptr;
        return temp;
    }

    KDNode *insert(KDNode *root, int point[], int depth)
    {
        // Base Case
        if (root == nullptr)
            return newNode(point);

        int dim = depth % k; // Current dimension x=1, y=0 (for 2D)

        // If the point to be inserted has a smaller value than the current root point, insert it into the left subtree
        // It's like a BST insertion
        if (point[dim] < (root->point[dim]))
            root->left = insert(root->left, point, depth + 1);
        else
            root->right = insert(root->right, point, depth + 1);

        return root;
    }

    // Display
    void display(KDNode *root, int depth){
        if (root == nullptr)
            return;

        int dim = depth % k; // Current dimension x=0, y=1 (for 2D)

        std::cout << "(" << root->point[0] << ", " << root->point[1] << ") " << dim << endl;

        display(root->left, depth + 1);
        display(root->right, depth + 1);
    }

};

int main()
{
    KDTree kdtree;

    // Sample points
    int points[][k] = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19}};

    // Insert points into the k-d tree
    for (int i = 0; i < sizeof(points) / sizeof(points[0]); ++i){
        kdtree.insert(points[i]);
    }
    
    kdtree.display();
    

    return 0;
}
