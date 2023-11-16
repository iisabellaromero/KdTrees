#include <iostream>
#include "Point.h"

using namespace std;

const int k=2; //this are the tree dimentions, you can modify it to any number you want

class KDNode{
    int point[k];
    KDNode *left;
    KDNode *right;

    public:
        KDNode* newNode(int arr[]){
            KDNode *temp = new KDNode;
            //Copy the data
            for (int i=0; i<k; i++)
                temp->point[i] = arr[i];
            //Initialize the children as NULL
            temp->left = temp->right = NULL;
            return temp;
        }

        KDNode* insert(KDNode *root , int point[], int depth){
            //Base Case
            if (root == NULL)
                return newNode(point);
            
            int dim = depth % k; // Current dimension x=1, y=0 (for 2D)

            // If the point to be inserted has smaller value than the current root point then insert it into the left subtree
            // It's like a BST insertion
            if (point[dim] < (root->point[dim]))
                root->left = insert(root->left, point, depth + 1);
            else
                root->right = insert(root->right, point, depth + 1);
            
            return root;
        }
}