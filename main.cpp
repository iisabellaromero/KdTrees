#include <iostream>
#include <vector>
#include "KDNode.h"

using namespace std;

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

        // Search a point in the tree
    KDNode *SearchNode(KDNode *root, int point[], int depth)
    {
        // Base Cases
        if (root == nullptr)
            return nullptr;
        if (arePointsSame(root->point, point))
            return root;

        // Current dimension x=1, y=0 (for 2D)
        int dim = depth % k;

        // If the point to be searched is smaller than the current root point, search it in the left subtree
        if (point[dim] < root->point[dim])
            return SearchNode(root->left, point, depth + 1);

        // If the point to be searched is greater than the current root point, search it in the right subtree
        return SearchNode(root->right, point, depth + 1);
    }

    // Delete a point from the tree
void DeletePoint(KDNode *&root, int point[], int depth)
{
    // Base Cases
    if (root == nullptr)
        return;

    // Current dimension x=1, y=0 (for 2D)
    int dim = depth % k;

    // If the point to be deleted is smaller than the current root point, search it in the left subtree
    if (point[dim] < root->point[dim])
        DeletePoint(root->left, point, depth + 1);

    // If the point to be deleted is greater than the current root point, search it in the right subtree
    else if (point[dim] > root->point[dim])
        DeletePoint(root->right, point, depth + 1);

    // If the point to be deleted is the current root point
    else
    {
        // If the node is a leaf node or has only a right child
        if (root->left == nullptr)
        {
            KDNode *temp = root->right;
            delete root;
            root = temp; // Update the pointer to the right child or nullptr if there is no right child
        }
        // If the node has only a left child
        else if (root->right == nullptr)
        {
            KDNode *temp = root->left;
            delete root;
            root = temp; // Update the pointer to the left child
        }
        // If the node has both left and right children
        else
        {
            KDNode *temp = FindMin(root->right, dim);
            *root->point = *temp->point;
            DeletePoint(root->right, temp->point, depth + 1);
        }
    }
}

    // Find the node with minimum value in the dimension
    KDNode *FindMin(KDNode *root, int d)
    {
        if (root == nullptr)
            return nullptr;

        KDNode *min = root;
        KDNode *l = FindMin(root->left, d);
        KDNode *r = FindMin(root->right, d);

        if (l != nullptr && l->point[d] < min->point[d])
            min = l;
        if (r != nullptr && r->point[d] < min->point[d])
            min = r;
        return min;
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

    // Check if two points are the same
    bool arePointsSame(int point1[], int point2[])
    {
        // Compare individual pointinate values
        for (int i = 0; i < k; ++i)
            if (point1[i] != point2[i])
                return false;

        return true;
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
    int points[][2] = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19}};

    // Insert points into the k-d tree
    for (int i = 0; i < sizeof(points) / sizeof(points[0]); ++i)
    {
        kdtree.insert(points[i]);
    }

    kdtree.display();

    cout << "Search for point (3, 6): " << endl;
    KDNode *result = kdtree.SearchNode(kdtree.getRoot(), points[0], 0);

    if (result != nullptr)
    {
        cout << "Found: (" << result->point[0] << ", " << result->point[1] << ")" << endl;
    }
    else
    {
        cout << "Not found." << endl;
    }

    KDNode *root = kdtree.getRoot();

    cout << "Delete point (17,15): " << endl;
    kdtree.DeletePoint(root, points[1], 0);
    kdtree.display();

    return 0;
}


// TO-DO: 
// 1. Delete FUNCIONA PERO NO PARA EL ROOT ni para (13,15) por alguna razon
// 2. Nearest Neighbor
// 3. Range Search
